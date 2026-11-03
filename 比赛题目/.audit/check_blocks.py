import sys
import zipfile
from pathlib import Path

sys.path.insert(0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts")
from oi_common import extract_fences, normalize_source, split_problems

root = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")


def load_dir(package: Path):
    solution = (package / "总题解.md").read_text(encoding="utf-8")
    stds = {
        p.stem: p.read_bytes().decode("utf-8", errors="replace")
        for p in (package / "代码").glob("*.cpp")
    }
    return solution, stds


def load_zip(package: Path):
    with zipfile.ZipFile(package) as zf:
        solution = zf.read("总题解.md").decode("utf-8-sig")
        stds = {
            Path(name).stem: zf.read(name).decode("utf-8", errors="replace")
            for name in zf.namelist()
            if name.startswith("代码/") and name.endswith(".cpp")
        }
    return solution, stds


for package in [
    root / "NOIP" / "NOIP模拟赛-宴会名册",
    root / "NOIP" / "第一套 NOIP 模拟卷.zip",
    root / "NOIP" / "第三套 NOIP 模拟赛",
]:
    solution, stds = load_zip(package) if package.is_file() else load_dir(package)
    parts = split_problems(solution)
    print("==", package.name)
    for slug, section in parts.items():
        if slug not in stds:
            continue
        blocks = [
            (lang, code)
            for lang, code, _ in extract_fences(section)
            if lang in ("cpp", "c++")
        ]
        target = normalize_source(stds[slug])
        print(
            slug,
            "blocks",
            len(blocks),
            "match",
            [normalize_source(code) == target for _, code in blocks],
        )
