from __future__ import annotations

import shutil
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))

from audit_v3103 import Package

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit" / "pdf"


def main() -> None:
    if OUT.exists():
        shutil.rmtree(OUT)
    OUT.mkdir(parents=True)
    for category in ("CSP-J", "NOIP"):
        for child in sorted((ROOT / category).iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            key = (child.stem if child.is_file() else child.name).replace(" ", "_")
            try:
                for name in pkg.names:
                    if not name.lower().endswith(".pdf"):
                        continue
                    target = OUT / key / Path(name)
                    target.parent.mkdir(parents=True, exist_ok=True)
                    if child.is_file():
                        assert pkg._zip is not None
                        target.write_bytes(pkg._zip.read(pkg._originals[name]))
                    else:
                        shutil.copyfile(child / Path(name), target)
            finally:
                pkg.close()
    for path in sorted(OUT.rglob("*.pdf")):
        print(path.relative_to(OUT))


if __name__ == "__main__":
    main()
