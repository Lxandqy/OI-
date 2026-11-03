import sys
from pathlib import Path

sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")
from oi_common import extract_fences, normalize_source, split_problems

root = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
text = root / ".audit" / "text" / "CSP-J" / "第七套_V3.8_完整重构包.zip" / "solution.md"
std = root / ".audit" / "std_stage" / "CSP-J-第七套_V3.8_完整重构包" / "files.cpp"
solution = text.read_text(encoding="utf-8")
raw = text.read_bytes()
print("raw CRLF", raw.count(b"\r\n"), "CRCRLF", raw.count(b"\r\r\n"), "LF", raw.count(b"\n"))
parts = split_problems(solution)
blocks = [c for lang, c, _ in extract_fences(parts["files"]) if lang in ("cpp", "c++")]
target = normalize_source(std.read_text(encoding="utf-8"))
print("blocks", len(blocks), "std bytes", std.stat().st_size)
for index, block in enumerate(blocks):
    print(index, normalize_source(block) == target, len(block))
if blocks:
    a = normalize_source(blocks[0]).splitlines()
    b = target.splitlines()
    import difflib

    print("\n".join(list(difflib.unified_diff(b, a, fromfile="std", tofile="solution"))[:80]))
