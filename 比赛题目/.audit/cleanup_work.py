from __future__ import annotations

import shutil
from pathlib import Path


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
AUDIT = (ROOT / ".audit").resolve()


def safe_remove(name: str) -> None:
    target = (AUDIT / name).resolve()
    if not target.is_relative_to(AUDIT) or target == AUDIT:
        raise SystemExit(f"unsafe cleanup target: {target}")
    if target.exists():
        print("remove", target)
        shutil.rmtree(target)


for directory in ("samples", "sample_build"):
    safe_remove(directory)
