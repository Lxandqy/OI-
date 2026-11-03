from __future__ import annotations

import shutil
from pathlib import Path


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\CSP-J\CSP-J秋日训练卷")


def main() -> None:
    source = ROOT / "下发文件"
    target = ROOT / "下发"
    if source.is_dir():
        if target.exists():
            shutil.rmtree(target)
        source.rename(target)
    for slug in ("harvest", "pairs", "rail", "visit"):
        for number in (1, 2):
            for suffix in (".in", ".ans"):
                path = target / slug / f"{slug}{number}{suffix}"
                if path.exists():
                    path.unlink()
    print("fixed", ROOT)


if __name__ == "__main__":
    main()
