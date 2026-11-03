from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(
    0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts"
)

import audit_details as ad
from audit_v3103 import Package, first_name
from oi_common import extract_samples, output_matches, split_problems

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"
BUILD = OUT / "build"
GXX = Path(
    r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\tools\w64devkit\w64devkit\bin\g++.exe"
)


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


def std_name(pkg: Package, fmt: str, slug: str) -> str | None:
    candidates = (
        [f"{slug}/std.cpp"]
        if fmt == "legacy_cspj_T1-T4"
        else [f"std/{slug}/{slug}.cpp", f"std/{slug}.cpp", f"代码/{slug}.cpp"]
    )
    for candidate in candidates:
        if candidate in pkg.names:
            return candidate
    return None


def read_std(pkg: Package, name: str) -> bytes:
    if pkg.is_zip:
        assert pkg._zip is not None
        return pkg._zip.read(pkg._originals[name])
    return (pkg.path / Path(name)).read_bytes()


def run_one(exe: Path, slug: str, io: str, inp: str, timeout: int = 20) -> tuple[bool, str]:
    with tempfile.TemporaryDirectory(prefix="oi-run-") as tmp:
        work = Path(tmp)
        if io == "file":
            (work / f"{slug}.in").write_text(inp, encoding="utf-8")
            try:
                proc = subprocess.run(
                    [str(exe)],
                    cwd=work,
                    capture_output=True,
                    timeout=timeout,
                )
            except subprocess.TimeoutExpired:
                return False, "TIMEOUT"
            out = work / f"{slug}.out"
            got = out.read_text(errors="replace") if out.exists() else ""
            return proc.returncode == 0, got
        try:
            proc = subprocess.run(
                [str(exe)],
                cwd=work,
                input=inp.encode(),
                capture_output=True,
                timeout=timeout,
            )
        except subprocess.TimeoutExpired:
            return False, "TIMEOUT"
        return proc.returncode == 0, proc.stdout.decode(errors="replace")


def sample_pairs(samples: dict, slug: str) -> dict[int, tuple[bytes | None, bytes | None]]:
    result: dict[int, list[bytes | None]] = {}
    for name, data in samples["files"].items():
        stem = Path(name).stem
        suffix = Path(name).suffix.lower()
        if suffix not in (".in", ".ans", ".out"):
            continue
        if stem.startswith(slug):
            rest = stem[len(slug):]
            if rest.isdigit():
                number = int(rest)
            elif not rest:
                number = 1
            else:
                match = re.search(r"(\d+)$", stem)
                if not match:
                    continue
                number = int(match.group(1))
        else:
            # Legacy CSP-J attachments are named attachment1.in/attachment2.in.
            match = re.search(r"(\d+)$", stem)
            if not match:
                continue
            number = int(match.group(1))
        slot = result.setdefault(number, [None, None])
        if suffix == ".in":
            slot[0] = data
        elif suffix in (".ans", ".out"):
            if slot[1] is None or suffix == ".ans":
                slot[1] = data
    return {k: (v[0], v[1]) for k, v in result.items()}


def main() -> None:
    if BUILD.exists():
        shutil.rmtree(BUILD)
    BUILD.mkdir(parents=True)
    env = dict(os.environ)
    env["PATH"] = str(GXX.parent) + os.pathsep + env.get("PATH", "")
    records = []
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                fmt, slugs = infer(pkg)
                stem = child.stem if child.is_file() else child.name
                for slug in slugs:
                    std = std_name(pkg, fmt, slug)
                    record = {
                        "category": category,
                        "package": stem,
                        "slug": slug,
                        "std": std,
                        "compile": "MISSING",
                        "compile_error": "",
                        "inline": [],
                        "public": [],
                    }
                    if not std:
                        records.append(record)
                        continue
                    src = BUILD / f"{stem}-{slug}.cpp"
                    src.parent.mkdir(parents=True, exist_ok=True)
                    src.write_bytes(read_std(pkg, std))
                    exe = BUILD / f"{stem}-{slug}.exe"
                    proc = subprocess.run(
                        [
                            str(GXX),
                            "-O2",
                            "-std=c++14",
                            "-Wl,--stack=536870912",
                            str(src),
                            "-o",
                            str(exe),
                        ],
                        capture_output=True,
                        text=True,
                        encoding="utf-8",
                        errors="replace",
                        env=env,
                    )
                    record["compile"] = "PASS" if proc.returncode == 0 else "FAIL"
                    record["compile_error"] = (proc.stderr or proc.stdout)[-1500:]
                    if proc.returncode != 0:
                        records.append(record)
                        continue
                    std_text = src.read_text(encoding="utf-8", errors="replace")
                    io = "file" if "freopen" in std_text else "std"
                    docs = ad.read_statement_and_solution(pkg, fmt, slug)
                    try:
                        parts = split_problems(docs["statement"])
                        inline = extract_samples(parts.get(slug, docs["statement"]))
                    except Exception:
                        inline = {}
                    for k, sample in sorted(inline.items()):
                        if "in" not in sample or "out" not in sample:
                            continue
                        ok, got = run_one(exe, slug, io, sample["in"])
                        record["inline"].append(
                            {
                                "k": k,
                                "ok": bool(ok and output_matches(got, sample["out"])),
                                "got": got[-300:],
                                "expected": sample["out"][-300:],
                            }
                        )
                    samples = ad.resolve_samples(pkg, fmt, slug)
                    for k, (inp, outp) in sorted(sample_pairs(samples, slug).items()):
                        if inp is None or outp is None:
                            continue
                        ok, got = run_one(exe, slug, io, inp.decode(errors="replace"))
                        record["public"].append(
                            {
                                "k": k,
                                "ok": bool(
                                    ok
                                    and output_matches(
                                        got, outp.decode(errors="replace")
                                    )
                                ),
                            }
                        )
                    records.append(record)
            finally:
                pkg.close()
    (OUT / "run_samples.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# std 编译与样例复现", ""]
    for record in records:
        inline = record["inline"]
        public = record["public"]
        lines.append(
            f"- {record['category']}/{record['package']}/{record['slug']}: "
            f"compile={record['compile']}; inline={sum(x['ok'] for x in inline)}/{len(inline)}; "
            f"public={sum(x['ok'] for x in public)}/{len(public)}"
        )
        if record["compile"] == "FAIL":
            lines.append("  - " + record["compile_error"].replace("\n", " ")[:300])
        for item in inline + public:
            if not item["ok"]:
                lines.append(f"  - FAIL sample {item['k']}")
    (OUT / "run_samples.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"Wrote {OUT / 'run_samples.json'} and .md")


if __name__ == "__main__":
    main()
