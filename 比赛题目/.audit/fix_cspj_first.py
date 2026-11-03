from __future__ import annotations

import shutil
import sys
import zipfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import open_zip


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
SRC = ROOT / "CSP-J" / "CSP-J模拟赛第一套.zip"
BACKUP = ROOT / ".audit" / "backup_zips" / SRC.name
TMP = ROOT / ".audit" / "work" / "cspj_first"


def main() -> None:
    if not BACKUP.exists():
        BACKUP.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(SRC, BACKUP)
    if TMP.exists():
        shutil.rmtree(TMP)
    TMP.mkdir(parents=True)
    with open_zip(SRC) as zf:
        for name in zf.namelist():
            if name.endswith("/"):
                continue
            clean = name.split("/", 1)[1] if name.startswith("第一套/") else name
            target = TMP / clean
            target.parent.mkdir(parents=True, exist_ok=True)
            data = zf.read(name)
            if clean.startswith("std/") and clean.endswith(".cpp"):
                data = data.decode("gbk").encode("utf-8")
            target.write_bytes(data)
    # The outer directory carried no information; rebuild the ZIP with the
    # standard package root.
    temp_zip = TMP.with_suffix(".new.zip")
    with zipfile.ZipFile(temp_zip, "w", zipfile.ZIP_DEFLATED) as zf:
        for path in sorted(TMP.rglob("*")):
            if path.is_file():
                zf.write(path, path.relative_to(TMP).as_posix())
    shutil.move(str(temp_zip), str(SRC))
    print("fixed", SRC)


if __name__ == "__main__":
    main()
