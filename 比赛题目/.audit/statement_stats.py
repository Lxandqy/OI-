from __future__ import annotations

import json
import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(
    0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts"
)

from audit_v3103 import Package, first_name
from oi_common import extract_samples, split_problems

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
TEXT = ROOT / ".audit" / "text"


def main() -> None:
    rows = []
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                names = pkg.names
                legacy = sorted({n.split("/", 1)[0] for n in names if re.match(r"T\d+/", n)})
                record = {"category": category, "package": child.stem if child.is_file() else child.name}
                if legacy:
                    record["problems"] = []
                    for slug in legacy:
                        text = (TEXT / category / child.name / slug / "statement.md").read_text(
                            encoding="utf-8", errors="replace"
                        )
                        record["problems"].append(
                            {
                                "slug": slug,
                                "inline": len(re.findall(r"###\s*样例\s*\d+", text)),
                                "refs": sorted(
                                    {int(x) for x in re.findall(r"【样例\s*(\d+)】", text)}
                                ),
                                "old_sections": re.findall(r"^##\s+(.+)$", text, re.M)[:5],
                            }
                        )
                else:
                    name = first_name(names, ["statement.md", "总题面.md", "题面.md"])
                    text = (TEXT / category / child.name / name).read_text(
                        encoding="utf-8", errors="replace"
                    )
                    try:
                        parts = split_problems(text)
                    except ValueError as exc:
                        record["error"] = str(exc)
                        parts = {}
                    record["problems"] = []
                    for slug, body in parts.items():
                        try:
                            samples = sorted(extract_samples(body))
                        except ValueError:
                            samples = []
                        refs = sorted(
                            {int(x) for x in re.findall(r"【样例\s*(\d+)】", body)}
                        )
                        record["problems"].append(
                            {"slug": slug, "inline": samples, "refs": refs}
                        )
                rows.append(record)
            finally:
                pkg.close()
    print(json.dumps(rows, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
