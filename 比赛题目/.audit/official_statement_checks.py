from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))

import audit_details as ad
from audit_v3103 import Package, first_name

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"
PUBLIC = OUT / "public"
CHECK = Path(
    r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts\check_md.py"
)
PY = sys.executable


def infer(pkg: Package) -> tuple[str, list[str]]:
    names = pkg.names
    legacy = sorted({n.split("/", 1)[0] for n in names if re.match(r"T\d+/", n)})
    noip_nested = any(n.startswith("data/") and n.endswith(".zip") for n in names)
    if legacy:
        return "legacy_cspj_T1-T4", legacy
    if noip_nested:
        return "noip_zip", sorted(
            Path(n).stem for n in names if n.startswith("data/") and n.endswith(".zip")
        )
    data_dirs = sorted(
        {n.split("/", 2)[1] for n in names if n.startswith("data/") and n.count("/") >= 2}
    )
    slugs = data_dirs or sorted(
        {Path(n).stem for n in names if re.match(r"std/[^/]+/[^/]+\.cpp$", n)}
    )
    return "generic_dir", slugs


def sample_pairs(samples: dict, slug: str) -> dict[int, tuple[bytes | None, bytes | None]]:
    result: dict[int, list[bytes | None]] = {}
    for name, data in samples["files"].items():
        stem = Path(name).stem
        suffix = Path(name).suffix.lower()
        if suffix not in (".in", ".ans", ".out"):
            continue
        rest = stem[len(slug):] if stem.startswith(slug) else ""
        if rest.isdigit():
            number = int(rest)
        elif not rest:
            number = 1
        else:
            match = re.search(r"(\d+)$", stem)
            if not match:
                continue
            number = int(match.group(1))
        kind = suffix[1:]
        slot = result.setdefault(number, [None, None])
        if kind == "in":
            slot[0] = data
        elif kind in ("ans", "out"):
            if slot[1] is None or kind == "ans":
                slot[1] = data
    return {k: (v[0], v[1]) for k, v in result.items()}


def stage(pkg: Package, fmt: str, slug: str, root: Path) -> tuple[int, int]:
    samples = ad.resolve_samples(pkg, fmt, slug)
    pairs = sample_pairs(samples, slug)
    dest = root / slug
    dest.mkdir(parents=True, exist_ok=True)
    written = 0
    for number, (inp, outp) in sorted(pairs.items()):
        if inp is None or outp is None:
            continue
        (dest / f"{slug}{number}.in").write_bytes(inp)
        (dest / f"{slug}{number}.ans").write_bytes(outp)
        written += 1
    return written, len(pairs)


def run_check(statement: Path, public_root: Path | None, log_name: str) -> dict:
    cmd = [PY, str(CHECK), "--statement", str(statement)]
    if public_root is not None:
        cmd += ["--public-root", str(public_root)]
    env = dict(os.environ)
    env["PYTHONIOENCODING"] = "utf-8"
    proc = subprocess.run(
        cmd,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        env=env,
    )
    log = OUT / "logs" / log_name
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text(
        "$ " + " ".join(cmd) + "\n\nSTDOUT:\n" + proc.stdout + "\nSTDERR:\n" + proc.stderr,
        encoding="utf-8",
    )
    tail = (proc.stdout + proc.stderr).strip().splitlines()
    return {
        "statement": str(statement.relative_to(ROOT)),
        "public_root": str(public_root.relative_to(ROOT)) if public_root else None,
        "returncode": proc.returncode,
        "log": str(log.relative_to(ROOT)),
        "summary": tail[-1] if tail else "",
        "output": proc.stdout.strip(),
    }


def main() -> None:
    if PUBLIC.exists():
        shutil.rmtree(PUBLIC)
    PUBLIC.mkdir(parents=True)
    records = []
    for index, category in enumerate(("CSP-J", "NOIP"), start=0):
        folder = ROOT / category
        for child in sorted(folder.iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                fmt, slugs = infer(pkg)
                stem = child.stem if child.suffix.lower() == ".zip" else child.name
                key = f"{index}-{len(records):02d}"
                public_root = PUBLIC / key
                staged = {}
                for slug in slugs:
                    staged[slug] = stage(pkg, fmt, slug, public_root)
                checks = []
                if fmt == "legacy_cspj_T1-T4":
                    for slug in slugs:
                        statement = child / slug / "statement.md" if not pkg.is_zip else None
                        # Legacy sources live inside the ZIP; use the extracted copy.
                        statement = OUT / "text" / category / child.name / slug / "statement.md"
                        checks.append(run_check(statement, public_root, f"{key}-{slug}.txt"))
                else:
                    statement_name = first_name(
                        pkg.names, ["statement.md", "总题面.md", "题面.md"]
                    )
                    statement = OUT / "text" / category / child.name / statement_name
                    checks.append(run_check(statement, public_root, f"{key}-all.txt"))
                records.append(
                    {
                        "category": category,
                        "package": stem,
                        "format": fmt,
                        "slugs": slugs,
                        "staged": staged,
                        "checks": checks,
                    }
                )
            finally:
                pkg.close()
    (OUT / "official_statement_checks.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# 官方 check_md --statement 复核（含 --public-root）", ""]
    for record in records:
        lines.append(f"## {record['category']} / {record['package']}")
        lines.append(f"- 格式 `{record['format']}`；slug：{', '.join(record['slugs'])}")
        for check in record["checks"]:
            lines.append(
                f"- `{Path(check['statement']).name}` → "
                f"{'PASS' if check['returncode'] == 0 else 'FAIL'}"
                f"（日志 `{check['log']}`）"
            )
            if check["returncode"] != 0:
                for line in check["output"].splitlines():
                    lines.append(f"  - {line}")
        lines.append("")
    (OUT / "official_statement_checks.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"Wrote {OUT / 'official_statement_checks.json'} and .md")


if __name__ == "__main__":
    main()
