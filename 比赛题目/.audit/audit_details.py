from __future__ import annotations

import hashlib
import io
import json
import re
import zipfile
from pathlib import Path, PurePosixPath

from audit_v3103 import Package, first_name, headings, slug_from_heading


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"


def norm_ws(data: bytes) -> str:
    return " ".join(data.decode("utf-8", errors="replace").split())


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def parse_config(text: str) -> dict:
    lines = [line.strip() for line in text.splitlines() if line.strip()]
    result: dict = {
        "first": lines[0] if lines else "",
        "points": None,
        "tl": None,
        "ml_kib": None,
        "test_lines": [],
        "issues": [],
    }
    if lines:
        match = re.search(
            r"-p\s+(\d+)\s+-t\s+([0-9.]+)\s+-m\s+(\d+)", lines[0]
        )
        if match:
            result["points"] = int(match.group(1))
            result["tl"] = float(match.group(2))
            result["ml_kib"] = int(match.group(3))
        else:
            result["issues"].append("config 首行不是可识别的基础格式")
    result["test_lines"] = [
        line for line in lines[1:] if re.match(r"test\s+\d+\.in\s+\d+\.(?:out|ans)", line)
    ]
    if not result["test_lines"]:
        result["issues"].append("config 没有 test 行")
    return result


def read_zip_text(zf: zipfile.ZipFile, name: str) -> str:
    return zf.read(name).decode("utf-8", errors="replace")


def zip_file_names(zf: zipfile.ZipFile) -> list[str]:
    return [n for n in zf.namelist() if not n.endswith("/")]


def in_memory_tests(name_bytes: dict[str, bytes], prefix: str = "") -> dict:
    names = list(name_bytes)
    ins = set()
    outs = set()
    for name in names:
        if not name.startswith(prefix):
            continue
        tail = name[len(prefix):]
        if match := re.fullmatch(r"(\d+)\.in", tail):
            ins.add(int(match.group(1)))
        elif match := re.fullmatch(r"(\d+)\.(?:out|ans)", tail):
            outs.add(int(match.group(1)))
    contiguous = bool(ins) and ins == outs == set(range(1, max(ins) + 1))
    return {
        "count": len(ins),
        "paired": contiguous,
        "indices": sorted(ins),
    }


def get_nested_zip(pkg: Package, name: str) -> zipfile.ZipFile | None:
    return pkg.nested_zip(name)


def resolve_data(pkg: Package, fmt: str, slug: str) -> dict:
    """Return hidden input bytes/config and sample-directory candidates."""
    hidden: dict[str, bytes] = {}
    config_text = ""
    location = ""
    nested = None

    if fmt == "legacy_cspj_T1-T4":
        prefix = f"{slug}/data/"
        if pkg.is_zip:
            assert pkg._zip is not None
            for name in pkg.names:
                if name.startswith(prefix) and re.fullmatch(r"\d+\.(?:in|out)", name[len(prefix):]):
                    hidden[name[len(prefix):]] = pkg._zip.read(pkg._originals[name])
            config_name = prefix + "config"
            if config_name in pkg.names:
                config_text = pkg.read_text(config_name)
                location = config_name
        else:
            data_dir = pkg.path / "data"
            if data_dir.is_dir():
                for path in data_dir.iterdir():
                    if path.is_file() and re.fullmatch(r"\d+\.(?:in|out)", path.name):
                        hidden[path.name] = path.read_bytes()
                if (data_dir / "config").is_file():
                    config_text = (data_dir / "config").read_text(
                        encoding="utf-8", errors="replace"
                    )
                    location = str(data_dir / "config")

    elif fmt == "noip_zip":
        rel = f"data/{slug}.zip"
        nested = get_nested_zip(pkg, rel)
        if nested is not None:
            location = rel
            for name in zip_file_names(nested):
                hidden[Path(name).name] = nested.read(name)
            if "config" in nested.namelist():
                config_text = read_zip_text(nested, "config")
    else:
        prefix = f"data/{slug}/"
        if pkg.is_zip:
            assert pkg._zip is not None
            for name in pkg.names:
                tail = name[len(prefix):] if name.startswith(prefix) else ""
                if re.fullmatch(r"\d+\.(?:in|out)", tail):
                    hidden[tail] = pkg._zip.read(pkg._originals[name])
            config_name = prefix + "config"
            if config_name in pkg.names:
                config_text = pkg.read_text(config_name)
                location = config_name
        else:
            data_dir = pkg.path / "data" / slug
            if data_dir.is_dir():
                for path in data_dir.iterdir():
                    if path.is_file() and re.fullmatch(r"\d+\.(?:in|out)", path.name):
                        hidden[path.name] = path.read_bytes()
                if (data_dir / "config").is_file():
                    config_text = (data_dir / "config").read_text(
                        encoding="utf-8", errors="replace"
                    )
                    location = str(data_dir / "config")

    test_info = in_memory_tests(hidden)
    config = parse_config(config_text) if config_text else None
    return {
        "location": location,
        "hidden": hidden,
        "tests": test_info,
        "config": config,
        "nested": nested,
    }


