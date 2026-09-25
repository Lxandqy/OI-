"""Keep solution prose as Markdown math while preserving actual code blocks."""

from pathlib import Path
import re


FENCE = re.compile(r"(```[^\n]*\n[\s\S]*?\n```)")
INLINE_CODE = re.compile(r"`([^`\n]+)`")

# These are literal syntax or program names, not mathematical expressions.
CODE = {"long long", "*", "+", ".cpp", "题名.cpp", "leftLess[j][k]"}

SPECIAL = {
    "r→g→b→r": r"\mathrm r\to\mathrm g\to\mathrm b\to\mathrm r",
    "r/g/b": r"\mathrm r/\mathrm g/\mathrm b",
    "0..k-1": r"0,\ldots,k-1",
    "p+1..j": r"p+1,\ldots,j",
    "(新色-原色+3)%3": r"(\text{新色}-\text{原色}+3)\bmod 3",
    "i=n": r"i=n",
    "c≠首色": r"c\ne\text{首色}",
    "c=首色": r"c=\text{首色}",
    "0=不选": r"0=\text{不选}",
    "1=选": r"1=\text{选}",
    "0=跳过 a_{i+1}": r"0=\text{跳过 }a_{i+1}",
    "1=选 a_{i+1}": r"1=\text{选 }a_{i+1}",
    "j=下一段的末位": r"j=\text{下一段的末位}",
    "p=总位数,r=0": r"p=\text{总位数},r=0",
    "p=总位数,r≠0": r"p=\text{总位数},r\ne0",
    "c_l·sum(c_l..c_r)": r"c_l\sum_{t=l}^{r}c_t",
    "sum c(c+1)/2": r"\sum_c\frac{c(c+1)}{2}",
    "c(c+1)/2": r"\frac{c(c+1)}{2}",
}


def math_source(value):
    if value in SPECIAL:
        return SPECIAL[value]
    value = value.replace("²", "^2").replace("³", "^3")
    value = re.sub(r"\^\(([^()]*)\)", r"^{\1}", value)
    value = re.sub(r"\bC\(([^,()]+),([^,()]+)\)", r"\\binom{\1}{\2}", value)
    value = re.sub(r"\bdp(?=\[)", r"\\mathrm{dp}", value)
    value = re.sub(r"\bval(?=_)", r"\\mathrm{val}", value)
    for old, new in (
        ("≤", r"\le "), ("≥", r"\ge "), ("≠", r"\ne "),
        ("→", r"\to "), ("·", r"\cdot "), ("×", r"\times "),
        ("⌊", r"\lfloor "), ("⌋", r"\rfloor "),
    ):
        value = value.replace(old, new)
    value = re.sub(r"(?<!\\)\blog\b", r"\\log", value)
    value = re.sub(r"(?<!\\)\bmax\b", r"\\max", value)
    return value


def format_heading(line):
    if not line.startswith("## "):
        return line
    line = line.replace("n≤100/1000", r"$n\le100$ / $n\le1000$")
    return re.sub(
        r"\b([nmk])≤(\d+(?:\^\d+)?)",
        lambda match: "$" + match.group(1) + r"\le" + match.group(2) + "$",
        line,
    )


def format_solution(source):
    parts = FENCE.split(source)
    for i in range(0, len(parts), 2):
        parts[i] = INLINE_CODE.sub(
            lambda match: match.group(0) if match.group(1) in CODE
            else "$" + math_source(match.group(1)) + "$",
            parts[i],
        )
        parts[i] = "\n".join(format_heading(line) for line in parts[i].split("\n"))
    return "".join(parts)


def format_built(root):
    for suite in range(4, 8):
        folder = root / f"suite{suite}_full"
        pieces = []
        for task in range(1, 5):
            path = folder / f"T{task}" / "solution.md"
            content = format_solution(path.read_text(encoding="utf-8"))
            path.write_text(content, encoding="utf-8", newline="\n")
            pieces.append(content.rstrip())
        (folder / "solution.md").write_text(
            "\n\n".join(pieces) + "\n", encoding="utf-8", newline="\n"
        )


if __name__ == "__main__":
    format_built(Path(__file__).parent / "built")
