from __future__ import annotations

import io
import re
import shutil
import sys
import zipfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
STAGED = ROOT / ".audit" / "staged"
SAMPLES = ROOT / ".audit" / "samples"
BUILD = ROOT / ".audit" / "package_staging"
BUILD_ZIP = ROOT / ".audit" / "package_staging_zip"
BACKUPS = ROOT / ".audit" / "backup_dirs"


PACKAGES = {
    "meeting": {
        "source": "NOIP模拟赛-宴会名册",
        "container": "dir",
        "data": "zip",
        "samples": {"invite": [2], "river": [2], "trio": [2], "roads": [2]},
    },
    "third": {
        "source": "第三套 NOIP 模拟赛",
        "container": "dir",
        "data": "zip",
        "samples": {
            "relay": [2],
            "watch": [2],
            "palpath": [2],
            "circle": [3],
        },
    },
    "fourth": {
        "source": "第四套 NOIP 模拟赛",
        "container": "dir",
        "data": "zip",
        "samples": {"cut": [4], "region": [4], "track": [4], "bits": [4]},
    },
    "sixth": {
        "source": "第六套 NOIP 模拟赛",
        "container": "dir",
        "data": "zip",
        "samples": {
            "product": [3],
            "disk": [3],
            "gcdforest": [2],
            "joint": [2],
        },
    },
    "second": {
        "source": "第二套 NOIP 模拟卷",
        "container": "dir",
        "data": "dir",
        "limits": {
            "repair": (2, 256),
            "patrol": (3, 512),
            "compile": (3, 256),
            "orcost": (2, 256),
        },
        "samples": {"repair": [4], "patrol": [4], "compile": [4], "orcost": [4]},
    },
    "cc": {
        "source": "NOIP模拟赛-第二套-CC版.zip",
        "container": "zip",
        "data": "zip",
        "samples": {"lamp": [3], "liar": [4], "bridge": [3], "park": [3]},
    },
    "fifth": {
        "source": "第五套 NOIP 模拟赛.zip",
        "container": "zip",
        "data": "zip",
        "samples": {"cross": [3], "password": [3], "spider": [3], "tree": [3]},
    },
    "first": {
        "source": "第一套 NOIP 模拟卷.zip",
        "container": "zip",
        "data": "dir",
        "limits": {
            "xor4": (2, 256),
            "triplet": (2, 256),
            "menu": (2, 256),
            "logic": (2, 256),
        },
        "samples": {"xor4": [4], "triplet": [3], "menu": [4], "logic": [4]},
    },
}


def decode_source(raw: bytes) -> str:
    for encoding in ("utf-8", "gbk"):
        try:
            return raw.decode(encoding)
        except UnicodeDecodeError:
            pass
    raise UnicodeDecodeError("utf-8", raw, 0, 1, "unknown source encoding")


def read_member(pkg: Package, name: str) -> bytes:
    if pkg.is_zip:
        assert pkg._zip is not None
        return pkg._zip.read(pkg._originals[name])
    return (pkg.path / Path(name)).read_bytes()


def find_std(pkg: Package, slug: str) -> str:
    for name in (f"代码/{slug}.cpp", f"std/{slug}/{slug}.cpp", f"std/{slug}.cpp"):
        if name in pkg.names:
            return name
    raise FileNotFoundError(f"{pkg.path}: no std for {slug}")


def source_data_files(pkg: Package, slug: str) -> dict[str, bytes]:
    result: dict[str, bytes] = {}
    prefix = f"data/{slug}/"
    for name in pkg.names:
        if not name.startswith(prefix):
            continue
        tail = name[len(prefix):]
        if re.fullmatch(r"\d+\.(?:in|out)", tail):
            result[Path(tail).name] = read_member(pkg, name)
    if not result:
        raise FileNotFoundError(f"{pkg.path}: no data directory for {slug}")
    tests = sorted(int(Path(name).stem) for name in result if name.endswith(".in"))
    if tests != list(range(1, len(tests) + 1)):
        raise ValueError(f"{slug}: hidden inputs are not numbered 1..N")
    for index in tests:
        if f"{index}.out" not in result:
            raise ValueError(f"{slug}: missing {index}.out")
    return result