def resolve_samples(pkg: Package, fmt: str, slug: str) -> dict:
    """Read every plausible distributed sample input/output pair."""
    result = {
        "files": {},
        "dirs": [],
        "numbers": [],
        "issue": "",
    }

    # Generic directories and older packages: look for a sample directory.
    if not pkg.is_zip:
        for dirname in ("下发", "下发文件", "下发样例", "样例", "samples", "attachment"):
            base = pkg.path / dirname
            if not base.is_dir():
                continue
            candidates = [
                base / slug,
                base / f"{slug}.zip",
            ]
            for candidate in candidates:
                if candidate.is_dir():
                    result["dirs"].append(str(candidate))
                    for path in candidate.iterdir():
                        if path.is_file() and re.fullmatch(
                            re.escape(slug) + r"(\d+)\.(in|ans|out)", path.name
                        ):
                            result["files"][path.name] = path.read_bytes()
                elif candidate.is_file() and candidate.suffix.lower() == ".zip":
                    result["dirs"].append(str(candidate))
                    with zipfile.ZipFile(candidate) as zf:
                        for name in zip_file_names(zf):
                            base = Path(name).name
                            if re.fullmatch(
                                re.escape(slug) + r"(\d+)\.(in|ans|out)", base
                            ):
                                result["files"][base] = zf.read(name)
            if result["files"]:
                break

    # Zip package: sample directories are commonly 下发/<slug>/... or 下发/<slug>.zip.
    if pkg.is_zip:
        for dirname in ("下发", "下发文件", "下发样例", "样例", "samples", "attachment"):
            prefix = dirname + "/"
            if not any(n.startswith(prefix) for n in pkg.names):
                continue
            for name in pkg.names:
                if not name.startswith(prefix):
                    continue
                tail = name[len(prefix):]
                base = Path(tail).name
                if re.fullmatch(re.escape(slug) + r"(\d+)\.(in|ans|out)", base):
                    assert pkg._zip is not None
                    result["files"][base] = pkg._zip.read(pkg._originals[name])
            zname = f"{prefix}{slug}.zip"
            nested = pkg.nested_zip(zname)
            if result["files"] == {} and nested is not None:
                result["dirs"].append(zname)
                for name in zip_file_names(nested):
                    base = Path(name).name
                    if re.fullmatch(
                        re.escape(slug) + r"(\d+)\.(in|ans|out)", base
                    ):
                        result["files"][base] = nested.read(name)
                nested.close()
            if result["files"]:
                break

    # Legacy CSP-J stores samples in T*/attachment.zip. Inspect the nested archive.
    if pkg.is_zip and fmt == "legacy_cspj_T1-T4":
        zname = f"{slug}/attachment.zip"
        nested = pkg.nested_zip(zname)
        if nested is not None:
            result["dirs"].append(zname)
            for name in zip_file_names(nested):
                base = Path(name).name
                if re.fullmatch(r".+(\d+)\.(in|ans|out)", base):
                    result["files"][base] = nested.read(name)
            nested.close()

    numbers = set()
    for name in result["files"]:
        base = Path(name).stem
        if base.startswith(slug) and base[len(slug):].isdigit():
            numbers.add(int(base[len(slug):]))
        elif match := re.search(r"(\d+)$", base):
            numbers.add(int(match.group(1)))
    result["numbers"] = sorted(numbers)
    return result


