from __future__ import annotations

import json
import os
import subprocess
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))

import audit_details as ad
from audit_v3103 import Package, first_name

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"
PUBLIC = OUT / "public"
STAGE = OUT / "std_stage"
CHECK = Path(
    r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts\check_md.py"
)
PY = sys.executable
GXX = ROOT / ".audit" / "tools" / "w64devkit" / "w64devkit" / "bin" / "g++.exe"


def infer(pkg: Package) -> tuple[str, list[str]]:
    names = pkg.names
    noip_nested = any(n.startswith("data/") and n.endswith(".zip") for n in names)
    if noip_nested:
        return "noip_zip", sorted(
            Path(n).stem for n in names if n.startswith("data/") and n.endswith(".zip")
        )
    data_dirs = sorted(
        {n.split("/", 2)[1] for n in names if n.startswith("data/") and n.count("/") >= 2}
    )
    slugs = data_dirs or sorted(
        {Path(n).stem for n in names if n.startswith("std/") and n.endswith(".cpp")}
    )
    return "generic_dir", slugs


def std_name(pkg: Package, slug: str) -> str | None:
    for candidate in (f"std/{slug}/{slug}.cpp", f"std/{slug}.cpp", f"代码/{slug}.cpp"):
        if candidate in pkg.names:
            return candidate
    return None


def read_utf8_source(data: bytes) -> bytes:
    for encoding in ("utf-8-sig", "gbk"):
        try:
            return data.decode(encoding).encode("utf-8")
        except UnicodeDecodeError:
            continue
    return data.decode("utf-8", errors="replace").encode("utf-8")


def run_check(
    statement: Path,
    solution: Path,
    standard: list[tuple[str, Path]],
    io: str,
    log: Path,
) -> dict:
    cmd = [
        str(PY),
        str(CHECK),
        "--statement",
        str(statement),
        "--solution",
        str(solution),
        "--io",
        io,
        "--compile",
        str(GXX) + " -O2 -std=c++14",
    ]
    for slug, path in standard:
        cmd += ["--std", f"{slug}={path}"]
    env = dict(os.environ)
    env["PYTHONIOENCODING"] = "utf-8"
    proc = subprocess.run(
        cmd,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        env=env,
    )
    log.parent.mkdir(parents=True, exist_ok=True)
    log.write_text(
        "$ " + " ".join(cmd) + "\n\nSTDOUT:\n" + proc.stdout + "\nSTDERR:\n" + proc.stderr,
        encoding="utf-8",
    )
    tail = (proc.stdout + proc.stderr).strip().splitlines()
    return {
        "returncode": proc.returncode,
        "log": str(log.relative_to(ROOT)),
        "summary": tail[-1] if tail else "",
        "output": proc.stdout.strip(),
    }


def main() -> None:
    STAGE.mkdir(parents=True, exist_ok=True)
    records = []
    for category in ("CSP-J", "NOIP"):
        folder = ROOT / category
        for child in sorted(folder.iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                fmt, slugs = infer(pkg)
                stem = child.stem if child.is_file() else child.name
                key = f"{category}-{stem}"
                text_root = OUT / "text" / category / child.name
                statement_name = first_name(
                    pkg.names, ["statement.md", "总题面.md", "题面.md"]
                )
                solution_name = first_name(
                    pkg.names, ["solution.md", "总题解.md", "题解.md"]
                )
                statement = text_root / statement_name
                solution = text_root / solution_name
                standard: list[tuple[str, Path]] = []
                problems = []
                for slug in slugs:
                    name = std_name(pkg, slug)
                    if name is None:
                        problems.append({"slug": slug, "std": None})
                        continue
                    assert pkg._zip is not None if pkg.is_zip else True
                    data = (
                        pkg._zip.read(pkg._originals[name])
                        if pkg.is_zip
                        else (pkg.path / Path(name)).read_bytes()
                    )
                    stage = STAGE / key / f"{slug}.cpp"
                    stage.parent.mkdir(parents=True, exist_ok=True)
                    stage.write_bytes(read_utf8_source(data))
                    standard.append((slug, stage))
                    problems.append({"slug": slug, "std": name})
                io = (
                    "file"
                    if standard
                    and all(
                        "freopen" in path.read_text(encoding="utf-8", errors="replace")
                        for _, path in standard
                    )
                    else "std"
                )
                result = run_check(
                    statement,
                    solution,
                    standard,
                    io,
                    OUT / "logs" / f"solution-{key}.txt",
                )
                records.append(
                    {
                        "category": category,
                        "package": stem,
                        "format": fmt,
                        "problems": problems,
                        "io": io,
                        "check": result,
                    }
                )
            finally:
                pkg.close()
    (OUT / "official_solution_checks.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# 官方 check_md --solution 复核", ""]
    for record in records:
        status = "PASS" if record["check"]["returncode"] == 0 else "FAIL"
        lines.append(
            f"- {record['category']}/{record['package']}: {status} "
            f"（日志 `{record['check']['log']}`）"
        )
        if status == "FAIL":
            for line in record["check"]["output"].splitlines():
                lines.append(f"  - {line}")
    (OUT / "official_solution_checks.md").write_text(
        "\n".join(lines) + "\n", encoding="utf-8"
    )
    print(f"Wrote {OUT / 'official_solution_checks.json'} and .md")


if __name__ == "__main__":
    main()
