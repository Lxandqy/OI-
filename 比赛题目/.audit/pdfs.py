from __future__ import annotations

import sys
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def main() -> None:
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            if child.is_file():
                with zipfile.ZipFile(child) as zf:
                    names = [n for n in zf.namelist() if n.lower().endswith(".pdf")]
            else:
                names = [str(p.relative_to(child)) for p in child.rglob("*.pdf")]
            print(f"{category}/{child.name}: {', '.join(names) if names else '无'}")


if __name__ == "__main__":
    main()
