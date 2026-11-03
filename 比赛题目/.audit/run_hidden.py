from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
import sys
import tempfile
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(
    0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts"
)

import audit_details as ad
from audit_v3103 import Package
from oi_common import output_matches
from run_samples import BUILD, GXX, infer, read_std, run_one, std_name

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"


def hidden_pairs(pkg: Package, fmt: str, slug: str) -> dict[int, tuple[bytes | None, bytes | None]]:
    pairs: dict[int, list[bytes | None]] = {}
    if fmt == "noip_zip":
        nested = pkg.nested_zip(f"data/{slug}.zip")
        if nested is None:
            return {}
        try:
            for name in nested.namelist():
                path = Path(name)
                if not path.stem.isdigit():
                    continue
                number = int(path.stem)
                suffix = path.suffix.lower()
                if suffix not in (".in", ".out", ".ans"):
                    continue
                slot = pairs.setdefault(number, [None, None])
                if suffix == ".in":
                    slot[0] = nested.read(name)
                elif slot[1] is None or suffix == ".ans":
                    slot[1] = nested.read(name)
        finally:
            nested.close()
        return {k: (v[0], v[1]) for k, v in pairs.items()}

    prefix = f"data/{slug}/"
    if pkg.is_zip:
        assert pkg._zip is not None
        for name in pkg.names:
            if not name.startswith(prefix):
                continue
            stem = Path(name).stem
            suffix = Path(name).suffix.lower()
            if not stem.isdigit() or suffix not in (".in", ".out", ".ans"):
                continue
            number = int(stem)
            slot = pairs.setdefault(number, [None, None])
            data = pkg._zip.read(pkg._originals[name])
            if suffix == ".in":
                slot[0] = data
            elif slot[1] is None or suffix == ".ans":
                slot[1] = data
        return {k: (v[0], v[1]) for k, v in pairs.items()}

    data_dir = pkg.path / "data" / slug
    if data_dir.is_dir():
        for path in data_dir.iterdir():
            if not path.stem.isdigit() or path.suffix.lower() not in (".in", ".out", ".ans"):
                continue
            number = int(path.stem)
            slot = pairs.setdefault(number, [None, None])
            if path.suffix.lower() == ".in":
                slot[0] = path.read_bytes()
            elif slot[1] is None or path.suffix.lower() == ".ans":
                slot[1] = path.read_bytes()
    return {k: (v[0], v[1]) for k, v in pairs.items()}


def detach_std(pkg: Package, fmt: str, slug: str, dest: Path) -> str | None:
    std = std_name(pkg, fmt, slug)
    if std is None:
        return None
    dest.write_bytes(read_std(pkg, std))
    return std


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--category", action="append", default=[])
    parser.add_argument("--timeout", type=int, default=10)
    args = parser.parse_args()
    categories = args.category or ["CSP-J", "NOIP"]
    BUILD.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ)
    env["PATH"] = str(GXX.parent) + os.pathsep + env.get("PATH", "")
    records = []
    for category in categories:
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                fmt, slugs = infer(pkg)
                stem = child.stem if child.is_file() else child.name
                for slug in slugs:
                    record = {
                        "category": category,
                        "package": stem,
                        "slug": slug,
                        "compiled": False,
                        "tests": 0,
                        "passed": 0,
                        "failures": [],
                    }
                    src = BUILD / f"{stem}-{slug}.cpp"
                    src.parent.mkdir(parents=True, exist_ok=True)
                    std = detach_std(pkg, fmt, slug, src)
                    if std is None:
                        record["failures"].append("missing std")
                        records.append(record)
                        continue
                    exe = BUILD / f"{stem}-{slug}.exe"
                    proc = subprocess.run(
                        [str(GXX), "-O2", "-std=c++14", "-Wl,--stack=536870912",
                         str(src), "-o", str(exe)],
                        capture_output=True, text=True, encoding="utf-8",
                        errors="replace", env=env,
                    )
                    if proc.returncode != 0:
                        record["failures"].append("compile: " + (proc.stderr or proc.stdout)[-800:])
                        records.append(record)
                        continue
                    record["compiled"] = True
                    io = "file" if "freopen" in src.read_text(encoding="utf-8", errors="replace") else "std"
                    pairs = hidden_pairs(pkg, fmt, slug)
                    record["tests"] = len(pairs)
                    for number, (inp, expected) in sorted(pairs.items()):
                        if inp is None or expected is None:
                            record["failures"].append(f"{number}: missing input or answer")
                            continue
                        ok, got = run_one(exe, slug, io, inp.decode(errors="replace"), args.timeout)
                        if ok and output_matches(got, expected.decode(errors="replace")):
                            record["passed"] += 1
                        else:
                            record["failures"].append(
                                f"{number}: {'TIMEOUT' if got == 'TIMEOUT' else 'wrong output'}"
                            )
                    records.append(record)
                    print(f"{category}/{stem}/{slug}: {record['passed']}/{record['tests']}", flush=True)
            finally:
                pkg.close()
    tag = "-".join(categories).replace("/", "_")
    (OUT / f"hidden_{tag}.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    total = sum(r["tests"] for r in records)
    passed = sum(r["passed"] for r in records)
    problems = [r for r in records if r["failures"]]
    lines = [
        "# std 隐藏测试点复测",
        "",
        f"题目 {len(records)}，测试点 {total}，通过 {passed}，异常题 {len(problems)}。",
        "",
    ]
    for record in records:
        status = "PASS" if record["compiled"] and record["passed"] == record["tests"] else "FAIL"
        lines.append(
            f"- {record['category']}/{record['package']}/{record['slug']}: "
            f"{status}（{record['passed']}/{record['tests']}）"
        )
        for failure in record["failures"][:8]:
            lines.append("  - " + failure.replace("\n", " ")[:300])
    (OUT / f"hidden_{tag}.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"TOTAL {passed}/{total}, problem records {len(records)}, failures {len(problems)}")


if __name__ == "__main__":
    main()
