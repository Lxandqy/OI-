from pathlib import Path
import re

ROOT = Path(__file__).parent / "built"
EXPECTED_DIAGRAMS = {
    (4, 3): 2, (4, 4): 1, (5, 2): 2, (5, 3): 2, (5, 4): 1,
    (6, 2): 3, (6, 4): 3,
}
errors = []
for suite in range(4, 8):
    root = ROOT / f"suite{suite}_full"
    pieces = []
    for task in range(1, 5):
        base = root / f"T{task}"
        text = (base / "solution.md").read_text(encoding="utf-8")
        pieces.append(text.rstrip())
        blocks = re.findall(r"```cpp\n(.*?)\n```", text, re.S)
        heads = re.findall(r"(?m)^## (.+)$", text)
        need = EXPECTED_DIAGRAMS.get((suite, task), 0)
        if text.count("```mermaid\n") != need:
            errors.append((suite, task, "diagram count"))
        if not heads[:2] == ["题意简化", "问题拆分"]:
            errors.append((suite, task, "heading order"))
        if heads[-1] != "知识点总结":
            errors.append((suite, task, "conclusion"))
        if any(not text.startswith(f"## {h}\n\n---\n\n", text.find(f"## {h}")) for h in heads):
            errors.append((suite, task, "heading format"))
        for h in heads:
            if h.startswith("部分分"):
                section = text.split(f"## {h}\n\n---\n\n", 1)[1].split("\n\n## ", 1)[0]
                if "```cpp\n" not in section or not re.search(r"(?m)^1\. ", section):
                    errors.append((suite, task, "partial lacks code or steps", h))
        if not re.search(r"(?m)^1\. .+\n2\. ", text):
            errors.append((suite, task, "split not numbered"))
        if not blocks or blocks[-1].rstrip() != (base / "std.cpp").read_text(encoding="utf-8").rstrip():
            errors.append((suite, task, "std mismatch"))
        prose = re.sub(r"```(?:cpp|mermaid|text)\n.*?\n```", "", text, flags=re.S)
        if prose.count("$") % 2:
            errors.append((suite, task, "math delimiter count"))
        if re.search(r"\b10\^\s+\d", prose):
            errors.append((suite, task, "broken power"))
        print(f"S{suite}T{task}: {len(heads)} H2, {len(blocks)} C++, {need} diagrams")
    if (root / "solution.md").read_text(encoding="utf-8").strip() != "\n\n".join(pieces).strip():
        errors.append((suite, "root mismatch"))
print("ERRORS", errors)
if errors:
    raise SystemExit(1)
