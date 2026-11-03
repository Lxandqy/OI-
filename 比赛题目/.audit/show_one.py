from __future__ import annotations

import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
TEXT = ROOT / ".audit" / "text"

MAP = {
    "archive": ROOT,
    "report": ROOT / "验收报告_V3.10.3.md",
    "cspj1": TEXT / "CSP-J" / "CSP-J模拟赛第一套.zip",
    "autumn": TEXT / "CSP-J" / "CSP-J秋日训练卷",
    "gold": TEXT / "CSP-J" / "CSP-J金桂第一试",
    "noip1": TEXT / "NOIP" / "第一套 NOIP 模拟卷.zip",
    "noip2": TEXT / "NOIP" / "第二套 NOIP 模拟卷",
    "legacy7": TEXT / "CSP-J" / "第七套_V3.8_完整重构包.zip",
    "legacy5": TEXT / "CSP-J" / "第五套_V3.8_完整重构包.zip",
    "legacy6": TEXT / "CSP-J" / "第六套_V3.8_完整重构包.zip",
    "legacy4": TEXT / "CSP-J" / "第四套_V3.8_完整重构包.zip",
    "cc": TEXT / "NOIP" / "NOIP模拟赛-第二套-CC版.zip",
    "feast": TEXT / "NOIP" / "NOIP模拟赛-宴会名册",
    "noip3": TEXT / "NOIP" / "第三套 NOIP 模拟赛",
    "noip4": TEXT / "NOIP" / "第四套 NOIP 模拟赛",
    "noip5": TEXT / "NOIP" / "第五套 NOIP 模拟赛.zip",
    "noip6": TEXT / "NOIP" / "第六套 NOIP 模拟赛",
}


def main() -> None:
    key = sys.argv[1] if len(sys.argv) > 1 else "cspj1"
    name = sys.argv[2] if len(sys.argv) > 2 else ("归档说明.md" if key == "archive" else "statement.md")
    limit = int(sys.argv[3]) if len(sys.argv) > 3 else 80
    path = MAP[key] if MAP[key].is_file() else MAP[key] / name
    if not path.is_file():
        print("missing", path)
        for item in sorted(MAP[key].iterdir()):
            print(" ", item.name)
        return
    print("=" * 100)
    print(path)
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines()[:limit]:
        print(line)


if __name__ == "__main__":
    main()
