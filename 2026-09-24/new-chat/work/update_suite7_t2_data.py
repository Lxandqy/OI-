"""Rebuild the three intermediate subtask cases for suite 7, task 2."""

from bisect import bisect_left, insort
from pathlib import Path
import random
import subprocess
import zipfile


ROOT = Path(__file__).parent
SOURCE = ROOT / "source7" / "T2" / "judge" / "data"
BUILT = ROOT / "built" / "suite7_full" / "T2" / "data"
GPP = Path("D:/Dev-Cpp/MinGW64/bin/g++.exe")
EXE = ROOT / "bin" / "suite7_t2_updated.exe"


def count_quadruples(a):
    n = len(a)
    answer = 0
    prefix = []
    for j in range(1, n - 2):
        insort(prefix, a[j - 1])
        greater = 0
        for k in range(n - 1, j, -1):
            if a[k] < a[j]:
                answer += bisect_left(prefix, a[k]) * greater
            if a[k] > a[j]:
                greater += 1
    return answer


def main():
    EXE.parent.mkdir(exist_ok=True)
    subprocess.run([str(GPP), "-std=c++14", "-O2",
                    str(ROOT / "built" / "suite7_full" / "T2" / "std.cpp"),
                    "-o", str(EXE)], check=True)
    rng = random.Random(20260924)
    cases = {
        3: rng.sample(range(-1_000_000, 1_000_000), 700),
        4: [rng.randrange(-80, 81) for _ in range(750)],
        5: [0] * 200 + [2] * 200 + [1] * 200 + [3] * 200,
    }
    for case, a in cases.items():
        content = f"{len(a)}\n" + " ".join(map(str, a)) + "\n"
        expected = count_quadruples(a)
        program = subprocess.run([str(EXE)], input=content.encode(),
                                 capture_output=True, timeout=5, check=True)
        assert program.stdout.decode().strip() == str(expected), case
        for folder in (SOURCE, BUILT):
            (folder / f"{case}.in").write_text(content, encoding="utf-8", newline="\n")
            (folder / f"{case}.out").write_text(f"{expected}\n", encoding="utf-8", newline="\n")
        print(f"case {case}: n={len(a)}, answer={expected}")

    archive = ROOT / "built" / "suite7_full" / "T2" / "data.zip"
    with zipfile.ZipFile(archive, "w", compression=zipfile.ZIP_DEFLATED) as z:
        for path in sorted(BUILT.iterdir(), key=lambda p: (int(p.stem), p.suffix)):
            z.write(path, path.name)
    print("rebuilt", archive)


if __name__ == "__main__":
    main()
