import os
import shutil
import sys
import zipfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")

root = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
backup = root / ".audit" / "backup_textnorm"


def normalize(data: bytes) -> bytes:
    return (
        data.replace(b"\r\r\n", b"\n")
        .replace(b"\r\n", b"\n")
        .replace(b"\r", b"\n")
    )


def backup_bytes(package: str, name: str, data: bytes) -> None:
    target = backup / package / Path(name)
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(data)


def fix_zip(package: Path, names: set[str]) -> None:
    temporary = package.with_suffix(".zip.tmp")
    with zipfile.ZipFile(package) as source, zipfile.ZipFile(
        temporary, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=6
    ) as target:
        for info in source.infolist():
            data = source.read(info.filename)
            if info.filename in names:
                backup_bytes(package.name, info.filename, data)
                data = normalize(data)
            target.writestr(info, data)
    with zipfile.ZipFile(temporary) as check:
        bad = check.testzip()
        if bad is not None:
            raise RuntimeError(f"corrupt member: {bad}")
    os.replace(temporary, package)


def fix_dir(package: Path, names: set[str]) -> None:
    for name in sorted(names):
        path = package / Path(name)
        data = path.read_bytes()
        backup_bytes(package.name, name, data)
        path.write_bytes(normalize(data))


def main() -> None:
    targets = {
        root / "NOIP" / "NOIP模拟赛-宴会名册": {
            "代码/invite.cpp",
            "代码/river.cpp",
            "代码/trio.cpp",
        },
        root / "NOIP" / "第一套 NOIP 模拟卷.zip": {"总题解.md"},
        root / "NOIP" / "第三套 NOIP 模拟赛": {
            "代码/circle.cpp",
            "代码/relay.cpp",
            "代码/watch.cpp",
        },
    }
    for package, names in targets.items():
        if package.is_file():
            fix_zip(package, names)
        else:
            fix_dir(package, names)
        print("normalized", package.name)


if __name__ == "__main__":
    main()
