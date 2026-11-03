from __future__ import annotations

import io
import os
import zipfile
from pathlib import Path


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
NOIP = ROOT / "NOIP"
TMP = ROOT / ".audit" / "zip_normalize_tmp"


def normalize_lines(data: bytes) -> bytes:
    return data.replace(b"\r\r\n", b"\n").replace(b"\r\n", b"\n")


def rewrite_nested(data: bytes) -> bytes:
    output = io.BytesIO()
    with zipfile.ZipFile(io.BytesIO(data)) as source:
        with zipfile.ZipFile(output, "w", zipfile.ZIP_DEFLATED) as target:
            for item in source.infolist():
                payload = source.read(item.filename)
                if item.filename.lower().endswith((".in", ".ans", ".out")):
                    payload = normalize_lines(payload)
                target.writestr(item.filename, payload)
    return output.getvalue()


def rewrite_sample_zip(path: Path) -> None:
    path.write_bytes(rewrite_nested(path.read_bytes()))


def rewrite_package_zip(path: Path) -> None:
    TMP.mkdir(parents=True, exist_ok=True)
    temp = TMP / path.name
    with zipfile.ZipFile(path) as source:
        with zipfile.ZipFile(temp, "w", zipfile.ZIP_DEFLATED) as target:
            for item in source.infolist():
                payload = source.read(item.filename)
                if item.filename.startswith("下发/") and item.filename.endswith(".zip"):
                    payload = rewrite_nested(payload)
                target.writestr(item, payload)
    os.replace(temp, path)


def main() -> None:
    for package in sorted(NOIP.iterdir()):
        if package.is_dir():
            for sample_zip in sorted((package / "下发").glob("*.zip")):
                rewrite_sample_zip(sample_zip)
                print("dir", sample_zip)
        elif package.suffix.lower() == ".zip":
            rewrite_package_zip(package)
            print("zip", package)


if __name__ == "__main__":
    main()
