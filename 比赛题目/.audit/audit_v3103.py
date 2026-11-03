from __future__ import annotations

import io
import json
import re
import zipfile
from pathlib import Path


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"


class Package:
    def __init__(self, path: Path):
        self.path = path
        self.is_zip = path.is_file() and path.suffix.lower() == ".zip"
        self._zip: zipfile.ZipFile | None = None
        if self.is_zip:
            self._zip = open_zip(path)
            raw = [n for n in self._zip.namelist() if n and not n.endswith("/")]
        else:
            raw = [p.relative_to(path).as_posix() for p in path.rglob("*") if p.is_file()]
        prefix = self._common_prefix(raw)
        self.names = [self._strip(n, prefix) for n in raw]
        self._originals = {self._strip(n, prefix): n for n in raw}

    @staticmethod
    def _common_prefix(names: list[str]) -> str:
        if not names or any("/" not in n for n in names):
            return ""
        firsts = {n.split("/", 1)[0] for n in names}
        return next(iter(firsts)) + "/" if len(firsts) == 1 else ""

    @staticmethod
    def _strip(name: str, prefix: str) -> str:
        return name[len(prefix):] if prefix and name.startswith(prefix) else name

    def read_text(self, name: str) -> str:
        name = name.replace("\\", "/")
        if self.is_zip:
            assert self._zip is not None
            return self._zip.read(self._originals.get(name, name)).decode(
                "utf-8", errors="replace"
            )
        return (self.path / Path(name)).read_text(encoding="utf-8", errors="replace")

    def nested_zip(self, name: str) -> zipfile.ZipFile | None:
        name = name.replace("\\", "/")
        if self.is_zip:
            assert self._zip is not None
            try:
                return open_zip(io.BytesIO(self._zip.read(self._originals.get(name, name))))
            except KeyError:
                return None
        path = self.path / Path(name)
        if not path.is_file():
            return None
        return open_zip(path)

    def close(self) -> None:
        if self._zip is not None:
            self._zip.close()


def open_zip(source) -> zipfile.ZipFile:
    for encoding in ("utf-8", "gbk"):
        try:
            return zipfile.ZipFile(source, metadata_encoding=encoding)
        except (UnicodeDecodeError, LookupError):
            if hasattr(source, "seek"):
                source.seek(0)
    if hasattr(source, "seek"):
        source.seek(0)
    return zipfile.ZipFile(source)


def first_name(names: list[str], candidates: list[str]) -> str | None:
    for candidate in candidates:
        if candidate in names:
            return candidate
    for candidate in candidates:
        hits = [n for n in names if n.endswith("/" + candidate)]
        if len(hits) == 1:
            return hits[0]
    return None


def headings(text: str, level: int = 1) -> list[str]:
    pattern = re.compile(r"^" + "#" * level + r"\s+(.+)$", re.MULTILINE)
    return [m.group(1).strip() for m in pattern.finditer(text)]


def slug_from_heading(value: str) -> str | None:
    match = re.search(r"[（(]([a-z0-9][a-z0-9_-]*)[）)]\s*$", value)
    return match.group(1) if match else None


def zip_tests(zf: zipfile.ZipFile) -> tuple[int, bool, bool]:
    names = [n for n in zf.namelist() if not n.endswith("/")]
    ins = {
        int(m.group(1))
        for n in names
        if (m := re.fullmatch(r"(?:.*/)?(\d+)\.in", n))
    }
    outs = {
        int(m.group(1))
        for n in names
        if (m := re.fullmatch(r"(?:.*/)?(\d+)\.(?:out|ans)", n))
    }
    has_config = any(n == "config" or n.endswith("/config") for n in names)
    paired = bool(ins) and ins == outs and ins == set(range(1, max(ins) + 1))
    return len(ins), paired, has_config


def dir_tests(base: Path) -> tuple[int, bool, bool]:
    ins = {int(p.stem) for p in base.glob("*.in") if p.stem.isdigit()}
    outs = {
        int(p.stem)
        for p in list(base.glob("*.out")) + list(base.glob("*.ans"))
        if p.stem.isdigit()
    }
    has_config = (base / "config").is_file()
    paired = bool(ins) and ins == outs and ins == set(range(1, max(ins) + 1))
    return len(ins), paired, has_config


def sample_count_dir(path: Path) -> int:
    return sum(1 for p in path.rglob("*.in") if p.is_file())


def sample_count_zip(zf: zipfile.ZipFile) -> int:
    return sum(1 for n in zf.namelist() if n.endswith(".in") and not n.endswith("/"))


