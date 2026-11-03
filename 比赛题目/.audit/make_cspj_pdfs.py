from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import zipfile
from pathlib import Path


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
CSPJ = ROOT / "CSP-J"
OUT = ROOT / ".audit" / "cspj_pdf_work"
BACKUP = ROOT / ".audit" / "backup_zips"
STAGING = ROOT / ".audit" / "package_staging_cspj"
PYTHON = Path(
    r"C:\Users\Administrator\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe"
)
SKILL = Path(r"C:\Users\Administrator\.codex\skills\oi-contest-authoring")
TECTONIC = Path(
    r"C:\Users\Administrator\Desktop\OI-\2026-10-19\cspj-golden-osmanthus\work\tools\tectonic.exe"
)
OLD_PDF = ROOT / ".audit" / "pdf"

SUITES = {
    "第四套_V3.8_完整重构包.zip": {
        "subtitle": "第四套",
        "old_pdf": "第四套_V3.8_完整重构包",
    },
    "第五套_V3.8_完整重构包.zip": {
        "subtitle": "第五套",
        "old_pdf": "第五套_V3.8_完整重构包",
    },
    "第六套_V3.8_完整重构包.zip": {
        "subtitle": "第六套",
        "old_pdf": "第六套_V3.8_完整重构包",
    },
    "第七套_V3.8_完整重构包.zip": {
        "subtitle": "第七套",
        "old_pdf": "第七套_V3.8_完整重构包",
    },
}


def read_text(zf: zipfile.ZipFile, name: str) -> str:
    return zf.read(name).decode("utf-8-sig").replace("\r\n", "\n").replace("\r", "\n")


def esc_text(text: str) -> str:
    text = text.replace("\\", r"\textbackslash{}")
    for old, new in (("&", r"\&"), ("%", r"\%"), ("#", r"\#"), ("_", r"\_")):
        text = text.replace(old, new)
    return text


def inline(text: str) -> str:
    pieces = re.split(r"(\$[^$]*\$|`[^`]+`)", text)
    result = []
    for piece in pieces:
        if not piece:
            continue
        if piece.startswith("$") and piece.endswith("$") and len(piece) >= 2:
            result.append(piece)
        elif piece.startswith("`") and piece.endswith("`") and len(piece) >= 2:
            token = piece[1:-1]
            if token.endswith((".in", ".out", ".ans")) or "/" in token:
                result.append(r"\OIFile{" + token + "}")
            else:
                result.append(r"\texttt{\detokenize{" + token + "}}")
        else:
            value = esc_text(piece)
            value = re.sub(r"\*\*(.+?)\*\*", r"\\textbf{\1}", value)
            result.append(value)
    return "".join(result)


ITEM_RE = re.compile(r"^(?:- |\d+\. )(.+)$")


def is_block_start(line: str) -> bool:
    stripped = line.strip()
    return (
        not stripped
        or stripped == "---"
        or line.startswith("#")
        or line.startswith("|")
        or stripped.startswith("```")
        or stripped.startswith("$$")
        or ITEM_RE.match(line) is not None
    )


def finish_display_math(body: list[str]) -> list[str]:
    """Typeset trailing Chinese sentence punctuation inside the display line."""
    if body:
        stripped = body[-1].rstrip()
        if stripped and stripped[-1] in "。，；：":
            body[-1] = stripped[:-1] + r"\text{" + stripped[-1] + "}"
    return [r"\[", *body, r"\]", ""]


def emit_display_math(lines: list[str], i: int, out: list[str]) -> int:
    first = lines[i].strip()[2:]
    body = []
    if first.endswith("$$"):
        content = first[:-2].strip()
        if content:
            body.append(content)
        out.extend(finish_display_math(body))
        return i + 1
    if first.strip():
        body.append(first.rstrip())
    i += 1
    while i < len(lines):
        line = lines[i]
        if line.strip().endswith("$$"):
            before = line[: line.rfind("$$")].rstrip()
            if before.strip():
                body.append(before)
            out.extend(finish_display_math(body))
            return i + 1
        body.append(line)
        i += 1
    raise ValueError("unclosed display math")


