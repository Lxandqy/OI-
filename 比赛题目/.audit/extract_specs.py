from __future__ import annotations

import re
import sys
from pathlib import Path

sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")
from oi_common import split_problems


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\text\NOIP")


def section(body: str, name: str) -> str:
    match = re.search(
        r"^#{2,4}\s*【" + re.escape(name) + r"】\s*$(.*?)(?=^#{2,4}\s*【|^#\s|\Z)",
        body,
        re.M | re.S,
    )
    return match.group(1).strip() if match else ""


def main() -> None:
    for pkg in sorted(ROOT.iterdir()):
        statement = next(
            (f for f in pkg.glob("*.md") if f.name in ("statement.md", "总题面.md")),
            None,
        )
        if statement is None:
            continue
        text = statement.read_text(encoding="utf-8")
        try:
            parts = split_problems(text)
        except Exception as exc:
            print(pkg.name, "PARSE", exc)
            continue
        print("\n###", pkg.name)
        for slug, body in parts.items():
            print("\n--", slug, "--")
            print("INPUT:", re.sub(r"\n+", " | ", section(body, "输入格式"))[:800])
            print("RANGE:", re.sub(r"\n+", " | ", section(body, "数据范围"))[:700])


if __name__ == "__main__":
    main()