def package_record(path: Path, category: str) -> dict:
    pkg = Package(path)
    try:
        names = pkg.names
        stem = path.stem if pkg.is_zip else path.name

        statement = first_name(names, ["statement.md", "总题面.md", "题面.md"])
        solution = first_name(names, ["solution.md", "总题解.md", "题解.md"])
        teacher = first_name(names, ["教师说明.md"])
        statement_text = pkg.read_text(statement) if statement else ""
        solution_text = pkg.read_text(solution) if solution else ""

        statement_headings = headings(statement_text, 1)
        solution_headings = headings(solution_text, 1)
        statement_slugs = [s for h in statement_headings if (s := slug_from_heading(h))]
        solution_slugs = [s for h in solution_headings if (s := slug_from_heading(h))]

        legacy_t = sorted({n.split("/", 1)[0] for n in names if re.match(r"T\d+/", n)})
        data_entries = sorted({n.split("/", 1)[1] for n in names if n.startswith("data/")})
        data_dirs = sorted({x.split("/", 1)[0] for x in data_entries if "/" in x})
        data_zips = sorted({x.split("/", 1)[0][:-4] for x in data_entries if x.endswith(".zip")})
        code_slugs = sorted(
            {
                Path(n).stem
                for n in names
                if re.match(r"代码/[^/]+\.cpp$", n) or re.match(r"std/[^/]+\.cpp$", n)
            }
        )
        std_dirs = sorted({n.split("/", 1)[1] for n in names if n.startswith("std/") and "/" in n})

        if legacy_t:
            fmt = "legacy_cspj_T1-T4"
            slugs = legacy_t
        elif data_zips or code_slugs:
            fmt = "noip_zip"
            slugs = data_zips or code_slugs or statement_slugs
        elif data_dirs or std_dirs:
            fmt = "generic_dir"
            slugs = data_dirs or std_dirs or statement_slugs
        else:
            fmt = "other"
            slugs = statement_slugs or solution_slugs

        tests = {}
        for slug in slugs:
            if fmt == "legacy_cspj_T1-T4":
                base = f"{slug}/data"
                sub = [n for n in names if n.startswith(base + "/")]
                subdir = path / Path(base) if not pkg.is_zip else None
                if pkg.is_zip:
                    inner = [n for n in names if n.startswith(f"{slug}/data/") and n.endswith(".in")]
                    n = len(inner)
                    outs = len([n for n in names if n.startswith(f"{slug}/data/") and n.endswith(".out")])
                    tests[slug] = {"points": n, "paired": n == outs and n > 0, "config": False}
                elif subdir and subdir.is_dir():
                    n, paired, config = dir_tests(subdir)
                    tests[slug] = {"points": n, "paired": paired, "config": config}
            elif fmt == "noip_zip":
                rel = f"data/{slug}.zip"
                zf = pkg.nested_zip(rel)
                if zf is not None:
                    try:
                        n, paired, config = zip_tests(zf)
                    finally:
                        zf.close()
                    tests[slug] = {"points": n, "paired": paired, "config": config}
            else:
                if pkg.is_zip:
                    prefix = f"data/{slug}/"
                    ins = {
                        int(m.group(1))
                        for n in names
                        if n.startswith(prefix) and (m := re.fullmatch(r"(\d+)\.in", n[len(prefix):]))
                    }
                    outs = {
                        int(m.group(1))
                        for n in names
                        if n.startswith(prefix)
                        and (m := re.fullmatch(r"(\d+)\.(?:out|ans)", n[len(prefix):]))
                    }
                    config = f"{prefix}config" in names
                    paired = bool(ins) and ins == outs and ins == set(range(1, max(ins) + 1))
                    tests[slug] = {"points": len(ins), "paired": paired, "config": config}
                else:
                    base = path / "data" / slug
                    if base.is_dir():
                        n, paired, config = dir_tests(base)
                        tests[slug] = {"points": n, "paired": paired, "config": config}

        samples = {}
        sample_dir = next(
            (d for d in ("下发", "下发文件", "samples") if any(n == d or n.startswith(d + "/") for n in names)),
            None,
        )
        if sample_dir:
            for slug in slugs:
                if pkg.is_zip:
                    direct = sum(
                        1
                        for n in names
                        if n.startswith(f"{sample_dir}/{slug}/") and n.endswith(".in")
                    )
                    zrel = f"{sample_dir}/{slug}.zip"
                    if direct == 0 and zrel in names:
                        zf = pkg.nested_zip(zrel)
                        if zf is not None:
                            try:
                                direct = sample_count_zip(zf)
                            finally:
                                zf.close()
                    samples[slug] = direct
                else:
                    d = path / sample_dir / slug
                    if d.is_dir():
                        samples[slug] = sample_count_dir(d)
                    z = path / sample_dir / f"{slug}.zip"
                    if not d.is_dir() and z.is_file():
                        with zipfile.ZipFile(z) as zf:
                            samples[slug] = sample_count_zip(zf)

        all_names_lower = [n.lower() for n in names]
        pdfs = [n for n in names if n.lower().endswith(".pdf")]
        configs = [n for n in names if n == "config" or n.endswith("/config")]
        has_subtasks = bool(
            re.search(
                r"部分分|子任务|subtask|保证得分|点组|分档|"
                r"保证\s*\d+\s*分|得\s*\d+\s*分|保证测试点|通过测试点|"
                r"覆盖测试点|覆盖[^。\n]{0,20}点|"
                r"前[一二三四五六七八九十\d]+\s*个?点",
                solution_text,
                re.IGNORECASE,
            )
        )
        source_note = teacher is not None or any(
            token in n for n in names
            for token in ("来源", "source", "查重", "改编", "审计", "验收")
        )
        forbidden_visible = sorted(
            set(
                re.findall(
                    r"(?:Codeforces|Codeforces|CF\d{2,}|洛谷|rating|难度标签|算法标签)",
                    statement_text,
                    re.IGNORECASE,
                )
            )
        )
        unsafe_zip = [
            n for n in names
            if n.startswith("/") or ".." in Path(n).parts or re.match(r"^[A-Za-z]:", n)
        ]

        issues: list[str] = []
        if not statement:
            issues.append("缺少汇总题面 statement.md/总题面.md")
        if not solution:
            issues.append("缺少汇总题解 solution.md/总题解.md")
        if fmt == "legacy_cspj_T1-T4":
            issues.append("旧版 CSP-J 目录结构：仅逐题 statement，不是最新汇总题面结构")
        config_required = category == "NOIP"
        if config_required and fmt not in ("legacy_cspj_T1-T4", "noip_zip") and not configs:
            issues.append("未发现 config")
        for slug, info in tests.items():
            if not info.get("paired"):
                issues.append(f"{slug}: 正式点 in/out 不连续或不配对")
            if config_required and not info.get("config") and fmt != "legacy_cspj_T1-T4":
                issues.append(f"{slug}: 缺 config")
        if not samples:
            issues.append("未发现公开大样例")
        elif any(count == 0 for count in samples.values()):
            missing = [slug for slug, count in samples.items() if count == 0]
            issues.append("以下题目缺公开大样例: " + ", ".join(missing))
        if samples and max(samples.values(), default=0) > 3:
            issues.append("大样例超过默认上限 3 组")
        if category == "CSP-J" and not pdfs:
            issues.append("CSP-J 默认要求 Markdown+PDF，未发现 PDF")
        if category == "NOIP" and any(n.lower().endswith(".pdf") for n in names):
            issues.append("NOIP 出现 PDF；最新默认结构为 Markdown")
        # CSP-J/CSP-S 只在改编时需要教师材料；NOIP 来源记录可留在交付树外。
        # 缺少来源资料作为字段记录，不自动判成题包缺陷。
        if not has_subtasks:
            issues.append("题解未发现部分分/点组说明")
        if forbidden_visible:
            issues.append("题面疑似出现来源/rating/算法标签: " + ", ".join(forbidden_visible))
        if unsafe_zip:
            issues.append("包内存在危险路径")
        if not slugs:
            issues.append("未识别出题目 slug")

        return {
            "category": category,
            "package": stem,
            "format": fmt,
            "slugs": slugs,
            "statement": statement,
            "solution": solution,
            "teacher_note": teacher,
            "statement_h1": statement_headings,
            "solution_h1": solution_headings,
            "pdfs": pdfs,
            "configs": configs,
            "tests": tests,
            "sample_counts": samples,
            "source_note": source_note,
            "has_partial_score_text": has_subtasks,
            "issues": issues,
        }
    finally:
        pkg.close()


