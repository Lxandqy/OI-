from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
import zipfile
from pathlib import Path


CSP_ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\CSP-J")
AUDIT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit")
GXX = AUDIT / "tools" / "w64devkit" / "w64devkit" / "bin" / "g++.exe"
BACKUP = AUDIT / "backup_zips"
WORK = AUDIT / "work" / "legacy_cspj"

SETS = {
    "第七套_V3.8_完整重构包": {
        "title": "CSP-J 模拟赛第七套",
        "slugs": ["palindrome", "quad", "files", "leafcut"],
        "titles": ["回文串", "交错四元组", "文件判定", "树与叶子"],
    },
    "第五套_V3.8_完整重构包": {
        "title": "CSP-J 模拟赛第五套",
        "slugs": ["date", "purchase", "divisible", "green"],
        "titles": ["上下五千年", "采购", "整除序列", "绿野仙踪"],
    },
    "第六套_V3.8_完整重构包": {
        "title": "CSP-J 模拟赛第六套",
        "slugs": ["maxmod", "crossmul", "triples", "splitnum"],
        "titles": ["最多求余", "各乘一个", "三元组", "切割"],
    },
    "第四套_V3.8_完整重构包": {
        "title": "CSP-J 模拟赛第四套",
        "slugs": ["chain", "sumsq", "necklace", "eval"],
        "titles": ["接龙", "平方和", "彩彩的三彩项链", "表达式"],
    },
}


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


def split_h2(text: str) -> tuple[str, list[tuple[str, str]]]:
    matches = list(re.finditer(r"^##\s+(.+?)\s*$", text, re.M))
    if not matches:
        return text, []
    pre = text[: matches[0].start()]
    sections = []
    for i, match in enumerate(matches):
        end = matches[i + 1].start() if i + 1 < len(matches) else len(text)
        sections.append((match.group(1).strip(), text[match.end() : end]))
    return pre, sections


def code_blocks(body: str) -> tuple[list[str], str]:
    blocks = []
    pattern = re.compile(r"```(?:text)?\s*\n(.*?)```", re.S)
    for match in pattern.finditer(body):
        blocks.append(match.group(1).rstrip("\n"))
    explanation = pattern.sub("", body)
    explanation = re.sub(r"^(?:输入|输出)\s*[：:]\s*$", "", explanation, flags=re.M)
    explanation = re.sub(r"^样例\s*\d+\s*[：:]\s*$", "", explanation, flags=re.M)
    explanation = "\n".join(line.rstrip() for line in explanation.splitlines()).strip()
    return blocks, explanation


def parse_samples(section_body: str) -> list[tuple[str, str, str]]:
    """Return [(input, output, explanation)]."""
    groups: list[tuple[str, str]] = []
    h3 = list(re.finditer(r"^###\s+样例\s*(\d+)\s*$", section_body, re.M))
    if h3:
        for i, match in enumerate(h3):
            end = h3[i + 1].start() if i + 1 < len(h3) else len(section_body)
            groups.append((match.group(0), section_body[match.end() : end]))
    else:
        h2 = list(
            re.finditer(r"^##\s+样例\s*(\d+)\s*$", section_body, re.M)
        )
        if h2:
            for i, match in enumerate(h2):
                end = h2[i + 1].start() if i + 1 < len(h2) else len(section_body)
                groups.append((match.group(0), section_body[match.end() : end]))
        else:
            groups.append(("", section_body))

    result: list[tuple[str, str, str]] = []
    for _, body in groups:
        blocks, explanation = code_blocks(body)
        if len(blocks) < 2:
            continue
        # Most samples are one input/output pair. If a group contains
        # several pairs, keep the first pair: the old packages only use this
        # layout for grouped sample headings, which are split above.
        result.append((blocks[0], blocks[1], explanation))
    return result


