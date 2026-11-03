from __future__ import annotations

import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
TEXT = ROOT / ".audit" / "text"


def main() -> None:
    raw = sys.argv[1:]
    tokens = [item for item in raw if not item.isdigit()]
    limit = next((int(item) for item in raw if item.isdigit()), 40)
    paths = [
        path
        for path in sorted(TEXT.rglob("*.md"))
        if all(token in str(path) for token in tokens)
    ]
    if not paths:
        print("no match for", tokens)
        for path in sorted(TEXT.rglob("statement.md")):
            print("candidate:", path.relative_to(TEXT))
    for path in paths:
        if not path.is_file():
            continue
        print("=" * 100)
        print(path.relative_to(TEXT))
        text = path.read_text(encoding="utf-8", errors="replace").splitlines()
        for line in text[:limit]:
            print(line)


if __name__ == "__main__":
    main()