def emit_list(lines: list[str], i: int, out: list[str]) -> int:
    ordered = bool(re.match(r"^\d+\. ", lines[i]))
    env = "enumerate" if ordered else "itemize"
    out.append(r"\begin{%s}" % env)
    while i < len(lines):
        match = ITEM_RE.match(lines[i])
        if match is None:
            break
        if bool(re.match(r"^\d+\. ", lines[i])) != ordered:
            break
        parts = [match.group(1).strip()]
        i += 1
        while i < len(lines) and lines[i].strip() and not is_block_start(lines[i]):
            parts.append(lines[i].strip())
            i += 1
        out.append(r"\item " + inline(" ".join(parts)))
        if i < len(lines) and not lines[i].strip():
            j = i + 1
            while j < len(lines) and not lines[j].strip():
                j += 1
            next_match = ITEM_RE.match(lines[j]) if j < len(lines) else None
            if next_match and bool(re.match(r"^\d+\. ", lines[j])) == ordered:
                i = j
    out.extend([r"\end{%s}" % env, ""])
    return i


def emit_paragraph(lines: list[str], i: int, out: list[str]) -> int:
    parts = []
    while i < len(lines) and not is_block_start(lines[i]):
        parts.append(lines[i].strip())
        i += 1
    if not parts:
        raise ValueError(f"empty paragraph at line: {lines[i]!r}")
    out.extend([inline(" ".join(parts)), ""])
    return i


def split_table_row(line: str) -> list[str]:
    """Split a Markdown table row without breaking `|` inside math or code."""
    text = line.strip()
    if text.startswith("|"):
        text = text[1:]
    if text.endswith("|"):
        text = text[:-1]
    cells: list[str] = []
    buf: list[str] = []
    in_math = False
    in_code = False
    for char in text:
        if char == "$" and not in_code:
            in_math = not in_math
        elif char == "`" and not in_math:
            in_code = not in_code
        if char == "|" and not in_math and not in_code:
            cells.append("".join(buf).strip())
            buf = []
        else:
            buf.append(char)
    cells.append("".join(buf).strip())
    return cells


def emit_table(table_lines: list[str]) -> list[str]:
    rows = []
    for line in table_lines:
        stripped = line.strip()
        if re.fullmatch(r"[|\-:\s]+", stripped):
            continue
        rows.append(split_table_row(stripped))
    if not rows:
        return []
    cols = len(rows[0])
    out = [r"\begin{OIDataTable}{|" + "|".join(["c"] * cols) + "|}"]
    for index, row in enumerate(rows):
        if len(row) != cols:
            raise ValueError(f"table row has {len(row)} cells, expected {cols}: {row!r}")
        out.append(" & ".join(inline(cell) for cell in row) + r"\\\hline")
    out.append(r"\end{OIDataTable}")
    return out


def strip_sample_reference(text: str) -> str:
    text = re.sub(
        r"^见(?:下发文件|选手目录)(?:中|下的)?[^。]*。",
        "",
        text,
    ).strip()
    if text in ("本组为公开大样例，不计入正式测试点。", ""):
        return ""
    return text


def parse_problems(statement: str) -> list[tuple[str, str, list[str]]]:
    starts = []
    for match in re.finditer(r"^#\s+(.+?)（([a-z0-9][a-z0-9_-]*)）\s*$", statement, flags=re.M):
        starts.append((match.start(), match.group(1).strip(), match.group(2)))
    result = []
    for index, (start, name, slug) in enumerate(starts):
        end = starts[index + 1][0] if index + 1 < len(starts) else len(statement)
        result.append((name, slug, statement[start:end].splitlines()[1:]))
    return result


def data_range_need(lines: list[str], start: int) -> int:
    """Estimate the height of the final data-range block in text baselines."""
    rows = 0
    other = 0
    j = start + 1
    while j < len(lines) and not lines[j].startswith("## "):
        stripped = lines[j].strip()
        if stripped.startswith("|"):
            if not re.fullmatch(r"[|\-:\s]+", stripped):
                rows += 1
        elif stripped:
            other += 1
        j += 1
    if rows == 0:
        rows = 4
    return min(30, 1 + other + int(rows * 1.1))


