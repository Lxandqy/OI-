from __future__ import annotations

import sys
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def main() -> None:
    target = ROOT / "CSP-J" / "CSP-J模拟赛第一套.zip"
    with zipfile.ZipFile(target, metadata_encoding="utf-8") as zf:
        name = next(n for n in zf.namelist() if n.endswith("std/star/star.cpp"))
        data = zf.read(name)
    for enc in ("utf-8", "gbk", "gb18030"):
        try:
            text = data.decode(enc)
            print("=" * 20, enc, "OK")
            for line in text.splitlines():
                if "//" in line:
                    print(line)
                    break
        except UnicodeDecodeError as exc:
            print("=" * 20, enc, "FAIL", exc.start)


if __name__ == "__main__":
    main()
