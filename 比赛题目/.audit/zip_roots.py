from __future__ import annotations

import sys
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import open_zip

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def main() -> None:
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not child.is_file() or child.suffix.lower() != ".zip":
                continue
            with open_zip(child) as zf:
                names = [n for n in zf.namelist() if n and not n.endswith("/")]
            roots = sorted({n.split("/", 1)[0] for n in names})
            top_files = [n for n in names if "/" not in n]
            print(f"{category}/{child.name}")
            print(f"  roots={roots[:8]}  top_files={top_files[:8]}  members={len(names)}")


if __name__ == "__main__":
    main()
