from __future__ import annotations

import subprocess
import sys
import urllib.request
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\tools")
URL = (
    "https://github.com/skeeto/w64devkit/releases/download/v2.10.1/"
    "w64devkit-x64-2.10.1.7z.exe"
)
EXE = ROOT / "w64devkit-x64-2.10.1.7z.exe"
DEST = ROOT / "w64devkit"


def main() -> None:
    ROOT.mkdir(parents=True, exist_ok=True)
    if not EXE.is_file():
        print("downloading", URL)
        req = urllib.request.Request(URL, headers={"User-Agent": "codex-audit"})
        with urllib.request.urlopen(req, timeout=120) as response, EXE.open("wb") as out:
            total = int(response.headers.get("Content-Length", "0"))
            done = 0
            while True:
                chunk = response.read(1024 * 1024)
                if not chunk:
                    break
                out.write(chunk)
                done += len(chunk)
                if total:
                    print(f"\r{done * 100 // total}%", end="", flush=True)
        print()
    DEST.mkdir(parents=True, exist_ok=True)
    print("extracting")
    proc = subprocess.run(
        [str(EXE), "-y", f"-o{DEST}"],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    print("exit", proc.returncode)
    print(proc.stdout[-1000:])
    print(proc.stderr[-1000:])
    for name in ("g++.exe", "gcc.exe", "mingw32-make.exe"):
        path = DEST / "bin" / name
        print(name, path.is_file(), path)


if __name__ == "__main__":
    main()
