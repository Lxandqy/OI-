from __future__ import annotations

import re
from pathlib import Path

from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
TARGETS = [
    ROOT / "CSP-J" / "CSP-J模拟赛第一套.zip",
    ROOT / "NOIP" / "第一套 NOIP 模拟卷.zip",
    ROOT / "CSP-J" / "第四套_V3.8_完整重构包.zip",
]


for path in TARGETS:
    pkg = Package(path)
    try:
        print("##", path.name)
        top = sorted({name.split("/", 1)[0] for name in pkg.names})
        print("top:", top)
        for name in pkg.names:
            if "/data/" in "/" + name + "/":
                continue
            if "attachment" not in name and "下发" not in name and "样例" not in name and not name.endswith((".zip", "config")):
                continue
            if name.endswith((".in", ".ans", ".out", ".zip", "config")):
                print(name)
        if path.name.startswith("第四套"):
            nested = pkg.nested_zip("T1/attachment.zip")
            if nested is not None:
                print("T1/attachment.zip members:", nested.namelist())
                nested.close()
            nested = pkg.nested_zip("T1/data.zip")
            if nested is not None:
                print("T1/data.zip members:", nested.namelist())
                nested.close()
    finally:
        pkg.close()