def problem_tex(name: str, slug: str, lines: list[str]) -> str:
    out = [r"\OIProblem{%s}{%s}" % (name, slug), ""]
    i = 0
    while i < len(lines):
        line = lines[i]
        if not line.strip() or line.strip() == "---":
            i += 1
            continue
        if line.startswith("## "):
            title = line[3:].strip()
            extra = re.fullmatch(r"【样例\s*(\d+)】", title)
            sample = re.fullmatch(r"【样例\s*(\d+)\s*(输入|输出)】", title)
            if extra:
                number = int(extra.group(1))
                out.append(r"\OIAdditionalSample{%d}{%s/%s}" % (number, slug, slug))
                i += 1
                while i < len(lines) and not lines[i].strip():
                    i += 1
                if i < len(lines) and not lines[i].startswith("#"):
                    remaining = strip_sample_reference(lines[i].strip())
                    if remaining:
                        out.extend([inline(remaining), ""])
                    i += 1
                continue
            if sample:
                number = int(sample.group(1))
                kind = sample.group(2)
                i += 1
                while i < len(lines) and not lines[i].strip():
                    i += 1
                if i >= len(lines) or lines[i].strip() != "```text":
                    raise ValueError(f"sample {number} {kind} is not followed by a text fence")
                i += 1
                body = []
                while i < len(lines) and lines[i].strip() != "```":
                    body.append(lines[i])
                    i += 1
                if i >= len(lines):
                    raise ValueError("unclosed sample fence")
                out.append(r"\begin{OISample}{%d}{%s}" % (number, kind))
                out.extend(body)
                out.append(r"\end{OISample}")
                i += 1
                continue
            section = title.strip("【】")
            if section == "数据范围":
                out.append(r"\Needspace{%d\baselineskip}" % data_range_need(lines, i))
            out.extend([r"\OISection{%s}" % section, ""])
            i += 1
            continue
        if line.startswith("|"):
            table = []
            while i < len(lines) and lines[i].startswith("|"):
                table.append(lines[i])
                i += 1
            out.extend(emit_table(table))
            out.append("")
            continue
        if line.startswith("- ") or re.match(r"^\d+\. ", line):
            i = emit_list(lines, i, out)
            continue
        if line.strip().startswith("$$"):
            i = emit_display_math(lines, i, out)
            continue
        if line.strip().startswith("```"):
            i += 1
            body = []
            while i < len(lines) and lines[i].strip() != "```":
                body.append(esc_text(lines[i]))
                i += 1
            if i >= len(lines):
                raise ValueError("unclosed generic code fence")
            out.extend([r"\begin{quote}\ttfamily", *body, r"\end{quote}", ""])
            i += 1
            continue
        i = emit_paragraph(lines, i, out)
    return "\n".join(out).rstrip() + "\n"


def cover(subtitle: str, problems: list[tuple[str, str, list[str]]]) -> str:
    names = [name for name, _, _ in problems]
    slugs = [slug for _, slug, _ in problems]
    row = lambda label, values: (
        label + " & " + " & ".join(values) + r"\\\hline"
    )
    table_rows = [
        row("题目名称", names),
        row("题目类型", ["传统型"] * 4),
        row("目录", [r"{\ttfamily " + slug + "}" for slug in slugs]),
        row("可执行文件名", [r"{\ttfamily " + slug + "}" for slug in slugs]),
        row("输入文件名", [r"{\ttfamily " + slug + ".in}" for slug in slugs]),
        row("输出文件名", [r"{\ttfamily " + slug + ".out}" for slug in slugs]),
        row("每个测试点时限", ["1.0 秒"] * 4),
        row("内存限制", ["512 MiB"] * 4),
        row("测试点数目", ["10"] * 4),
        row("测试点是否等分", ["是，每点 10 分"] * 4),
    ]
    compile_row = row("对于 C++ 语言", [r"{\ttfamily " + slug + ".cpp}" for slug in slugs])
    return rf"""\documentclass[11pt,a4paper]{{article}}
\usepackage{{oi-statement}}
\OISetup{{CSP-J 模拟赛}}{{{subtitle}}}{{入门级}}
\OISetCompileOptions{{-O2 -std=c++14}}
\begin{{document}}
\OICoverTitle
\OICoverTable{{4}}{{
{os.linesep.join(table_rows)}
}}
\OICompilation{{4}}{{
{compile_row}
}}
\OICoverNotes
\begin{{enumerate}}
\item 本套为 CSP-J 训练模拟赛，共 4 题，每题 100 分，总分 400 分。
\item 各题均采用标准输入输出，提交对应的同名 C++ 源程序。
\item 每题有 10 个测试点，每点 10 分，按测试点独立计分。
\item 答案采用普通文本比较，忽略行末空格和文件末尾多余换行。
\item 题面样例与下发大样例不计入正式测试点。
\item 程序可使用的栈空间与题目的内存限制一致。
\item 样例框左侧行号不属于输入输出。
\item 使用 C++14，编译选项为 \texttt{{-O2 -std=c++14}}。
\end{{enumerate}}
"""


