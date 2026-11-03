from __future__ import annotations

import itertools
import random
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
OUT = ROOT / ".audit" / "samples"
GXX = ROOT / ".audit" / "tools" / "w64devkit" / "w64devkit" / "bin" / "g++.exe"


def rng_for(slug: str) -> random.Random:
    seed = 20261020 + sum((i + 1) * ord(ch) for i, ch in enumerate(slug))
    return random.Random(seed)


def make_invite() -> str:
    rng = rng_for("invite")
    n, k = 5000, 2500
    lines = [f"{n} {k}"]
    lines += [f"{rng.randrange(n)} {rng.randrange(n)}" for _ in range(n)]
    return "\n".join(lines) + "\n"


def make_river() -> str:
    rng = rng_for("river")
    n = 200000
    length = 1000000000
    xs = [4000 * i + (i * 17) % 97 for i in range(1, n + 1)]
    costs = [rng.randrange(1, 1000000001) for _ in range(n)]
    budget = sum(costs) // 5
    lines = [f"{length} {n} {budget}"]
    lines += [f"{x} {c}" for x, c in zip(xs, costs)]
    return "\n".join(lines) + "\n"


def make_trio() -> str:
    rng = rng_for("trio")
    n = 200000
    lines = [str(n)]
    for i in range(2, n + 1):
        parent = rng.randrange(max(1, i // 3), i) if i > 3 else i - 1
        lines.append(f"{parent} {rng.randrange(1, 1000000001)}")
    return "\n".join(lines) + "\n"


def make_roads() -> str:
    rng = rng_for("roads")
    n = 200000
    lines = [f"{n} {n}"]
    for i in range(2, n + 1):
        lines.append(f"{i - 1} {i} {rng.randrange(1, 1000000001)}")
    lines.append(f"1 {n} {rng.randrange(1, 1000000001)}")
    return "\n".join(lines) + "\n"


def make_relay() -> str:
    rng = rng_for("relay")
    n = m = 500000
    workers = list(range(1, n))
    rng.shuffle(workers)
    tasks = workers[:m]
    rng.shuffle(tasks)
    return f"{n} {m}\n" + " ".join(map(str, tasks)) + "\n"


def make_watch() -> str:
    rng = rng_for("watch")
    n = 200000
    lines = [str(n)]
    for i in range(n):
        left = rng.randrange(1, 1000000001)
        right = min(1000000000, left + rng.randrange(0, 1000000))
        lines.append(f"{left} {right} {rng.randrange(1, 1000000001)}")
    return "\n".join(lines) + "\n"


def make_palpath() -> str:
    rng = rng_for("palpath")
    n = m = 350
    bits = [str(rng.randrange(2)) for _ in range(n * m)]
    weights = [str(rng.randrange(1, 1000000001)) for _ in range(n * m)]
    lines = [f"{n} {m}"]
    lines += [
        " ".join(bits[i * m : (i + 1) * m])
        for i in range(n)
    ]
    lines += [
        " ".join(weights[i * m : (i + 1) * m])
        for i in range(n)
    ]
    return "\n".join(lines) + "\n"


def make_circle() -> str:
    n = 100000
    lines = [f"{n} {n - 1}"]
    lines += [f"{i} {i + 1}" for i in range(1, n)]
    operations = ["3"]
    for i in range(1, n):
        operations.append(f"2 {i} {i + 1}")
        operations.append("3")
    lines.append(str(len(operations)))
    lines += operations
    return "\n".join(lines) + "\n"


def make_bits() -> str:
    rng = rng_for("bits")
    n, k, m = 18, 30, 100000
    lines = [f"{n} {k} {m}"]
    for _ in range(m):
        left = rng.randrange(1, n + 1)
        right = rng.randrange(left, n + 1)
        lines.append(
            f"{rng.choice(['A', 'O'])} {left} {right} {rng.randrange(1 << k)}"
        )
    return "\n".join(lines) + "\n"


def make_cut() -> str:
    rng = rng_for("cut")
    n = 500000
    return f"{n}\n" + " ".join(str(rng.randrange(1, 1000000001)) for _ in range(n)) + "\n"


def make_region() -> str:
    rng = rng_for("region")
    n = 200000
    lines = [str(n), " ".join(str(rng.randrange(-1000000000, 1000000001)) for _ in range(n))]
    lines += [f"{i} {i + 1}" for i in range(1, n)]
    return "\n".join(lines) + "\n"


def make_track() -> str:
    rng = rng_for("track")
    n = 200000
    total = n * (n - 1) * (n - 2) // 6
    k = rng.randrange(1, total + 1)
    lines = [f"{n} 10000 {k}"]
    positions = list(range(0, n * 500, 500))
    rng.shuffle(positions)
    for x in positions:
        lines.append(f"{x} {rng.randrange(-10000, 10001)}")
    return "\n".join(lines) + "\n"


def make_compile() -> str:
    t = 1200
    lines = [str(t)]
    for _ in range(t):
        lines += ["50 1", " ".join(["1"] * 50), "1000000000", "1"]
    return "\n".join(lines) + "\n"


def make_patrol() -> str:
    rng = rng_for("patrol")
    n, d = 200000, 137
    lines = [f"{n} {d}"]
    for i in range(2, n + 1):
        lines.append(f"{rng.randrange(max(1, i - 50), i)} {i}")
    a = list(range(1, n + 1))
    b = list(range(1, n + 1))
    rng.shuffle(a)
    rng.shuffle(b)
    ma, mb = 50000, 60000
    lines.append(str(ma))
    lines.append(" ".join(map(str, a[:ma])))
    lines.append(str(mb))
    lines.append(" ".join(map(str, b[:mb])))
    return "\n".join(lines) + "\n"


def make_repair() -> str:
    rng = rng_for("repair")
    n = 300000
    return f"{n}\n" + " ".join(str(rng.randrange(1, 1000000001)) for _ in range(n)) + "\n"


def make_orcost() -> str:
    rng = rng_for("orcost")
    n, q = 50000, 100000
    lines = [f"{n} {q}", " ".join(str(rng.randrange(1 << 30)) for _ in range(n))]
    for _ in range(q):
        left = rng.randrange(1, n)
        right = rng.randrange(left + 1, n + 1)
        lines.append(f"{left} {right}")
    return "\n".join(lines) + "\n"


def make_lamp() -> str:
    rng = rng_for("lamp")
    n, k, length = 300000, 150000, 1000000
    lines = ["0", f"{n} {k} {length}"]
    for _ in range(n):
        left = rng.randrange(1, 1000000001)
        right = min(1000000000, left + rng.randrange(0, 5000000))
        lines.append(f"{left} {right}")
    return "\n".join(lines) + "\n"


def make_liar() -> str:
    rng = rng_for("liar")
    n = m = 300000
    identities = [0] * n
    for index in rng.sample(range(n), 100000):
        identities[index] = 1
    lines = ["0", f"{n} {m} 100000"]
    for _ in range(m):
        i = rng.randrange(n)
        j = rng.randrange(n - 1)
        if j >= i:
            j += 1
        lines.append(f"{i + 1} {j + 1} {identities[i] ^ identities[j]}")
    return "\n".join(lines) + "\n"


def make_bridge() -> str:
    rng = rng_for("bridge")
    n = m = 300000
    lines = ["0", f"{n} {m}"]
    for i in range(2, n + 1):
        lines.append(f"{i - 1} {i}")
    lines.append(f"1 {n}")
    return "\n".join(lines) + "\n"


def make_park() -> str:
    rng = rng_for("park")
    n, k = 100000, 200
    lines = ["0", f"{n} {k}"]
    lines.append(" ".join(str(rng.randrange(-1000000000, 1000000001)) for _ in range(n)))
    for i in range(2, n + 1):
        lines.append(f"{rng.randrange(max(1, i - 100), i)} {i}")
    return "\n".join(lines) + "\n"


def make_cross() -> str:
    rng = rng_for("cross")
    n = 500000
    return f"{n}\n" + " ".join(str(rng.randrange(1000000001)) for _ in range(n)) + "\n"


def make_password() -> str:
    rng = rng_for("password")
    n, m, k = 5000, 5000, 1000000000
    lines = [f"{n} {m} {k}", " ".join(str(rng.randrange(1, k + 1)) for _ in range(n))]
    for _ in range(m):
        left = rng.randrange(1, k + 1)
        right = rng.randrange(left, k + 1)
        lines.append(f"{left} {right}")
    return "\n".join(lines) + "\n"


def make_spider() -> str:
    rng = rng_for("spider")
    n = 300000
    labels = [rng.randrange(1, 300001) for _ in range(n)]
    s = rng.randrange(1, n + 1)
    t = rng.randrange(1, n + 1)
    while t == s:
        t = rng.randrange(1, n + 1)
    return f"{n}\n" + " ".join(map(str, labels)) + f"\n{s} {t}\n"


def make_tree() -> str:
    rng = rng_for("tree")
    n = 200000
    lines = [str(n)]
    lines.append(" ".join(str(rng.randrange(max(1, i - 50), i)) for i in range(2, n + 1)))
    for _ in range(n):
        left = rng.randrange(1, 1000000001)
        right = rng.randrange(left, 1000000001)
        lines.append(f"{left} {right}")
    return "\n".join(lines) + "\n"


def make_product() -> str:
    rng = rng_for("product")
    n = 200000
    left = 93000
    right = 200000
    return (
        f"{n} {left} {right}\n"
        + " ".join(str(rng.randrange(-2, 3)) for _ in range(n))
        + "\n"
    )


def make_disk() -> str:
    rng = rng_for("disk")
    n = q = 200000
    lines = [f"{n} {q}", " ".join(str(rng.randrange(-1000000000, 1000000001)) for _ in range(n))]
    for _ in range(q):
        lines.append(f"{rng.randrange(1, n + 1)} {rng.randrange(1, 1000000000001)}")
    return "\n".join(lines) + "\n"


def make_gcdforest() -> str:
    rng = rng_for("gcdforest")
    n = 200000
    lines = [str(n), " ".join(str(rng.randrange(1, 200001)) for _ in range(n))]
    for i in range(2, n + 1):
        lines.append(f"{rng.randrange(max(1, i - 100), i)} {i} {rng.randrange(1, 1000000001)}")
    return "\n".join(lines) + "\n"


def make_joint() -> str:
    rng = rng_for("joint")
    n = m = q = 200000
    lines = [f"{n} {m} {q}"]
    for i in range(2, n + 1):
        lines.append(f"{i - 1} {i} {rng.randrange(1, 1000000001)}")
    lines.append(f"1 {n} {rng.randrange(1, 1000000001)}")
    for _ in range(q):
        lines.append(f"1 {rng.randrange(1, m + 1)}")
    return "\n".join(lines) + "\n"


def make_xor4() -> str:
    rng = rng_for("xor4")
    n, m = 200000, 4
    masks = [rng.randrange(1 << 30) for _ in range(m)]
    values = [rng.randrange(-1000000000, 1000000001) for _ in range(n)]
    return (
        f"{n} {m}\n"
        + " ".join(map(str, masks))
        + "\n"
        + " ".join(map(str, values))
        + "\n"
    )


def make_triplet() -> str:
    n = 299997
    edges = [(1, 2), (2, 3), (3, 1)]
    edges += [(i - 1, i) for i in range(4, n + 1)]
    return f"{n}\n" + "\n".join(f"{u} {v}" for u, v in edges) + "\n"


def make_menu() -> str:
    rng = rng_for("menu")
    n, m, c = 50000, 200000, 22
    lines = [f"{n} {m} {c}"]
    lines.append(" ".join(str(rng.randrange(1, c + 1)) for _ in range(m)))
    for _ in range(n):
        lines.append("".join("1" if rng.random() < 0.35 else "0" for _ in range(c)))
    return "\n".join(lines) + "\n"


def make_logic() -> str:
    n, rank = 50, 10
    rows = [
        "1" * (rank + 1) + "1" * (n - rank - 1),
    ]
    # Seed vectors span the first ten coordinates; the affine offset is one.
    vectors = [1 << i for i in range(rank)]
    values = []
    for mask in range(1 << rank):
        value = 1
        for bit in range(rank):
            if mask >> bit & 1:
                value ^= vectors[bit]
        values.append(format(value, f"0{n}b"))
    return f"{n} {len(values)}\n" + "\n".join(values) + "\n"


GENERATORS = {
    "invite": make_invite,
    "river": make_river,
    "trio": make_trio,
    "roads": make_roads,
    "relay": make_relay,
    "watch": make_watch,
    "palpath": make_palpath,
    "circle": make_circle,
    "bits": make_bits,
    "cut": make_cut,
    "region": make_region,
    "track": make_track,
    "compile": make_compile,
    "patrol": make_patrol,
    "repair": make_repair,
    "orcost": make_orcost,
    "lamp": make_lamp,
    "liar": make_liar,
    "bridge": make_bridge,
    "park": make_park,
    "cross": make_cross,
    "password": make_password,
    "spider": make_spider,
    "tree": make_tree,
    "product": make_product,
    "disk": make_disk,
    "gcdforest": make_gcdforest,
    "joint": make_joint,
    "xor4": make_xor4,
    "triplet": make_triplet,
    "menu": make_menu,
    "logic": make_logic,
}


PACKAGES = {
    "meeting": ("NOIP模拟赛-宴会名册", "std", 2),
    "third": (
        "第三套 NOIP 模拟赛",
        "file",
        {"relay": 2, "watch": 2, "palpath": 2, "circle": 3},
    ),
    "fourth": ("第四套 NOIP 模拟赛", "file", 4),
    "sixth": (
        "第六套 NOIP 模拟赛",
        "file",
        {"product": 3, "disk": 3, "gcdforest": 2, "joint": 2},
    ),
    "second": ("第二套 NOIP 模拟卷", "file", 4),
    "cc": (
        "NOIP模拟赛-第二套-CC版.zip",
        "file",
        {"lamp": 3, "liar": 4, "bridge": 3, "park": 3},
    ),
    "fifth": ("第五套 NOIP 模拟赛.zip", "file", 3),
    "first": (
        "第一套 NOIP 模拟卷.zip",
        "std",
        {"xor4": 4, "triplet": 3, "menu": 4, "logic": 4},
    ),
}


def read_member(pkg: Package, name: str) -> bytes:
    if pkg.is_zip:
        assert pkg._zip is not None
        return pkg._zip.read(pkg._originals[name])
    return (pkg.path / Path(name)).read_bytes()


def find_std(pkg: Package, slug: str) -> str:
    candidates = (
        f"代码/{slug}.cpp",
        f"std/{slug}/{slug}.cpp",
        f"std/{slug}.cpp",
    )
    for name in candidates:
        if name in pkg.names:
            return name
    raise FileNotFoundError(f"{pkg.path}: no std for {slug}")


def decode_source(raw: bytes) -> str:
    for encoding in ("utf-8", "gbk"):
        try:
            return raw.decode(encoding)
        except UnicodeDecodeError:
            pass
    raise UnicodeDecodeError("utf-8", raw, 0, 1, "unknown source encoding")


def compile_std(source: Path, exe: Path) -> None:
    proc = subprocess.run(
        [
            str(GXX),
            "-O2",
            "-std=c++14",
            "-Wl,--stack=536870912",
            str(source),
            "-o",
            str(exe),
        ],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        timeout=120,
    )
    if proc.returncode:
        raise RuntimeError(proc.stderr[-2000:])


def run_sample(exe: Path, slug: str, io: str, text: str) -> str:
    with tempfile.TemporaryDirectory(prefix="oi-sample-") as tmp:
        work = Path(tmp)
        if io == "file":
            (work / f"{slug}.in").write_text(text, encoding="ascii")
            proc = subprocess.run(
                [str(exe)],
                cwd=work,
                capture_output=True,
                timeout=180,
            )
            if proc.returncode:
                raise RuntimeError(
                    f"{slug} exited {proc.returncode}: "
                    + proc.stderr.decode(errors="replace")[-1000:]
                )
            out = work / f"{slug}.out"
            if not out.exists():
                raise RuntimeError(f"{slug}: no {slug}.out")
            return out.read_text(encoding="utf-8", errors="replace")
        proc = subprocess.run(
            [str(exe)],
            input=text.encode("ascii"),
            capture_output=True,
            timeout=180,
        )
        if proc.returncode:
            raise RuntimeError(
                f"{slug} exited {proc.returncode}: "
                + proc.stderr.decode(errors="replace")[-1000:]
            )
        return proc.stdout.decode("utf-8", errors="replace")


def main() -> None:
    if len(sys.argv) > 1:
        wanted = set(sys.argv[1:])
    else:
        wanted = set(PACKAGES)
    for key, (name, io, sample_config) in PACKAGES.items():
        if key not in wanted:
            continue
        package_path = ROOT / "NOIP" / name
        pkg = Package(package_path)
        print(f"\n## {key}: {name}", flush=True)
        try:
            slugs = [
                Path(n).stem
                for n in pkg.names
                if n.startswith("代码/") and n.endswith(".cpp")
            ]
            if not slugs:
                slugs = [
                    Path(n).stem
                    for n in pkg.names
                    if n.startswith("std/") and n.endswith(".cpp")
                ]
            for slug in sorted(set(slugs)):
                if slug not in GENERATORS:
                    raise KeyError(f"no generator for {slug}")
                sample_number = (
                    sample_config[slug]
                    if isinstance(sample_config, dict)
                    else sample_config
                )
                target = OUT / key / slug
                target.mkdir(parents=True, exist_ok=True)
                input_text = GENERATORS[slug]()
                (target / f"{slug}{sample_number}.in").write_text(
                    input_text, encoding="ascii"
                )
                source = ROOT / ".audit" / "sample_build" / f"{key}-{slug}.cpp"
                source.parent.mkdir(parents=True, exist_ok=True)
                source.write_text(
                    decode_source(read_member(pkg, find_std(pkg, slug))),
                    encoding="utf-8",
                )
                exe = source.with_suffix(".exe")
                compile_std(source, exe)
                output_text = run_sample(exe, slug, io, input_text)
                (target / f"{slug}{sample_number}.ans").write_text(
                    output_text, encoding="ascii"
                )
                print(
                    f"  {slug}: in={len(input_text.encode())/1024:.1f} KiB "
                    f"out={len(output_text.encode())/1024:.1f} KiB",
                    flush=True,
                )
        finally:
            pkg.close()


if __name__ == "__main__":
    main()
