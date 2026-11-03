from __future__ import annotations

import json
from pathlib import Path


path = Path(r"C:\Users\Administrator\Desktop\OI-\比赛题目\.audit\audit_details.json")
records = json.loads(path.read_text(encoding="utf-8"))

for record in records:
    print(f"## {record['category']} / {record['package']}")
    for p in record["problems"]:
        config = p["config"]["first"] if p["config"] else "NONE"
        print(
            f"{p['slug']}: h1={' | '.join(p['h1']) or 'NONE'}; "
            f"sections={'PASS' if p['has_standard_sections'] else 'FAIL'}; "
            f"inline={p['inline_samples']}; refs={p['distributed_refs']}; "
            f"samples={p['sample_numbers']}; tests={p['test_count']}; "
            f"config={config}"
        )
