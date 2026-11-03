from __future__ import annotations

import subprocess
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit")
sys.path.insert(0, str(ROOT.parent / ".audit"))
import audit_details as ad
from audit_v3103 import Package

exe = next((ROOT / "build").glob("*第七套*T1.exe"))
pkg = Package(ROOT.parent / "CSP-J" / "第七套_V3.8_完整重构包.zip")
try:
    samples = ad.resolve_samples(pkg, "legacy_cspj_T1-T4", "T1")
    inp = samples["files"]["attachment1.in"].decode()
    expected = samples["files"]["attachment1.out"].decode()
finally:
    pkg.close()
print("exe", exe)
proc = subprocess.run([str(exe)], input=inp.encode(), capture_output=True, timeout=5)
print("rc", proc.returncode)
print("out", proc.stdout.decode(errors="replace")[:200])
print("expected", expected[:200])
print("err", proc.stderr.decode(errors="replace")[:200])
