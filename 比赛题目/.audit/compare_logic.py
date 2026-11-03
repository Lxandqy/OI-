import sys
import difflib
from pathlib import Path

sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")
from oi_common import extract_fences, normalize_source, split_problems

root = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
solution = (
    root
    / ".audit"
    / "text"
    / "NOIP"
    / "第一套 NOIP 模拟卷.zip"
    / "总题解.md"
).read_text(encoding="utf-8")
std = (
    root
    / ".audit"
    / "std_stage"
    / "NOIP-第一套 NOIP 模拟卷"
    / "logic.cpp"
).read_text(encoding="utf-8")
parts = split_problems(solution)
blocks = [c for lang, c, _ in extract_fences(parts["logic"]) if lang in ("cpp", "c++")]
print("blocks", len(blocks))
for index, block in enumerate(blocks):
    print(index, normalize_source(block) == normalize_source(std))
a = normalize_source(blocks[0]).splitlines()
b = normalize_source(std).splitlines()
print("\n".join(list(difflib.unified_diff(b, a, fromfile="std", tofile="solution"))[:100]))
