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
            headings = re.findall(r"^(#{2,3})\s+(.+)$", text, re.M)
            fences = len(re.findall(r"^```", text, re.M)) // 2
            print(f"\n-- {problem.name}: fences={fences}")
            for level, title in headings:
                print("  ", level, title)


if __name__ == "__main__":
    main()