def build_data_zip(
    pkg: Package,
    slug: str,
    data_mode: str,
    limit: tuple[float, int] | None,
) -> io.BytesIO:
    output = io.BytesIO()
    if data_mode == "zip":
        name = f"data/{slug}.zip"
        if name not in pkg.names:
            raise FileNotFoundError(f"{pkg.path}: no {name}")
        output.write(read_member(pkg, name))
        output.seek(0)
        with zipfile.ZipFile(output) as zf:
            config = zf.read("config").decode("utf-8")
            n = sum(
                bool(re.fullmatch(r"test \d+\.in \d+\.out", line.strip()))
                for line in config.splitlines()
            )
            if n == 0 or 100 % n:
                raise ValueError(f"{slug}: bad config test count")
        output.seek(0)
        return output
    if limit is None:
        raise ValueError(f"{slug}: missing time/memory limit")
    files = source_data_files(pkg, slug)
    tests = sorted(int(Path(name).stem) for name in files if name.endswith(".in"))
    seconds, memory_mib = limit
    config = f"-p {100 // len(tests)} -t {seconds} -m {memory_mib * 1024}\n"
    config += "".join(f"test {index}.in {index}.out\n" for index in tests)
    with zipfile.ZipFile(output, "w", zipfile.ZIP_DEFLATED) as zf:
        for index in tests:
            zf.writestr(f"{index}.in", files[f"{index}.in"])
            zf.writestr(f"{index}.out", files[f"{index}.out"])
        zf.writestr("config", config)
    output.seek(0)
    return output


def build_sample_zip(key: str, slug: str, numbers: list[int]) -> io.BytesIO:
    output = io.BytesIO()
    with zipfile.ZipFile(output, "w", zipfile.ZIP_DEFLATED) as zf:
        for number in numbers:
            source = SAMPLES / key / slug
            input_path = source / f"{slug}{number}.in"
            answer_path = source / f"{slug}{number}.ans"
            if not input_path.is_file() or not answer_path.is_file():
                raise FileNotFoundError(f"missing sample pair: {input_path}")
            if not answer_path.read_text(encoding="ascii", errors="replace").strip():
                raise ValueError(f"empty sample answer: {answer_path}")
            zf.write(input_path, f"{slug}/{slug}{number}.in")
            zf.write(answer_path, f"{slug}/{slug}{number}.ans")
    output.seek(0)
    return output


def write_dir_package(key: str, config: dict, pkg: Package) -> Path:
    target = BUILD / key
    if target.exists():
        shutil.rmtree(target)
    target.mkdir(parents=True)
    (target / "总题面.md").write_bytes((STAGED / key / "总题面.md").read_bytes())
    (target / "总题解.md").write_bytes((STAGED / key / "总题解.md").read_bytes())
    (target / "data").mkdir()
    (target / "代码").mkdir()
    (target / "下发").mkdir()
    slugs = list(config["samples"])
    for slug in slugs:
        data_zip = build_data_zip(
            pkg,
            slug,
            config["data"],
            config.get("limits", {}).get(slug),
        )
        (target / "data" / f"{slug}.zip").write_bytes(data_zip.getvalue())
        code = decode_source(read_member(pkg, find_std(pkg, slug)))
        (target / "代码" / f"{slug}.cpp").write_text(code, encoding="utf-8")
        sample_zip = build_sample_zip(key, slug, config["samples"][slug])
        (target / "下发" / f"{slug}.zip").write_bytes(sample_zip.getvalue())
    return target


def write_zip_package(key: str, config: dict, pkg: Package) -> Path:
    target = BUILD_ZIP / f"{key}.zip"
    target.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(target, "w", zipfile.ZIP_DEFLATED) as out:
        out.writestr("总题面.md", (STAGED / key / "总题面.md").read_bytes())
        out.writestr("总题解.md", (STAGED / key / "总题解.md").read_bytes())
        for slug, numbers in config["samples"].items():
            data_zip = build_data_zip(
                pkg,
                slug,
                config["data"],
                config.get("limits", {}).get(slug),
            )
            out.writestr(f"data/{slug}.zip", data_zip.getvalue())
            code = decode_source(read_member(pkg, find_std(pkg, slug)))
            out.writestr(f"代码/{slug}.cpp", code.encode("utf-8"))
            sample_zip = build_sample_zip(key, slug, numbers)
            out.writestr(f"下发/{slug}.zip", sample_zip.getvalue())
    return target


def backup_and_replace_dir(target: Path, stage: Path) -> None:
    backup = BACKUPS / target.name
    if backup.exists():
        raise FileExistsError(backup)
    backup.parent.mkdir(parents=True, exist_ok=True)
    target.rename(backup)
    try:
        stage.rename(target)
    except Exception:
        backup.rename(target)
        raise


def main() -> None:
    BUILD.mkdir(parents=True, exist_ok=True)
    BUILD_ZIP.mkdir(parents=True, exist_ok=True)
    wanted = set(sys.argv[1:]) if len(sys.argv) > 1 else set(PACKAGES)
    for key, config in PACKAGES.items():
        if key not in wanted:
            continue
        source = ROOT / "NOIP" / config["source"]
        pkg = Package(source)
        try:
            stage = (
                write_dir_package(key, config, pkg)
                if config["container"] == "dir"
                else write_zip_package(key, config, pkg)
            )
        finally:
            pkg.close()
        if config["container"] == "dir":
            backup_and_replace_dir(source, stage)
        else:
            if not source.is_file():
                raise ValueError(f"expected ZIP source: {source}")
            stage.replace(source)
        print(f"{key}: {source}")


if __name__ == "__main__":
    main()
