from __future__ import annotations

import json
import re
from pathlib import Path

from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def sections(text: str) -> list[tuple[str, str]]:
    matches = list(re.finditer(r"^#\s+(.+)$", text, re.M))
    out = []
    for i, match in enumerate(matches):
        end = matches[i + 1].start() if i + 1 < len(matches) else len(text)
        out.append((match.group(1).strip(), text[match.start():end]))
    return out


def has_problem_section(text: str, slug: str) -> bool:
    return any(slug in title for title, _ in sections(text))


for category in ("CSP-J", "NOIP"):
    for child in sorted((ROOT / category).iterdir()):
        if not (child.is_dir() or child.suffix.lower() == ".zip"):
            continue
        pkg = Package(child)
        try:
            names = pkg.names
            sol_name = next(
                (
                    n
                    for n in ("solution.md", "总题解.md", "题解.md")
                    if n in names
                ),
                None,
            )
            if not sol_name:
                continue
            sol = pkg.read_text(sol_name)
            print(f"## {category} / {child.name}")
            for title, body in sections(sol):
                if not re.search(r"[（(][a-z0-9][a-z0-9_-]*[）)]", title):
                    continue
                if "题解" in title and "（" not in title:
                    continue
                tokens = {
                    "题目/题意": len(re.findall(r"题意|题目", body)),
                    "测试点/保证": len(re.findall(r"测试点|保证", body)),
                    "部分/子任务": len(re.findall(r"部分分|子任务|subtask", body, re.I)),
                    "复杂度": len(re.findall(r"复杂度|O\(", body)),
                    "cpp": len(re.findall(r"```cpp", body)),
                }
                print(f"- {title}: {tokens}")
        finally:
            pkg.close()