def main() -> None:
    records = []
    for category in ("CSP-J", "CSP-S", "NOIP"):
        folder = ROOT / category
        if not folder.is_dir():
            continue
        for child in sorted(folder.iterdir()):
            if child.is_dir() or child.suffix.lower() == ".zip":
                records.append(package_record(child, category))

    OUT.mkdir(exist_ok=True)
    text_root = OUT / "text"
    for category in ("CSP-J", "CSP-S", "NOIP"):
        folder = ROOT / category
        if not folder.is_dir():
            continue
        for child in sorted(folder.iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                for name in pkg.names:
                    if not name.lower().endswith(".md"):
                        continue
                    target = text_root / category / child.name / Path(name)
                    target.parent.mkdir(parents=True, exist_ok=True)
                    value = pkg.read_text(name).replace("\r\n", "\n").replace("\r", "\n")
                    with target.open("w", encoding="utf-8", newline="\n") as handle:
                        handle.write(value)
            finally:
                pkg.close()
    (OUT / "inventory.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# 机械验收清单", ""]
    for record in records:
        lines.append(
            f"## {record['category']} / {record['package']}\n"
            f"- 结构：`{record['format']}`\n"
            f"- 题目：{', '.join(record['slugs']) or '未识别'}\n"
            f"- 题面/题解：{record['statement'] or '缺'} / {record['solution'] or '缺'}\n"
            f"- 测试点：{record['tests']}\n"
            f"- 大样例：{record['sample_counts']}\n"
            f"- 问题：{'；'.join(record['issues']) or '无'}\n"
        )
    (OUT / "inventory.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"Wrote {OUT / 'inventory.json'} and {OUT / 'inventory.md'}")


if __name__ == "__main__":
    main()
