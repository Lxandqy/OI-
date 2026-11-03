from __future__ import annotations

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def main() -> None:
    for source in sys.argv[1:]:
        path = Path(source)
        pkg = Package(path)
        try:
            names = pkg.names
            print(f"\n## {path}")
            roots = sorted({name.split("/", 1)[0] for name in names})
            print("roots:", roots)
            if path.name.startswith("第一套"):
                print("all names:")
                for name in names:
                    print(" ", name)
                continue
            for slug in sorted(
                {
                    Path(name).stem
                    for name in names
                    if re.fullmatch(r"(?:代码|std)/[^/]+\.cpp", name)
                    or re.fullmatch(r"std/[^/]+/[^/]+\.cpp", name)
                }
            ):
                print(f"[{slug}]")
                hits = [
                    name
                    for name in names
                    if f"/{slug}." in name
                    or name.endswith(f"/{slug}.cpp")
                    or name.split("/")[0] == slug
                ]
                for name in hits[:18]:
                    print(" ", name)
                if len(hits) > 18:
                    print("  ...", len(hits), "matching names")
        finally:
            pkg.close()


if __name__ == "__main__":
    main()
