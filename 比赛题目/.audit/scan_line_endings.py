import sys
import zipfile
from pathlib import Path

root = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def scan_bytes(name: str, data: bytes) -> bool:
    if name.lower().endswith((".md", ".cpp", ".h")):
        return b"\r\r\n" in data
    return False


for category in ("CSP-J", "NOIP"):
    for package in sorted((root / category).iterdir()):
        hits = []
        if package.is_file():
            with zipfile.ZipFile(package) as zf:
                for name in zf.namelist():
                    if scan_bytes(name, zf.read(name)):
                        hits.append(name)
        else:
            for path in package.rglob("*"):
                if path.is_file() and scan_bytes(path.name, path.read_bytes()):
                    hits.append(path.relative_to(package).as_posix())
        if hits:
            print(category, package.name, len(hits))
            for name in hits:
                print("  ", name)
