from __future__ import annotations

import io
import json
import re
import sys
import zipfile
from pathlib import Path

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
AUDIT = ROOT / ".audit"
sys.path.insert(0, str(AUDIT))
sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")

from audit_v3103 import Package
from oi_common import extract_samples, split_problems


def text_encoding(raw: bytes) -> str:
    try:
        raw.decode("utf-8")
        return "UTF-8"
    except UnicodeDecodeError:
        try:
            raw.decode("gbk")
            return "GBK"
        except UnicodeDecodeError:
            return "?"


def nested_config(data: zipfile.ZipFile) -> str:
    for name in ("config",) + tuple(
        n for n in data.namelist() if n.endswith("/config")
    ):
        if name in data.namelist():
            return data.read(name).decode("utf-8", errors="replace")
    return ""


def inspect(path: Path) -> dict:
    pkg = Package(path)
    try:
        names = pkg.names
        statement_name = next(
            n for n in ("总题面.md", "statement.md") if n in names
        )
        statement = pkg.read_text(statement_name)
        parts = split_problems(statement)
        data = {}
        for name in names:
            match = re.fullmatch(r"data/([a-z0-9_-]+)\.zip", name)
            if not match:
                continue
            slug = match.group(1)
            nested = pkg.nested_zip(name)
            assert nested is not None
            try:
                members = [n for n in nested.namelist() if not n.endswith("/")]
                cfg = nested_config(nested)
                data[slug] = {
                    "members": len(members),
                    "config": cfg.splitlines()[0] if cfg else "",
                    "tests": len(
                        [
                            n
                            for n in members
                            if re.fullmatch(r"(?:.*/)?\d+\.in", n)
                        ]
                    ),
                }
            finally:
                nested.close()
        if not data:
            for directory in sorted(p.name for p in (path / "data").glob("*")) if path.is_dir() else []:
                base = path / "data" / directory
                data[directory] = {
                    "members": sum(1 for _ in base.rglob("*") if _.is_file()),
                    "config": (base / "config").read_text(encoding="utf-8").splitlines()[0]
                    if (base / "config").is_file()
                    else "",
                    "tests": sum(1 for _ in base.glob("*.in")),
                }
        samples = {}
        for slug, body in parts.items():
            try:
                samples[slug] = sorted(extract_samples(body))
            except Exception as exc:
                samples[slug] = f"ERROR: {exc}"
        std = {}
        for name in names:
            if re.fullmatch(r"代码/[a-z0-9_-]+\.cpp", name):
                raw = (
                    pkg._zip.read(pkg._originals[name])
                    if pkg.is_zip
                    else (path / name).read_bytes()
                )
                std[Path(name).stem] = text_encoding(raw)
            elif re.fullmatch(r"std/[a-z0-9_-]+/[a-z0-9_-]+\.cpp", name):
                raw = (
                    pkg._zip.read(pkg._originals[name])
                    if pkg.is_zip
                    else (path / name).read_bytes()
                )
                std[Path(name).stem] = text_encoding(raw)
        return {
            "package": path.name,
            "is_zip": pkg.is_zip,
            "names": names,
            "slugs": sorted(data),
            "inline": samples,
            "data": data,
            "std_encoding": std,
        }
    finally:
        pkg.close()


def main() -> None:
    records = []
    for path in sorted((ROOT / "NOIP").iterdir()):
        if path.is_dir() or path.suffix.lower() == ".zip":
            record = inspect(path)
            records.append(record)
            print("\n##", record["package"])
            print("slugs:", record["slugs"])
            print("inline:", record["inline"])
            print("data:", record["data"])
            print("std:", record["std_encoding"])
            print("root:", [n for n in record["names"] if "/" not in n])
    (AUDIT / "noip_inspect.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )


if __name__ == "__main__":
    main()
