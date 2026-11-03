from pathlib import Path
import hashlib

here = Path(__file__).resolve().parent
root = here.parent / "比赛题目"
def target(name):
    p = (root / name).resolve()
    if not p.is_relative_to(root.resolve()):
        raise ValueError(name)
    return p
for name in (here / "全部目录.txt").read_text(encoding="utf-8").splitlines():
    target(name).mkdir(parents=True, exist_ok=True)
bad = []
lines = (here / "清单.tsv").read_text(encoding="utf-8").splitlines()[1:]
for line in lines:
    h, size, name = line.split("\t", 2)
    p = target(name)
    if not p.is_file() or p.stat().st_size != int(size):
        bad.append(name)
        continue
    digest = hashlib.sha256()
    with p.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            digest.update(chunk)
    if digest.hexdigest() != h:
        bad.append(name)
print(f"核对 {len(lines)} 个文件；不匹配 {len(bad)} 个。")
for name in bad:
    print(name)
raise SystemExit(bool(bad))
