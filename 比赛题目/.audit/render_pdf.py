from __future__ import annotations

import subprocess
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit")
PDF = ROOT / "pdf"
OUT = ROOT / "pdf_png"
PDFTOPPM = Path(
    r"C:\Users\Administrator\.cache\codex-runtimes\codex-primary-runtime\dependencies\native\poppler\Library\bin\pdftoppm.exe"
)
SKILL = Path(r"C:\Users\Administrator\.codex\skills\oi-contest-authoring")

TASKS = [
    (SKILL / "references" / "statement-reference.pdf", "reference", [1, 2, 4, 8]),
    (PDF / "CSP-J模拟赛第一套" / "statement.pdf", "cspj1", [1, 2, 9]),
    (PDF / "CSP-J秋日训练卷" / "statement.pdf", "autumn", [1, 2, 9]),
    (PDF / "CSP-J金桂第一试" / "statement.pdf", "gold", [1, 2, 9]),
    (PDF / "第七套_V3.8_完整重构包" / "题目汇总.pdf", "legacy7_summary", [1]),
    (PDF / "第七套_V3.8_完整重构包" / "T1" / "statement.pdf", "legacy7_t1", [1]),
    (PDF / "第一套_NOIP_模拟卷" / "statement.pdf", "noip1", [1, 2]),
    (PDF / "第二套_NOIP_模拟卷" / "statement.pdf", "noip2", [1, 2]),
]


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    for source, key, pages in TASKS:
        for page in pages:
            prefix = OUT / f"{key}_p{page}"
            cmd = [
                str(PDFTOPPM),
                "-png",
                "-r",
                "80",
                "-f",
                str(page),
                "-l",
                str(page),
                str(source),
                str(prefix),
            ]
            subprocess.run(cmd, check=True, capture_output=True)
        print(key, "ok")


if __name__ == "__main__":
    main()
