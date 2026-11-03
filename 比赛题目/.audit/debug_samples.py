from __future__ import annotations

import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8")
sys.path.insert(
    0, r"C:\Users\Administrator\.codex\skills\oi-contest-authoring\scripts"
)
from oi_common import extract_samples

p = Path(
    r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\text\CSP-J\CSP-J模拟赛第一套.zip\statement.md"
)
text = p.read_text(encoding="utf-8")
try:
    samples = extract_samples(text)
    print("samples", sorted(samples), len(samples))
    for k, v in sorted(samples.items())[:3]:
        print(k, {kk: len(vv) for kk, vv in v.items()})
except Exception as exc:
    print("ERROR", type(exc).__name__, exc)
