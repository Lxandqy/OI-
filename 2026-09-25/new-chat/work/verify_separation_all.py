from pathlib import Path
import subprocess
import time

root = Path(__file__).parent
checks = [
    (1, 'partial_direct_T1', range(3, 5)),
    (1, 'partial_enum_T1', range(5, 7)),
    (1, 'partial_cube_T1', range(7, 9)),
    (1, 'partial_mid_T1', range(15, 21)),
    (2, 'partial_T2', range(3, 5)),
    (2, 'partial_subset_T2', range(5, 9)),
    (2, 'partial_mid_T2', range(15, 21)),
    (3, 'partial_brute_T3', range(3, 9)),
    (3, 'partial_T3', range(13, 21)),
    (4, 'partial_brute_T4', range(3, 9)),
    (4, 'partial_T4', range(15, 21)),
]

for t, name, points in checks:
    for i in points:
        folder = root / 'built' / f'T{t}' / 'data'
        raw = (folder / f'{i}.in').read_text(encoding='utf-8')
        expected = (folder / f'{i}.out').read_text(encoding='utf-8')
        limit = 2 if t == 1 else 4
        start = time.perf_counter()
        try:
            proc = subprocess.run([str(root / (name + '.exe'))], input=raw, text=True,
                                  capture_output=True, timeout=limit)
            status = 'AC' if proc.returncode == 0 and proc.stdout == expected else 'WA/RE'
        except subprocess.TimeoutExpired:
            status = 'TLE'
        elapsed = time.perf_counter() - start
        assert status == 'TLE', (t, name, i, status, round(elapsed, 2))
        print(f'T{t} {name} -> point {i}: {status} {elapsed:.2f}s', flush=True)
print('all new higher-tier scale points reject the preceding slower algorithm', flush=True)
