import sys
import difflib
from pathlib import Path

sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")
from oi_common import extract_fences, normalize_source, split_problems

base = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\NOIP\NOIP模拟赛-宴会名册")
slug = "invite"
solution = (base / "总题解.md").read_text(encoding="utf-8")
std = (base / "代码" / f"{slug}.cpp").read_text(encoding="utf-8")
parts = split_problems(solution)
blocks = [c for lang, c, _ in extract_fences(parts[slug]) if lang in ("cpp", "c++")]
print("blocks", len(blocks), "match", [normalize_source(b) == normalize_source(std) for b in blocks])
a = normalize_source(blocks[0]).splitlines()
b = normalize_source(std).splitlines()
print("\n".join(list(difflib.unified_diff(b, a, fromfile="std", tofile="solution"))[:100]))
