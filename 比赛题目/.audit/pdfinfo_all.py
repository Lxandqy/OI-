from __future__ import annotations

import subprocess
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\pdf")
PDFINFO = Path(
    r"C:\Users\Administrator\.cache\codex-runtimes\codex-primary-runtime\dependencies\native\poppler\Library\bin\pdfinfo.exe"
)


def main() -> None:
    for path in sorted(ROOT.rglob("*.pdf")):
        proc = subprocess.run(
            [str(PDFINFO), str(path)],
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
        )
        pages = ""
        for line in proc.stdout.splitlines():
            if line.startswith("Pages:"):
                pages = line.split(":", 1)[1].strip()
                break
        print(f"{pages:>4}  {path.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
