from pathlib import Path
from random import Random
import subprocess

root = Path(__file__).parent

def run(name, raw):
    p = subprocess.run([str(root / (name + '.exe'))], input=raw, text=True, capture_output=True, timeout=5)
    assert p.returncode == 0, (name, p.stderr)
    return int(p.stdout)

for seed in range(100):
    rng = Random(seed)
    small = [0,1,2,4,8]
    rng.shuffle(small)
    large = [(1 << 29) + v for v in [0,1] + [1 << i for i in range(1, 28)]]
    n = 1000
    bulk_count = n - len(small) - len(large)
    bulk = rng.sample(range(1 << 28, 1 << 29), bulk_count)
    a = small + large + bulk
    first_bulk = len(small) + len(large) + 1
    edges = [(i - 1, i) for i in range(2, len(small) + 1)]
    edges.append((len(small), first_bulk))
    for i in range(first_bulk + 1, n + 1):
        edges.append((rng.randrange(first_bulk, i), i))
    for i in range(len(small) + 1, first_bulk):
        edges.append((rng.randrange(first_bulk, n + 1), i))
    assert len(edges) == n - 1
    raw = str(n) + '\n' + ' '.join(map(str, a)) + '\n' + ''.join(f'{u} {v}\n' for u, v in edges)
    got = tuple(run(name, raw) for name in ('T3','partial_consecutive_T3','partial_neighbor_T3','mutant_T3'))
    if got[0] >= 5 and got[0] != got[1] and got[0] != got[2] and got[0] != got[3]:
        print('seed', seed, 'scores', got, 'small', small, flush=True)
        break
