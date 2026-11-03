from __future__ import annotations

import subprocess
import sys
import tempfile
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(0, str(Path(__file__).parent))
import audit_details as ad
from audit_v3103 import Package

ROOT = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目")
pkg_path = ROOT / "CSP-J" / "第七套_V3.8_完整重构包.zip"
pkg = Package(pkg_path)
try:
    std_name = "T1/std.cpp"
    data = pkg._zip.read(pkg._originals[std_name])
    print("STD HEAD")
    print(data.decode("utf-8", errors="replace")[:800])
    samples = ad.resolve_samples(pkg, "legacy_cspj_T1-T4", "T1")
    print("FILES", sorted(samples["files"]))
    for name, content in samples["files"].items():
        print("---", name)
        print(content[:300].decode("utf-8", errors="replace"))
finally:
    pkg.close()
