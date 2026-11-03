from __future__ import annotations

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")
from audit_v3103 import Package
from oi_common import extract_samples, split_problems


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def main() -> None:
    for path in sorted((ROOT / "NOIP").iterdir()):
        if not (path.is_dir() or path.suffix.lower() == ".zip"):
            continue
        pkg = Package(path)
        print("\n##", path.name)
        try:
            statement_name = next(
                n for n in ("总题面.md", "statement.md") if n in pkg.names
            )
            parts = split_problems(pkg.read_text(statement_name))
            for slug in sorted(parts):
                samples = extract_samples(parts[slug])
                candidates = [
                    n
                    for n in pkg.names
                    if re.fullmatch(rf"(?:代码|std)/{re.escape(slug)}\.cpp", n)
                    or re.fullmatch(
                        rf"std/{re.escape(slug)}/{re.escape(slug)}\.cpp", n
                    )
                ]
                if not candidates:
                    print(slug, "STD MISSING", "inline", sorted(samples))
                    continue
                raw = (
                    pkg._zip.read(pkg._originals[candidates[0]])
                    if pkg.is_zip
                    else (path / candidates[0]).read_bytes()
                )
                text = raw.decode("utf-8", errors="replace")
                io = "file" if "freopen" in text else "std"
                print(slug, io, "inline", sorted(samples), candidates[0])
        finally:
            pkg.close()


if __name__ == "__main__":
    main()
