from pathlib import Path
from random import Random
import subprocess
import time

root = Path(__file__).parent
rng = Random(2451)


def raw(a, b):
    return f'{len(a)} {" ".join(map(str, b))}\n' + ' '.join(map(str, a)) + '\n'


def run(name, data, timeout=6):
    start = time.perf_counter()
    result = subprocess.run([str(root / (name + '.exe'))], input=data, text=True,
                            capture_output=True, timeout=timeout)
    assert result.returncode == 0, (name, result.stderr)
    return result.stdout.strip(), time.perf_counter() - start


for n in range(4, 10):
    for _ in range(30):
        a = [rng.randrange(-30, 31) for _ in range(n)]
        b = [rng.randrange(32) for _ in range(4)]
        data = raw(a, b)
        expected, _ = run('T1', data)
        for name in ('partial_direct_T1', 'partial_enum_T1', 'partial_cube_T1', 'partial_mid_T1'):
            got, _ = run(name, data)
            assert got == expected, (name, data, got, expected)
print('T1 four general algorithms random exact', flush=True)

for _ in range(100):
    n = rng.randrange(4, 40)
    a = [rng.randrange(-100, 101) for _ in range(n)]
    b = [0, 0, 0, rng.randrange(1024)]
    data = raw(a, b)
    assert run('partial_only_fourth_T1', data)[0] == run('T1', data)[0]
    b = [0, 0, 0, 0]
    data = raw(a, b)
    assert run('partial_zero_T1', data)[0] == run('T1', data)[0]
print('T1 mask specials random exact', flush=True)

for n in (30, 300, 3000):
    base = (1 << 24) - 1
    b = [1 << 20, 1 << 21, 1 << 22, 1 << 23]
    a = [base] * n
    for j, pos in enumerate((1, n // 3, 2 * n // 3, n - 2)):
        a[pos] ^= b[j]
    data = raw(a, b)
    assert run('partial_singleton_T1', data)[0] == run('T1', data)[0]
    b = [1 << 20, 1 << 21, 1 << 22, 1 << 23]
    a = [(i * 97) % 99991 for i in range(n)]
    data = raw(a, b)
    assert run('partial_cover_T1', data)[0] == run('T1', data)[0]
    b = [1, 2, 4, 3]
    a = [-1000000000] * n
    a[n // 3:2 * n // 3] = [999999999] * (n // 3)
    data = raw(a, b)
    assert run('partial_disjoint_T1', data)[0] == run('T1', data)[0]
print('T1 witness-guarantee specials exact', flush=True)

n = 30
data = raw([rng.randrange(-100, 101) for _ in range(n)], [13, 27, 55, 81])
expected, _ = run('T1', data)
got, seconds = run('partial_enum_T1', data, timeout=10)
assert got == expected
print('T1 n=30 optimized interval enumeration', round(seconds, 3), 'seconds', flush=True)
