from __future__ import annotations

import shutil
import subprocess
import sys
import zipfile
from pathlib import Path


PY = Path(sys.executable)
SKILL = Path(r"C:\Users\Administrator\.codex\skills\oi-contest-authoring")
GXX = Path(
    r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\tools\w64devkit\w64devkit\bin\g++.exe"
)
ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
WORK = ROOT / ".audit" / "check_one"


def main() -> None:
    if len(sys.argv) not in (2, 3):
        raise SystemExit("usage: check_generic_package.py <zip-or-dir> [file|std]")
    source = Path(sys.argv[1])
    io = sys.argv[2] if len(sys.argv) == 3 else "std"
    if WORK.exists():
        shutil.rmtree(WORK)
    WORK.mkdir(parents=True)
    if source.is_dir():
        shutil.copytree(source, WORK / "pkg")
    else:
        with zipfile.ZipFile(source) as zf:
            zf.extractall(WORK / "pkg")
    pkg = WORK / "pkg"
    public = WORK / "public"
    public.mkdir()
    for item in (pkg / "下发").iterdir():
        if item.is_dir():
            shutil.copytree(item, public / item.name)
        elif item.suffix.lower() == ".zip":
            with zipfile.ZipFile(item) as zf:
                zf.extractall(public)
    slugs = sorted(p.name for p in (pkg / "std").iterdir() if p.is_dir())
    cmd = [
        str(PY),
        str(SKILL / "scripts" / "check_md.py"),
        "--statement",
        str(pkg / "statement.md"),
        "--solution",
        str(pkg / "solution.md"),
        "--io",
        io,
        "--compile",
        f"{GXX} -O2 -std=c++14",
        "--public-root",
        str(public),
    ]
    for slug in slugs:
        cmd += ["--std", f"{slug}={pkg / 'std' / slug / (slug + '.cpp')}"]
    print(" ".join(cmd))
    result = subprocess.run(cmd, cwd=pkg)
    raise SystemExit(result.returncode)


if __name__ == "__main__":
    main()