def read_statement_and_solution(pkg: Package, fmt: str, slug: str) -> dict:
    statement_name = first_name(pkg.names, ["statement.md", "总题面.md", "题面.md"])
    solution_name = first_name(pkg.names, ["solution.md", "总题解.md", "题解.md"])
    statement = pkg.read_text(statement_name) if statement_name else ""
    solution = pkg.read_text(solution_name) if solution_name else ""
    # Legacy CSP-J has per-problem statements and solutions; use those for
    # sample/format checks, while retaining the aggregate files for report.
    if fmt == "legacy_cspj_T1-T4":
        per_statement = f"{slug}/statement.md"
        per_solution = f"{slug}/solution.md"
        if per_statement in pkg.names:
            statement = pkg.read_text(per_statement)
            statement_name = per_statement
        if per_solution in pkg.names:
            solution = pkg.read_text(per_solution)
            solution_name = per_solution
    return {
        "statement_name": statement_name,
        "solution_name": solution_name,
        "statement": statement,
        "solution": solution,
    }


def statement_shape(text: str) -> dict:
    # Preserve exact headings and sample headings for the audit report.
    h1 = re.findall(r"^#\s+(.+)$", text, re.M)
    h2 = re.findall(r"^##\s+(.+)$", text, re.M)
    sample_inline = re.findall(r"^#{2,4}\s*【样例\s*(\d+)\s*输入】\s*$", text, re.M)
    sample_out = re.findall(r"^#{2,4}\s*【样例\s*(\d+)\s*输出】\s*$", text, re.M)
    distributed_refs = sorted(
        {int(x) for x in re.findall(r"【样例\s*(\d+)】", text)}
    )
    return {
        "h1": h1,
        "h2": h2,
        "inline_numbers": sorted({int(x) for x in sample_inline}),
        "inline_in": sorted({int(x) for x in sample_inline}),
        "inline_out": sorted({int(x) for x in sample_out}),
        "distributed_refs": distributed_refs,
        "has_sections": all(
            name in text
            for name in ("【题目描述】", "【输入格式】", "【输出格式】", "【数据范围】")
        ),
    }


def section_text(solution: str, slug: str) -> str:
    matches = list(re.finditer(r"^#\s+(.+)$", solution, re.M))
    for i, match in enumerate(matches):
        heading = match.group(1).strip()
        if slug_from_heading(heading) == slug or slug in heading:
            end = matches[i + 1].start() if i + 1 < len(matches) else len(solution)
            return solution[match.start():end]
    return solution


def cpp_blocks(text: str) -> list[str]:
    return re.findall(r"```(?:cpp|c\+\+)\s*\n(.*?)```", text, re.S | re.I)


def normalize_code(code: str) -> str:
    code = code.replace("\r\n", "\n").replace("\r", "\n")
    return "\n".join(line.rstrip() for line in code.split("\n")).strip()


def strip_comments(code: str) -> str:
    code = re.sub(r"/\*.*?\*/", "", code, flags=re.S)
    code = re.sub(r"//[^\n]*", "", code)
    return re.sub(r"\s+", "", code)


def std_name(pkg: Package, fmt: str, slug: str) -> str | None:
    if fmt == "legacy_cspj_T1-T4":
        candidates = [f"{slug}/std.cpp"]
    else:
        candidates = [
            f"std/{slug}/{slug}.cpp",
            f"std/{slug}.cpp",
            f"代码/{slug}.cpp",
        ]
    for candidate in candidates:
        if candidate in pkg.names:
            return candidate
    return None


def sample_compare(
    hidden: dict[str, bytes], public: dict[str, bytes], inline_inputs: list[bytes]
) -> dict:
    hidden_hash: dict[str, int] = {}
    hidden_dupes: list[str] = []
    for name, data in hidden.items():
        if not name.endswith(".in"):
            continue
        key = digest(norm_ws(data).encode("utf-8"))
        if key in hidden_hash:
            hidden_dupes.append(f"{name} duplicates hidden input {hidden_hash[key]}.in")
        else:
            hidden_hash[key] = int(Path(name).stem)

    public_items: list[tuple[str, bytes]] = list(public.items())
    public_items.extend((f"inline sample {i + 1}", data) for i, data in enumerate(inline_inputs))
    seen: dict[str, str] = {}
    public_dupes: list[str] = []
    equal_hidden: list[str] = []
    for name, data in public_items:
        if not name.endswith(".in") and not name.startswith("inline sample "):
            continue
        key = digest(norm_ws(data).encode("utf-8"))
        if key in hidden_hash:
            equal_hidden.append(f"public {name} equals hidden {hidden_hash[key]}.in")
        if key in seen:
            public_dupes.append(f"public {name} repeats {seen[key]}")
        else:
            seen[key] = name
    return {
        "hidden_duplicates": hidden_dupes,
        "public_duplicates": public_dupes,
        "public_equals_hidden": equal_hidden,
    }


