from __future__ import annotations

import json
import shutil
import subprocess
import sys
import tempfile
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))

import audit_details as ad
from audit_v3103 import Package, first_name

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"
CHECK = Path(
    r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts\check_isolation.py"
)
PY = sys.executable


def infer(pkg: Package) -> tuple[str, list[str]]:
    names = pkg.names
    noip_nested = any(n.startswith("data/") and n.endswith(".zip") for n in names)
    if noip_nested:
        return "noip_zip", sorted(
            Path(n).stem for n in names if n.startswith("data/") and n.endswith(".zip")
        )
    data_dirs = sorted(
        {n.split("/", 2)[1] for n in names if n.startswith("data/") and n.count("/") >= 2}
    )
    return "generic_dir", data_dirs


def write_hidden(pkg: Package, fmt: str, slug: str, root: Path) -> int:
    count = 0
    data_suffixes = (".in", ".out", ".ans")
    if fmt == "noip_zip":
        nested = pkg.nested_zip(f"data/{slug}.zip")
        if nested is None:
            return 0
        try:
            for name in nested.namelist():
                if name.endswith(data_suffixes):
                    (root / Path(name).name).write_bytes(nested.read(name))
                    if name.endswith(".in"):
                        count += 1
        finally:
            nested.close()
        return count
    prefix = f"data/{slug}/"
    if pkg.is_zip:
        assert pkg._zip is not None
        for name in pkg.names:
            if name.startswith(prefix) and name.endswith(data_suffixes):
                (root / Path(name).name).write_bytes(pkg._zip.read(pkg._originals[name]))
                if name.endswith(".in"):
                    count += 1
    else:
        data_dir = pkg.path / "data" / slug
        if data_dir.is_dir():
            for path in data_dir.iterdir():
                if path.suffix not in data_suffixes or not path.is_file():
                    continue
                shutil.copy2(path, root / path.name)
                if path.suffix == ".in":
                    count += 1
    return count


def write_public(pkg: Package, fmt: str, slug: str, root: Path) -> int:
    samples = ad.resolve_samples(pkg, fmt, slug)
    count = 0
    for name, data in samples["files"].items():
        if name.endswith(".in"):
            (root / Path(name).name).write_bytes(data)
            count += 1
    return count


def main() -> None:
    work_root = OUT / "isolation_tmp"
    work_root.mkdir(parents=True, exist_ok=True)
    records = []
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                fmt, slugs = infer(pkg)
                stem = child.stem if child.is_file() else child.name
                text_root = OUT / "text" / category / child.name
                statement_name = first_name(
                    pkg.names, ["statement.md", "总题面.md", "题面.md"]
                )
                statement = text_root / statement_name
                for slug in slugs:
                    work = Path(tempfile.mkdtemp(prefix="iso-", dir=work_root))
                    try:
                        hidden = work / "hidden"
                        public = work / "public"
                        hidden.mkdir()
                        public.mkdir()
                        hidden_count = write_hidden(pkg, fmt, slug, hidden)
                        public_count = write_public(pkg, fmt, slug, public)
                        log = OUT / "logs" / f"isolation-{category}-{stem}-{slug}.txt"
                        log.parent.mkdir(parents=True, exist_ok=True)
                        cmd = [
                            str(PY),
                            str(CHECK),
                            "--hidden",
                            str(hidden),
                            "--public",
                            str(public),
                            "--statement",
                            str(statement),
                            "--slug",
                            slug,
                        ]
                        proc = subprocess.run(
                            cmd,
                            capture_output=True,
                            text=True,
                            encoding="utf-8",
                            errors="replace",
                        )
                        log.write_text(
                            "$ " + " ".join(cmd) + "\n\nSTDOUT:\n" + proc.stdout
                            + "\nSTDERR:\n" + proc.stderr,
                            encoding="utf-8",
                        )
                        records.append(
                            {
                                "category": category,
                                "package": stem,
                                "slug": slug,
                                "hidden_inputs": hidden_count,
                                "public_inputs": public_count,
                                "returncode": proc.returncode,
                                "passed": proc.returncode == 0,
                                "log": str(log.relative_to(ROOT)),
                                "output": proc.stdout.strip(),
                            }
                        )
                    finally:
                        shutil.rmtree(work, ignore_errors=True)
            finally:
                pkg.close()
    shutil.rmtree(work_root, ignore_errors=True)
    (OUT / "isolation.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# 公开/隐藏隔离检查", ""]
    for record in records:
        status = "PASS" if record["passed"] else "FAIL"
        lines.append(
            f"- {record['category']}/{record['package']}/{record['slug']}: "
            f"{status}（hidden {record['hidden_inputs']}，public {record['public_inputs']}）"
        )
        if not record["passed"]:
            lines.append("  - " + record["output"].replace("\n", " ")[:500])
    (OUT / "isolation.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"Wrote {OUT / 'isolation.json'} and .md")


if __name__ == "__main__":
    main()