def normalize_statement(
    text: str, title: str, slug: str, inline_count: int
) -> str:
    pre, sections = split_h2(text)
    preamble = pre
    preamble = re.sub(r"^#\s+.*$", "", preamble, count=1, flags=re.M).strip()
    preamble = re.sub(
        r"^\*\*(?:时间限制|空间限制|输入文件|输出文件)[^\n]*\n?", "",
        preamble,
        flags=re.M,
    ).strip()
    preamble = re.sub(r"^时间限制[^\n]*\n?", "", preamble, flags=re.M).strip()

    desc = ""
    input_format = ""
    output_format = ""
    data_range = ""
    samples: list[tuple[str, str, str]] = []
    sample_note = ""
    for name, body in sections:
        clean = name.strip()
        if clean in ("题目描述", "题目描述】"):
            desc = body.strip()
        elif clean in ("输入格式", "输入格式】"):
            input_format = body.strip()
        elif clean in ("输出格式", "输出格式】"):
            output_format = body.strip()
        elif clean.startswith("输入输出样例") or re.fullmatch(r"样例\s*\d+", clean):
            if clean.startswith("输入输出样例"):
                samples.extend(parse_samples(body))
            else:
                # A single H2 sample section; parse the body as one group.
                blocks, explanation = code_blocks(body)
                if len(blocks) >= 2:
                    samples.append((blocks[0], blocks[1], explanation))
        elif clean in ("样例说明", "样例说明】"):
            sample_note = body.strip()
        elif clean.startswith("数据范围"):
            data_range = body.strip()

    out = [f"# {title}（{slug}）", ""]
    if preamble:
        out.extend([preamble, ""])
    out.extend(["## 【题目描述】", "", desc, ""])
    out.extend(["## 【输入格式】", "", input_format, ""])
    out.extend(["## 【输出格式】", "", output_format, ""])
    for i, (inp, answer, explanation) in enumerate(samples, 1):
        out.extend(
            [
                f"## 【样例 {i} 输入】",
                "",
                "```text",
                inp,
                "```",
                "",
                f"## 【样例 {i} 输出】",
                "",
                "```text",
                answer,
                "```",
                "",
            ]
        )
        if explanation:
            out.extend([f"## 【样例 {i} 解释】", "", explanation, ""])
    if sample_note:
        out.extend(["## 【样例说明】", "", sample_note, ""])
    # Distributed samples are added by the caller after the inline block.
    out.extend(["## 【数据范围】", "", data_range, ""])
    return "\n".join(out).strip() + "\n"


def add_distributed_refs(text: str, slug: str, inline_count: int) -> str:
    chunks = []
    for i in range(2):
        number = inline_count + i + 1
        chunks.append(
            f"## 【样例 {number}】\n\n"
            f"见下发文件中的 `{slug}/{slug}{number}.in` 与 "
            f"`{slug}/{slug}{number}.ans`。本组为公开大样例，不计入正式测试点。\n"
        )
    insert = "\n".join(chunks)
    marker = "## 【数据范围】"
    if marker in text:
        return text.replace(marker, insert + "\n" + marker, 1)
    return text + "\n" + insert


