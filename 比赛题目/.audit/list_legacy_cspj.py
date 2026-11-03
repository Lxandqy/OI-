from __future__ import annotations

import re
from pathlib import Path


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\text\CSP-J")


def main() -> None:
    for pkg in sorted(ROOT.iterdir()):
        if not pkg.is_dir() or not any(p.name.startswith("T") for p in pkg.iterdir()):
            continue
        print("\n###", pkg.name)
        for problem in sorted(p for p in pkg.iterdir() if p.is_dir()):
            statement = problem / "statement.md"
            if not statement.is_file():
                continue
            text = statement.read_text(encoding="utf-8")
            h1 = re.search(r"^#\s+(.+)$", text, re.M)
            input_format = re.search(
                r"^##\s*输入格式\s*$(.*?)(?=^##|\Z)", text, re.M | re.S
            )
            sample = re.search(r"^###\s*样例 1\s*$(.*?)(?=^###|\Z)", text, re.M | re.S)
            print("\n--", problem.name, "--")
            print("TITLE:", h1.group(1).strip() if h1 else "?")
            if input_format:
                print("INPUT:", re.sub(r"\n+", " | ", input_format.group(1).strip())[:600])
            if sample:
                print("SAMPLE1:", re.sub(r"\n+", " | ", sample.group(1).strip())[:300])


if __name__ == "__main__":
    main()
