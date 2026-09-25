"""Check every published sample against its statement and rebuilt std.cpp."""

from pathlib import Path
import re
import subprocess


ROOT = Path(__file__).parent
GPP = Path("D:/Dev-Cpp/MinGW64/bin/g++.exe")
BIN = ROOT / "bin"
BIN.mkdir(exist_ok=True)
total = 0

for suite in range(4, 8):
    for task in range(1, 5):
        source = ROOT / f"source{suite}" / f"T{task}" / "release" / "sample"
        built = ROOT / "built" / f"suite{suite}_full" / f"T{task}"
        statement = (built / "statement.md").read_text(encoding="utf-8")
        samples = sorted(source.glob("sample*.in"), key=lambda p: int(re.search(r"\d+", p.stem).group()))
        assert samples, (suite, task)
        exe = BIN / f"sample_s{suite}t{task}.exe"
        subprocess.run([str(GPP), "-std=c++14", "-O2", str(built / "std.cpp"),
                        "-o", str(exe)], capture_output=True, check=True)
        for inp in samples:
            expected = inp.with_suffix(".out").read_text(encoding="utf-8")
            raw_input = inp.read_text(encoding="utf-8")
            assert "```text\n" + raw_input.strip() + "\n```" in statement, (suite, task, inp.name, "input absent")
            assert "```text\n" + expected.strip() + "\n```" in statement, (suite, task, inp.name, "output absent")
            if (suite, task) in ((4, 4), (5, 4)):
                name = "eval" if (suite, task) == (4, 4) else "green"
                scratch = ROOT / "sample_io"
                scratch.mkdir(exist_ok=True)
                (scratch / f"{name}.in").write_bytes(inp.read_bytes())
                subprocess.run([str(exe)], cwd=scratch, capture_output=True, timeout=10, check=True)
                actual = (scratch / f"{name}.out").read_text(encoding="utf-8")
            else:
                actual = subprocess.run([str(exe)], input=inp.read_bytes(),
                                        capture_output=True, timeout=10, check=True).stdout.decode()
            assert actual.split() == expected.split(), (suite, task, inp.name, "wrong answer")
            total += 1
        print(f"S{suite}T{task}: {len(samples)} statement samples checked", flush=True)

print(f"PASS: {total} samples match statement text and std.cpp output")
