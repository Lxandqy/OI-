from __future__ import annotations

import json
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import Package, first_name, headings, slug_from_heading  # noqa: E402


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit"


def normalize(code: str) -> str:
    code = code.replace("\r\n", "\n").replace("\r", "\n")
    return "\n".join(line.rstrip() for line in code.split("\n")).strip()


def cpp_blocks(text: str) -> list[str]:
    return re.findall(r"```(?:cpp|c\+\+)\s*\n(.*?)```", text, re.S | re.I)


def split_h1(text: str) -> dict[str, str]:
    matches = list(re.finditer(r"^#\s+(.+)$", text, re.M))
    result = {}
    for i, match in enumerate(matches):
        end = matches[i + 1].start() if i + 1 < len(matches) else len(text)
        result[match.group(1).strip()] = text[match.start():end]
    return result


def std_path(names: list[str], slug: str, fmt: str) -> str | None:
    if fmt == "legacy_cspj_T1-T4":
        candidates = [f"{slug}/std.cpp"]
    else:
        candidates = [
            f"std/{slug}/{slug}.cpp",
            f"std/{slug}.cpp",
            f"代码/{slug}.cpp",
        ]
    for candidate in candidates:
        if candidate in names:
            return candidate
    return None


def section_for(sections: dict[str, str], slug: str) -> str | None:
    for heading, body in sections.items():
        if slug_from_heading(heading) == slug:
            return body
    for heading, body in sections.items():
        if slug in heading:
            return body
    return None


def main() -> None:
    records = []
    for category in ("CSP-J", "NOIP"):
        folder = ROOT / category
        for child in sorted(folder.iterdir()):
            if not (child.is_dir() or child.suffix.lower() == ".zip"):
                continue
            pkg = Package(child)
            try:
                names = pkg.names
                statement = first_name(names, ["statement.md", "总题面.md", "题面.md"])
                solution = first_name(names, ["solution.md", "总题解.md", "题解.md"])
                stmt = pkg.read_text(statement) if statement else ""
                sol = pkg.read_text(solution) if solution else ""
                stmt_slugs = [s for h in headings(stmt) if (s := slug_from_heading(h))]
                legacy_t = sorted({n.split("/", 1)[0] for n in names if re.match(r"T\d+/", n)})
                slugs = legacy_t or stmt_slugs
                if not slugs:
                    # Fall back to solution headings and data/code names.
                    slugs = [s for h in headings(sol) if (s := slug_from_heading(h))]
                sections = split_h1(sol)
                problems = []
                for slug in slugs:
                    if legacy_t:
                        body = pkg.read_text(f"{slug}/solution.md") if f"{slug}/solution.md" in names else ""
                        std_name = std_path(names, slug, "legacy_cspj_T1-T4")
                    else:
                        body = section_for(sections, slug) or sol
                        std_name = std_path(names, slug, "noip_zip" if any(n.startswith("data/") and n.endswith(".zip") for n in names) else "generic_dir")
                    std_text = pkg.read_text(std_name) if std_name else ""
                    blocks = cpp_blocks(body)
                    exact = any(normalize(block) == normalize(std_text) for block in blocks) if std_text else False
                    similarity = 0.0
                    diff = ""
                    if std_text and blocks and not exact:
                        std_norm = normalize(std_text)
                        ranked = sorted(
                            blocks,
                            key=lambda block: difflib.SequenceMatcher(
                                None, normalize(block), std_norm
                            ).ratio(),
                            reverse=True,
                        )
                        best = normalize(ranked[0])
                        similarity = difflib.SequenceMatcher(None, best, std_norm).ratio()
                        diff = "\n".join(
                            difflib.unified_diff(
                                std_norm.splitlines(),
                                best.splitlines(),
                                fromfile="std",
                                tofile="solution-block",
                                lineterm="",
                            )
                        )
                    std_banned = []
                    if std_text:
                        for name, pattern in {
                            "auto": r"\bauto\b",
                            "decltype": r"\bdecltype\b",
                            "std::function": r"\bstd\s*::\s*function\b",
                            "lambda": r"\[[^\]\n]*\]\s*\(",
                            "#define int": r"#\s*define\s+int\b",
                        }.items():
                            if re.search(pattern, std_text):
                                std_banned.append(name)
                    problems.append(
                        {
                            "slug": slug,
                            "std": std_name,
                            "cpp_blocks": len(blocks),
                            "std_exact_in_solution": exact,
                            "best_similarity": round(similarity, 4),
                            "diff": diff,
                            "std_banned_tokens": std_banned,
                        }
                    )
                records.append(
                    {
                        "category": category,
                        "package": child.stem if child.suffix.lower() == ".zip" else child.name,
                        "statement": statement,
                        "solution": solution,
                        "problems": problems,
                    }
                )
            finally:
                pkg.close()

    (OUT / "solution_audit.json").write_text(
        json.dumps(records, ensure_ascii=False, indent=2), encoding="utf-8"
    )
    lines = ["# 题解 / std 文本核验", ""]
    for record in records:
        lines.append(f"## {record['category']} / {record['package']}")
        for problem in record["problems"]:
            lines.append(
                f"- `{problem['slug']}`：std={problem['std'] or '缺'}；"
                f"cpp块={problem['cpp_blocks']}；主解逐字匹配="
                f"{'PASS' if problem['std_exact_in_solution'] else 'FAIL'}；"
                f"禁用写法={problem['std_banned_tokens'] or '未命中'}"
            )
        lines.append("")
    (OUT / "solution_audit.md").write_text("\n".join(lines), encoding="utf-8")
    diff_lines = ["# 题解 / std 差异", ""]
    for record in records:
        for problem in record["problems"]:
            if problem["std_exact_in_solution"]:
                continue
            diff_lines.append(
                f"## {record['category']} / {record['package']} / {problem['slug']}\n"
                f"最接近代码块相似度：{problem['best_similarity']:.2%}\n\n"
                f"```diff\n{problem['diff'][:20000]}\n```\n"
            )
    (OUT / "solution_diffs.md").write_text("\n".join(diff_lines), encoding="utf-8")
    print(f"Wrote {OUT / 'solution_audit.json'} and {OUT / 'solution_audit.md'}")


if __name__ == "__main__":
    main()
