from __future__ import annotations

import re
import shutil
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit" / "staged"

PACKAGES = {
    "meeting": ("NOIP模拟赛-宴会名册", {"invite": 2, "river": 2, "trio": 2, "roads": 2}),
    "third": ("第三套 NOIP 模拟赛", {"relay": 2, "watch": 2, "palpath": 2, "circle": 3}),
    "fourth": ("第四套 NOIP 模拟赛", {"cut": 4, "region": 4, "track": 4, "bits": 4}),
    "sixth": ("第六套 NOIP 模拟赛", {"product": 3, "disk": 3, "gcdforest": 2, "joint": 2}),
    "second": ("第二套 NOIP 模拟卷", {"repair": 4, "patrol": 4, "compile": 4, "orcost": 4}),
    "cc": (
        "NOIP模拟赛-第二套-CC版.zip",
        {"lamp": 3, "liar": 4, "bridge": 3, "park": 3},
    ),
    "fifth": ("第五套 NOIP 模拟赛.zip", {"cross": 3, "password": 3, "spider": 3, "tree": 3}),
    "first": ("第一套 NOIP 模拟卷.zip", {"xor4": 4, "triplet": 3, "menu": 4, "logic": 4}),
}


def statement_name(pkg: Package) -> str:
    return next(n for n in ("总题面.md", "statement.md") if n in pkg.names)


def solution_name(pkg: Package) -> str:
    return next(n for n in ("总题解.md", "solution.md") if n in pkg.names)


def normalize_first(text: str) -> str:
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    text = re.sub(
        r"(?ms)^## 附加样例\s*\n.*?(?=^## 数据范围与子任务\s*$)",
        "",
        text,
    )
    replacements = {
        "## 题目描述": "## 【题目描述】",
        "## 输入格式": "## 【输入格式】",
        "## 输出格式": "## 【输出格式】",
        "## 数据范围与子任务": "## 【数据范围】",
    }
    lines = text.splitlines()
    result: list[str] = []
    current_sample = 0
    for line in lines:
        if line in replacements:
            result.append(replacements[line])
            continue
        match = re.fullmatch(r"## 样例 (\d+)", line.strip())
        if match:
            current_sample = int(match.group(1))
            result.append(f"## 【样例 {current_sample} 输入】")
            continue
        if line.strip() == "**输入：**":
            continue
        if line.strip() == "**输出：**":
            result.append(f"## 【样例 {current_sample} 输出】")
            continue
        result.append(line)
    text = "\n".join(result)
    text = text.replace(
        "题面样例和公开附加样例不计入正式测试点。",
        "题面样例和下发大样例均不计入正式测试点。",
    )
    return re.sub(r"\n{3,}", "\n\n", text)


def normalize_fifth(text: str) -> str:
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    text = re.sub(
        r"(?m)^(【(?:题目描述|输入格式|输出格式|数据范围|样例 \d+ (?:输入|输出|解释))】)\s*$",
        r"## \1",
        text,
    )
    return re.sub(r"\n{3,}", "\n\n", text)


def problem_spans(text: str) -> list[tuple[str, int, int]]:
    matches = list(re.finditer(r"(?m)^# .*（([a-z0-9][a-z0-9_-]*)）\s*$", text))
    spans = []
    for index, match in enumerate(matches):
        end = matches[index + 1].start() if index + 1 < len(matches) else len(text)
        spans.append((match.group(1), match.start(), end))
    return spans


def remove_existing_refs(segment: str) -> str:
    return re.sub(
        r"(?ms)^## 【样例 [4-9]\d*】\s*\n.*?(?=^## 【数据范围】\s*$)",
        "",
        segment,
    )


def add_reference(segment: str, slug: str, number: int) -> str:
    reference = (
        f"## 【样例 {number}】\n\n"
        f"见下发文件 `{slug}/{slug}{number}.in` 与 "
        f"`{slug}/{slug}{number}.ans`。该样例的数据规模满足全部测试点的限制，"
        "仅用于公开调试，不计入正式测试点。\n\n"
    )
    if re.search(r"(?m)^## 【数据范围】\s*$", segment):
        return re.sub(
            r"(?m)^## 【数据范围】\s*$",
            lambda _: reference + "## 【数据范围】",
            segment,
            count=1,
        )
    return segment.rstrip() + "\n\n" + reference


def patch_statement(text: str, refs: dict[str, int], mode: str) -> str:
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    if mode == "first":
        text = normalize_first(text)
    elif mode == "fifth":
        text = normalize_fifth(text)
    if mode == "second":
        pieces = []
        last = 0
        for slug, start, end in problem_spans(text):
            pieces.append(text[last:start])
            pieces.append(remove_existing_refs(text[start:end]))
            last = end
        pieces.append(text[last:])
        text = "".join(pieces)
    pieces = []
    last = 0
    for slug, start, end in problem_spans(text):
        pieces.append(text[last:start])
        segment = text[start:end]
        if slug not in refs:
            raise KeyError(f"no sample reference for {slug}")
        pieces.append(add_reference(segment, slug, refs[slug]))
        last = end
    pieces.append(text[last:])
    text = "".join(pieces)
    text = text.replace(
        "本卷不另附样例文件。",
        "题面普通样例之后另附下发大样例，编号接续且不计入正式测试点。",
    )
    return re.sub(r"\n{3,}", "\n\n", text).strip() + "\n"


def main() -> None:
    for key, (name, refs) in PACKAGES.items():
        source = ROOT / "NOIP" / name
        pkg = Package(source)
        try:
            statement = pkg.read_text(statement_name(pkg))
            solution = pkg.read_text(solution_name(pkg))
        finally:
            pkg.close()
        target = OUT / key
        if target.exists():
            shutil.rmtree(target)
        target.mkdir(parents=True)
        (target / "总题面.md").write_text(
            patch_statement(statement, refs, key), encoding="utf-8"
        )
        (target / "总题解.md").write_text(solution, encoding="utf-8")
        print(key, "statement", len(statement), "solution", len(solution))


if __name__ == "__main__":
    main()
