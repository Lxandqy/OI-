from __future__ import annotations

import io
import sys
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def open_zip(source):
    return zipfile.ZipFile(source)


def main() -> None:
    total = 0
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            size = 0
            if child.is_file():
                with open_zip(child) as zf:
                    for info in zf.infolist():
                        size += info.file_size
                        if info.filename.startswith("data/") and info.filename.endswith(".zip"):
                            try:
                                with zipfile.ZipFile(io.BytesIO(zf.read(info))) as nested:
                                    size += sum(x.file_size for x in nested.infolist())
                            except Exception:
                                pass
            else:
                size = sum(p.stat().st_size for p in child.rglob("*") if p.is_file())
            total += size
            print(f"{size/1048576:10.1f} MiB  {category}/{child.name}")
    print(f"{total/1048576:10.1f} MiB  TOTAL")


if __name__ == "__main__":
    main()