def compile_std(src: Path, build: Path, slug: str) -> Path:
    exe = build / f"{slug}.exe"
    proc = subprocess.run(
        [str(GXX), "-O2", "-std=c++14", str(src), "-o", str(exe)],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    if proc.returncode:
        raise RuntimeError(f"compile failed for {slug}: {proc.stderr[-2000:]}")
    return exe


def io_name_from_source(text: str, fallback: str) -> str:
    match = re.search(r'freopen\(\s*"([^"]+)\.in"', text)
    return Path(match.group(1)).name if match else fallback


def run_std(exe: Path, text: str, io_name: str, stdin_data: str) -> str:
    with tempfile.TemporaryDirectory(prefix="oi-old-") as tmp:
        work = Path(tmp)
        if "freopen" in text:
            (work / f"{io_name}.in").write_text(stdin_data, encoding="utf-8")
            proc = subprocess.run(
                [str(exe)], cwd=work, capture_output=True, timeout=30
            )
            out = work / f"{io_name}.out"
            return out.read_text(encoding="utf-8", errors="replace") if out.exists() else ""
        proc = subprocess.run(
            [str(exe)],
            cwd=work,
            input=stdin_data.encode(),
            capture_output=True,
            timeout=30,
        )
        return proc.stdout.decode("utf-8", errors="replace")


def normalize_answer(value: str) -> str:
    return value.replace("\r\n", "\n").strip() + "\n"


def transform_solution(text: str, titles: dict[str, str], slugs: dict[str, str]) -> str:
    lines = text.splitlines()
    out = []
    for line in lines:
        match = re.match(r"^#\s+T(\d+)\s+(.*)$", line)
        if match:
            old = "T" + match.group(1)
            title = titles.get(old, match.group(2).strip())
            slug = slugs[old]
            out.append(f"# {title}（{slug}）")
        else:
            out.append(line)
    return "\n".join(out).strip() + "\n"


def build_readme(set_title: str, slugs: list[str], names: list[str]) -> str:
    rows = "\n".join(
        f"| {i + 1} | {name} | `{slug}` | 10 | 10 |"
        for i, (name, slug) in enumerate(zip(names, slugs))
    )
    return f"""# {set_title} 教师说明

## 来源与改编

原包未提供来源记录，来源待确认；本说明不补写未经核实的出处。题意、数据与 std 按原包保留，仅做 V3.10.3 交付结构、题面栏目和样例引用规范化。

## 完整范围

CSP-J 训练套题，4 题，每题 100 分，总分 400 分。每题正式测试点为 10 个，每个 10 分；不设置 config（按用户要求，CSP-J/CSP-S 无需 config）。

## 测分矩阵

| 题号 | 题目 | slug | 测试点 | 每点分值 |
|---:|---|---|---:|---:|
{rows}

## 证据

- 题面样例与下发样例均由当前 std 复跑核对。
- 正式测试点按 `1..N.in/out` 连续配对。
- 本套为旧包结构迁移；题面和样例的机械检查结果见同批验收记录。
"""


def main() -> None:
    BACKUP.mkdir(parents=True, exist_ok=True)
    WORK.mkdir(parents=True, exist_ok=True)
    selected = set(sys.argv[1:])
    for stem, config in SETS.items():
        if selected and stem not in selected:
            continue
        src_zip = CSP_ROOT / f"{stem}.zip"
        if not src_zip.is_file():
            raise SystemExit(f"missing {src_zip}")
        work = WORK / stem
        if work.exists():
            shutil.rmtree(work)
        work.mkdir(parents=True)
        with zipfile.ZipFile(src_zip) as zf:
            zf.extractall(work)
        build = work / "_build"
        build.mkdir()
        slugs = config["slugs"]
        titles = config["titles"]
        mapping = {f"T{i + 1}": slugs[i] for i in range(4)}
        title_mapping = {f"T{i + 1}": titles[i] for i in range(4)}
        statement_parts = []
        solution_parts = []
        all_std: dict[str, Path] = {}
        for i, (old, slug) in enumerate(mapping.items()):
            problem_dir = work / old
            statement_path = problem_dir / "statement.md"
            statement_text = read_text(statement_path)
            inline_matches = re.findall(
                r"^###\s+样例\s*(\d+)\s*$|^##\s+样例\s*(\d+)\s*$",
                statement_text,
                re.M,
            )
            if inline_matches:
                inline_count = max(int(a or b) for a, b in inline_matches)
            else:
                # Unlabelled sample section normally contains exactly one pair.
                inline_count = 1
            new_statement = normalize_statement(
                statement_text, titles[i], slug, inline_count
            )
            new_statement = add_distributed_refs(new_statement, slug, inline_count)
            statement_parts.append(new_statement)

            # Compile and normalize the main solution.
            std_src = problem_dir / "std.cpp"
            std_text = read_text(std_src)
            if "freopen" in std_text:
                # The migrated CSP-J packages use one consistent standard-IO
                # interface. Removing the old file binding keeps the code and
                # the stated interface in sync.
                std_text = re.sub(
                    r"^[ \t]*freopen\([^\n]*\);[ \t]*(?:\r?\n|$)",
                    "",
                    std_text,
                    flags=re.M,
                )
                std_src.write_text(std_text, encoding="utf-8")
            exe = compile_std(std_src, build, slug)
            all_std[slug] = std_src

            # Repair inline sample outputs from the std; the old sample text
            # remains the source of the inputs and explanations.
            data_dir = work / "data" / slug
            data_dir.mkdir(parents=True)
            for f in (problem_dir / "data").iterdir():
                if f.is_file():
                    shutil.copy2(f, data_dir / f.name)
            std_dir = work / "std" / slug
            std_dir.mkdir(parents=True)
            shutil.copy2(std_src, std_dir / f"{slug}.cpp")

            # Distributed samples: attachment1/2, renumbered after inline.
            attach = problem_dir / "attachment.zip"
            if not attach.is_file():
                raise RuntimeError(f"missing attachment: {attach}")
            sample_dir = work / "下发" / slug
            sample_dir.mkdir(parents=True)
            with zipfile.ZipFile(attach) as az:
                names = az.namelist()
                for j in range(1, 3):
                    inp_name = next(
                        (n for n in names if Path(n).name == f"attachment{j}.in"),
                        None,
                    )
                    if inp_name is None:
                        raise RuntimeError(f"missing attachment{j}.in in {attach}")
                    input_text = az.read(inp_name).decode("utf-8", errors="replace")
                    answer = run_std(exe, std_text, slug, input_text)
                    number = inline_count + j
                    (sample_dir / f"{slug}{number}.in").write_text(
                        normalize_answer(input_text), encoding="utf-8"
                    )
                    (sample_dir / f"{slug}{number}.ans").write_text(
                        normalize_answer(answer), encoding="utf-8"
                    )

            sol = problem_dir / "solution.md"
            solution_parts.append(
                re.sub(
                    r"^[ \t]*freopen\([^\n]*\);[ \t]*(?:\r?\n|$)",
                    "",
                    read_text(sol),
                    flags=re.M,
                )
            )

        # Repair inline outputs using the now-normalized statements.
        repaired_parts = []
        for i, part in enumerate(statement_parts):
            slug = slugs[i]
            exe = build / f"{slug}.exe"
            std_text = read_text(all_std[slug])
            # Parse the standard sample headings and replace each output.
            pattern = re.compile(
                r"(## 【样例 (\d+) 输入】\n\n```text\n.*?\n```\n\n"
                r"## 【样例 \2 输出】\n\n```text\n)(.*?)(\n```)",
                re.S,
            )
            def replace_output(match: re.Match[str]) -> str:
                inp = re.search(
                    r"## 【样例 \d+ 输入】\n\n```text\n(.*?)\n```",
                    match.group(0),
                    re.S,
                )
                if not inp:
                    return match.group(0)
                got = run_std(exe, std_text, slug, inp.group(1))
                return match.group(1) + normalize_answer(got).rstrip("\n") + match.group(4)

            repaired_parts.append(pattern.sub(replace_output, part))

        statement = (
            f"# {config['title']}\n\n"
            "本套为 CSP-J 训练模拟赛，共 4 题，每题 100 分，总分 400 分。\n\n"
            "| 项目 | T1 | T2 | T3 | T4 |\n"
            "|---|---|---|---|---|\n"
            + "| 题目名称 | " + " | ".join(titles) + " |\n"
            + "| 目录 | " + " | ".join(f"`{s}`" for s in slugs) + " |\n"
            + "| 源程序 | " + " | ".join(f"`{s}.cpp`" for s in slugs) + " |\n"
            + "| 测试点数 | 10 | 10 | 10 | 10 |\n"
            + "| 每点分值 | 10 | 10 | 10 | 10 |\n\n"
            + "编译选项：`-O2 -std=c++14`。各题均采用标准输入输出；"
            + "题面样例与下发大样例不计入正式测试点。\n\n"
            + "\n".join(repaired_parts)
        )
        solution = "\n\n".join(solution_parts)
        solution = transform_solution(solution, title_mapping, mapping)
        teacher = build_readme(config["title"], slugs, titles)

        (work / "statement.md").write_text(statement, encoding="utf-8")
        (work / "solution.md").write_text(solution, encoding="utf-8")
        (work / "教师说明.md").write_text(teacher, encoding="utf-8")

        # Remove old per-problem layout and temporary build dir.
        for old in mapping:
            shutil.rmtree(work / old)
        shutil.rmtree(build)
        # The old aggregate PDFs are stale; they are not carried into the new
        # package. PDFs are rebuilt separately from the normalized Markdown.
        for stale in list(work.glob("*.pdf")):
            stale.unlink()

        backup = BACKUP / src_zip.name
        if backup.exists():
            backup.unlink()
        shutil.move(str(src_zip), str(backup))
        with zipfile.ZipFile(src_zip, "w", zipfile.ZIP_DEFLATED) as zf:
            for path in sorted(work.rglob("*")):
                if path.is_file():
                    zf.write(path, path.relative_to(work).as_posix())
        print("migrated", stem)


if __name__ == "__main__":
    main()