def check_zip_health(zf: zipfile.ZipFile) -> list[str]:
    names = zf.namelist()
    issues = []
    duplicate = sorted({n for n in names if names.count(n) > 1})
    if duplicate:
        issues.append("重复成员: " + ", ".join(duplicate[:8]))
    unsafe = [
        n
        for n in names
        if n.startswith("/")
        or ".." in PurePosixPath(n).parts
        or re.match(r"^[A-Za-z]:", n)
    ]
    if unsafe:
        issues.append("危险路径: " + ", ".join(unsafe[:8]))
    junk = [n for n in names if Path(n).name in (".DS_Store", "Thumbs.db")]
    if junk:
        issues.append("系统缓存: " + ", ".join(junk[:8]))
    return issues


def main() -> None:
    records = []
    for category in ("CSP-J", "NOIP"):
        folder = ROOT / category
        for child in sorted(folder.iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                stem = child.stem if child.suffix.lower() == ".zip" else child.name
                # Infer the format in the same way as the inventory script.
                names = pkg.names
                legacy = sorted({n.split("/", 1)[0] for n in names if re.match(r"T\d+/", n)})
                noip_nested = any(
                    n.startswith("data/") and n.endswith(".zip") for n in names
                )
                if legacy:
                    fmt = "legacy_cspj_T1-T4"
                    slugs = legacy
                elif noip_nested:
                    fmt = "noip_zip"
                    slugs = sorted(
                        Path(n).stem
                        for n in names
                        if n.startswith("data/") and n.endswith(".zip")
                    )
                else:
                    fmt = "generic_dir"
                    data_dirs = sorted(
                        {
                            n.split("/", 2)[1]
                            for n in names
                            if n.startswith("data/") and n.count("/") >= 2
                        }
                    )
                    slugs = data_dirs or sorted(
                        {
                            Path(n).stem
                            for n in names
                            if re.match(r"std/[^/]+/[^/]+\.cpp$", n)
                        }
                    )

                config_required = category == "NOIP"
                problems = []
                for slug in slugs:
                    docs = read_statement_and_solution(pkg, fmt, slug)
                    problem_statement = section_text(docs["statement"], slug)
                    shape = statement_shape(problem_statement)
                    data = resolve_data(pkg, fmt, slug)
                    samples = resolve_samples(pkg, fmt, slug)
                    std = std_name(pkg, fmt, slug)
                    std_text = pkg.read_text(std) if std else ""
                    blocks = cpp_blocks(section_text(docs["solution"], slug))
                    exact = any(normalize_code(b) == normalize_code(std_text) for b in blocks)
                    sem_exact = any(
                        strip_comments(b) == strip_comments(std_text) for b in blocks
                    )
                    inline_inputs = []
                    # Use the official extractor for inline samples where possible.
                    try:
                        from oi_common import extract_samples

                        inline = extract_samples(problem_statement)
                        inline_inputs = [v["in"].encode() for v in inline.values() if "in" in v]
                    except Exception:
                        inline_inputs = []
                    isolation = sample_compare(
                        data["hidden"], samples["files"], inline_inputs
                    )
                    config = data["config"]
                    if not config_required:
                        config_issue = []
                    elif config:
                        config_issue = list(config["issues"])
                    else:
                        config_issue = ["缺 config"]
                    if config and config_required:
                        if len(config["test_lines"]) != data["tests"]["count"]:
                            config_issue.append(
                                f"config 行数 {len(config['test_lines'])} 与正式点 {data['tests']['count']} 不一致"
                            )
                        if config["points"] is not None:
                            total = config["points"] * data["tests"]["count"]
                            if total != 100:
                                config_issue.append(f"config 总分 {total} 不是 100")
                        if config["tl"] is None or config["ml_kib"] is None:
                            config_issue.append("config 未提供可解析的时限/内存")
                    # Data archive health is reported once per archive below.
                    sample_refs = set(shape["distributed_refs"])
                    sample_issues = []
                    if samples["numbers"] and not sample_refs:
                        sample_issues.append("有下发输入但题面没有 【样例 k】 引用")
                    missing_refs = sorted(
                        k for k in sample_refs if k not in samples["numbers"]
                    )
                    if missing_refs:
                        sample_issues.append(
                            "题面引用了不存在的下发样例: " + ", ".join(map(str, missing_refs))
                        )
                    unreferenced = sorted(
                        k for k in samples["numbers"] if k not in sample_refs
                    )
                    if unreferenced:
                        sample_issues.append(
                            "下发样例未全部被题面引用: " + ", ".join(map(str, unreferenced))
                        )
                    if isolation["hidden_duplicates"]:
                        sample_issues.extend(isolation["hidden_duplicates"])
                    if isolation["public_duplicates"]:
                        sample_issues.extend(isolation["public_duplicates"])
                    if isolation["public_equals_hidden"]:
                        sample_issues.extend(isolation["public_equals_hidden"])
                    if not data["tests"]["paired"]:
                        sample_issues.append("正式点 in/out 不连续或未配对")
                    problems.append(
                        {
                            "slug": slug,
                            "statement": docs["statement_name"],
                            "solution": docs["solution_name"],
                            "h1": shape["h1"],
                            "has_standard_sections": shape["has_sections"],
                            "inline_samples": shape["inline_numbers"],
                            "distributed_refs": shape["distributed_refs"],
                            "sample_numbers": samples["numbers"],
                            "sample_files": sorted(samples["files"]),
                            "sample_dirs": samples["dirs"],
                            "test_count": data["tests"]["count"],
                            "test_paired": data["tests"]["paired"],
                            "config_location": data["location"],
                            "config_required": config_required,
                            "config": config,
                            "config_issues": config_issue,
                            "std": std,
                            "cpp_blocks": len(blocks),
                            "std_exact": exact,
                            "std_semantic_without_comments": sem_exact,
                            "sample_issues": sample_issues,
                            "isolation": isolation,
                        }
                    )
                health = []
                if pkg.is_zip:
                    assert pkg._zip is not None
                    health.extend(check_zip_health(pkg._zip))
                    for name in names:
                        if name.startswith("data/") and name.endswith(".zip"):
                            nested = pkg.nested_zip(name)
                            if nested:
                                health.extend(f"{name}: {x}" for x in check_zip_health(nested))
                                nested.close()
                records.append(
                    {
                        "category": category,
                        "package": stem,
                        "format": fmt,
                        "slugs": slugs,
                        "problems": problems,
                        "zip_health": health,
                    }
                )
            finally:
                pkg.close()

    (OUT / "audit_details.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# V3.10.3 细化验收", ""]
    for record in records:
        lines.append(f"## {record['category']} / {record['package']}")
        lines.append(
            f"- 格式：`{record['format']}`；ZIP 健康：{'；'.join(record['zip_health']) or '未发现问题'}"
        )
        for p in record["problems"]:
            config = p["config"]
            if not p["config_required"]:
                config_line = "不适用（CSP-J/CSP-S 不生成 config）"
            elif config:
                config_line = (
                    f"{config['first']}；{len(config['test_lines'])} test；总分 "
                    f"{(config['points'] or 0) * p['test_count']}"
                )
            else:
                config_line = "缺"
            lines.append(
                f"- `{p['slug']}`：点 {p['test_count']}（配对={'是' if p['test_paired'] else '否'}）；"
                f"config={config_line}；下发 {p['sample_numbers'] or '无'}；"
                f"引用 {p['distributed_refs'] or '无'}；std 逐字={'是' if p['std_exact'] else '否'}；"
                f"去注释后={'一致' if p['std_semantic_without_comments'] else '不一致'}"
            )
            for issue in p["config_issues"] + p["sample_issues"]:
                lines.append(f"  - {issue}")
        lines.append("")
    (OUT / "audit_details.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"Wrote {OUT / 'audit_details.json'} and {OUT / 'audit_details.md'}")


if __name__ == "__main__":
    main()