def build_tex(zip_path: Path, cfg: dict) -> tuple[Path, list[tuple[str, str, list[str]]]]:
    work = OUT / zip_path.stem
    work.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(zip_path) as zf:
        statement = read_text(zf, "statement.md")
    problems = parse_problems(statement)
    expected = {
        "第四套_V3.8_完整重构包.zip": ["chain", "sumsq", "necklace", "eval"],
        "第五套_V3.8_完整重构包.zip": ["date", "purchase", "divisible", "green"],
        "第六套_V3.8_完整重构包.zip": ["maxmod", "crossmul", "triples", "splitnum"],
        "第七套_V3.8_完整重构包.zip": ["palindrome", "quad", "files", "leafcut"],
    }[zip_path.name]
    if [slug for _, slug, _ in problems] != expected:
        raise ValueError(f"unexpected problem order in {zip_path.name}")
    tex = [cover(cfg["subtitle"], problems)]
    tex.extend(problem_tex(name, slug, lines) for name, slug, lines in problems)
    tex.append(r"\end{document}" + "\n")
    source = work / "statement.tex"
    source.write_text("\n".join(tex), encoding="utf-8")
    return source, problems


def compile_pdf(source: Path) -> Path:
    pdf = source.with_suffix(".pdf")
    report = source.with_name("statement-build.json")
    command = [
        str(PYTHON),
        str(SKILL / "scripts" / "build_statement.py"),
        str(source),
        str(pdf),
        "--engine",
        str(TECTONIC),
        "--report",
        str(report),
    ]
    result = subprocess.run(
        command,
        text=True,
        encoding="utf-8",
        errors="replace",
        capture_output=True,
    )
    if result.returncode:
        raise RuntimeError(result.stdout + result.stderr)
    return pdf


def repack(zip_path: Path, pdfs: dict[str, Path]) -> None:
    STAGING.mkdir(parents=True, exist_ok=True)
    replacement = STAGING / zip_path.name
    temporary = replacement.with_suffix(".zip.tmp")
    with zipfile.ZipFile(zip_path) as source, zipfile.ZipFile(
        temporary, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=6
    ) as target:
        for info in source.infolist():
            if info.filename in pdfs or info.is_dir():
                continue
            target.writestr(info, source.read(info.filename))
        for name, path in pdfs.items():
            target.write(path, name)
    os.replace(temporary, replacement)
    with zipfile.ZipFile(replacement) as zf:
        bad = zf.testzip()
        if bad is not None:
            raise RuntimeError(f"corrupt archive member: {bad}")
        names = zf.namelist()
        if len(names) != len(set(names)):
            raise RuntimeError("duplicate ZIP members")
        required = {"statement.pdf", "solution.pdf", "下发/statement.pdf"}
        if not required.issubset(names):
            raise RuntimeError(f"missing PDFs in {zip_path.name}")
    original = zip_path
    source_dir = original.parent
    shutil.copy2(replacement, source_dir / (original.name + ".new"))
    os.replace(source_dir / (original.name + ".new"), original)


def main() -> None:
    BACKUP.mkdir(parents=True, exist_ok=True)
    OUT.mkdir(parents=True, exist_ok=True)
    records = []
    for filename, cfg in SUITES.items():
        zip_path = CSPJ / filename
        backup = BACKUP / (filename + ".pre_pdf")
        if not backup.exists():
            shutil.copy2(zip_path, backup)
        source, problems = build_tex(zip_path, cfg)
        statement_pdf = compile_pdf(source)
        solution_pdf = OLD_PDF / cfg["old_pdf"] / "solution.pdf"
        if not solution_pdf.is_file():
            raise FileNotFoundError(solution_pdf)
        repack(
            zip_path,
            {
                "statement.pdf": statement_pdf,
                "solution.pdf": solution_pdf,
                "下发/statement.pdf": statement_pdf,
            },
        )
        records.append(
            {
                "package": filename,
                "problems": [slug for _, slug, _ in problems],
                "statement_pdf_sha256": __import__("hashlib").sha256(
                    statement_pdf.read_bytes()
                ).hexdigest(),
                "solution_pdf_sha256": __import__("hashlib").sha256(
                    solution_pdf.read_bytes()
                ).hexdigest(),
            }
        )
        print("packed", filename)
    (OUT / "result.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )


if __name__ == "__main__":
    main()
