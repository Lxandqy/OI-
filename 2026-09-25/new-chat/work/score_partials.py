from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
import subprocess
import time
import json

p = Path(__file__).parent


def one(t, method, i):
    folder = p / 'built' / f'T{t}' / 'data'
    raw = (folder / f'{i}.in').read_text(encoding='utf-8')
    exp = (folder / f'{i}.out').read_text(encoding='utf-8')
    start = time.perf_counter()
    try:
        name = (f'partial_T{t}.exe' if t <= 2 else f'partial_brute_T{t}.exe') if method == 'brute' else (f'partial_mid_T{t}.exe' if t <= 2 else f'partial_T{t}.exe')
        proc = subprocess.run([str(p / name)], input=raw, text=True,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=4)
        status = 'AC' if proc.returncode == 0 and proc.stdout == exp else ('RE' if proc.returncode else 'WA')
    except subprocess.TimeoutExpired:
        status = 'TLE'
    return t, method, i, status, round(time.perf_counter() - start, 3)


results = []
with ThreadPoolExecutor(max_workers=4) as pool:
    jobs = [pool.submit(one, t, method, i) for t in range(1, 5) for method in ('brute', 'mid') for i in range(1, 11)]
    for job in as_completed(jobs):
        results.append(job.result())
results.sort()
for t in range(1, 5):
    for method in ('brute', 'mid'):
        rows = [x for x in results if x[0] == t and x[1] == method]
        print(f'T{t} {method}:', [(i, status) for _, _, i, status, _ in rows], 'score', 10 * sum(status == 'AC' for _, _, _, status, _ in rows), flush=True)
(p / 'partial_scores.json').write_text(json.dumps(results, indent=2), encoding='utf-8')
