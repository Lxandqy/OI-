from __future__ import annotations

import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from audit_v3103 import Package


ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
GXX = ROOT / ".audit" / "tools" / "w64devkit" / "w64devkit" / "bin" / "g++.exe"
SOURCE = ROOT / "NOIP" / "第一套 NOIP 模拟卷.zip"


def main() -> None:
    pkg = Package(SOURCE)
    try:
        for slug, number in (("triplet", 3), ("logic", 4)):
            std_name = f"代码/{slug}.cpp"
            assert pkg._zip is not None
            source = pkg._zip.read(pkg._originals[std_name]).decode("utf-8")
            sample_zip = pkg.nested_zip(f"下发/{slug}.zip")
            assert sample_zip is not None
            inp = sample_zip.read(f"{slug}/{slug}{number}.in")
            ans = sample_zip.read(f"{slug}/{slug}{number}.ans")
            sample_zip.close()
            with tempfile.TemporaryDirectory() as tmp:
                work = Path(tmp)
                cpp = work / f"{slug}.cpp"
                exe = work / f"{slug}.exe"
                cpp.write_text(source, encoding="utf-8")
                proc = subprocess.run(
                    [
                        str(GXX),
                        "-O2",
                        "-std=c++14",
                        "-Wl,--stack=536870912",
                        str(cpp),
                        "-o",
                        str(exe),
                    ],
                    capture_output=True,
                )
                print(slug, "compile", proc.returncode)
                for run in range(3):
                    proc = subprocess.run(
                        [str(exe)], input=inp, capture_output=True, timeout=120
                    )
                    got = proc.stdout
                    print(
                        slug,
                        run,
                        "rc",
                        proc.returncode,
                        "got_len",
                        len(got),
                        "ans_len",
                        len(ans),
                        "same",
                        got.decode(errors="replace").split()
                        == ans.decode(errors="replace").split(),
                    )
                    if run == 0:
                        print("got head", got[:300])
                        print("ans head", ans[:300])
    finally:
        pkg.close()


if __name__ == "__main__":
    main()
