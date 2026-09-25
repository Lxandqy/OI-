from pathlib import Path
from random import Random
import subprocess

root = Path(__file__).parent
n = 1000
core = [0] + [1 << i for i in range(29)]

def run(name, raw):
    p = subprocess.run([str(root / (name + '.exe'))], input=raw, text=True, capture_output=True, timeout=5)
    assert p.returncode == 0
    return int(p.stdout)

for seed in range(100):
    rng = Random(seed)
    order = core[:]
    rng.shuffle(order)
    values = order + [(1 << 29) + 2 * i for i in range(n - len(core))]
    raw = f'{n}\n' + ' '.join(map(str, values)) + '\n'
    raw += ''.join(f'{i - 1} {i}\n' for i in range(2, n + 1))
    got = (run('T3', raw), run('partial_consecutive_T3', raw), run('partial_neighbor_T3', raw))
    if got[0] > 2 and got[0] != got[1] and got[0] != got[2]:
        print('seed', seed, 'scores', got, 'core order', order, flush=True)
        break
