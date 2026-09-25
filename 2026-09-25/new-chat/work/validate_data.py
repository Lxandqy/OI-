from pathlib import Path
import subprocess
import time
from fractions import Fraction
from collections import deque
from random import Random

ROOT = Path(__file__).parent
BUILT = ROOT / 'built'
RNG = Random(993)


def invoke(name, raw, timeout=10):
    start = time.perf_counter()
    try:
        p = subprocess.run([str(ROOT / (name + '.exe'))], input=raw, text=True,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=timeout)
    except subprocess.TimeoutExpired:
        return 'TLE', time.perf_counter() - start
    if p.returncode:
        return 'RE', time.perf_counter() - start
    return p.stdout, time.perf_counter() - start


def check4(raw, out):
    z = list(map(int, raw.split()))
    n, k = z[:2]
    a = list(map(Fraction, z[2:]))
    lines = out.strip().splitlines()
    used = int(lines[0])
    val = [Fraction(x) for x in lines[1].split()]
    assert len(val) == n and len(lines) == used + 2 and 0 <= used <= k
    last = (0, 0)
    for row in lines[2:]:
        l, r = map(int, row.split())
        assert 1 <= l < r <= n and (l, r) > last
        mean = sum(a[l - 1:r]) / (r - l + 1)
        a[l - 1:r] = [mean] * (r - l + 1)
        last = (l, r)
    assert a == val


def check2(raw, out):
    z = list(map(int, raw.split()))
    n = z[0]
    edges = [(z[i], z[i + 1]) for i in range(1, len(z), 2)]
    assert len(edges) == n
    deg = [0] * (n + 1)
    adj = [[] for _ in range(n + 1)]
    for u, v in edges:
        assert 1 <= u <= n and 1 <= v <= n and u != v
        deg[u] += 1
        deg[v] += 1
        adj[u].append(v)
        adj[v].append(u)
    seen = {1}
    q = [1]
    for u in q:
        for v in adj[u]:
            if v not in seen:
                seen.add(v)
                q.append(v)
    assert len(seen) == n
    if out.strip() == '-1':
        return
    vals = list(map(int, out.split()))
    m = vals[0]
    ids = vals[1:]
    assert len(ids) == m and ids == sorted(set(ids))
    assert all(1 <= x <= n for x in ids)
    cut = set(ids)
    fa = list(range(n + 1))
    def find(x):
        while fa[x] != x:
            fa[x] = fa[fa[x]]
            x = fa[x]
        return x
    for i, (u, v) in enumerate(edges, 1):
        if i not in cut:
            fa[find(u)] = find(v)
    size = [0] * (n + 1)
    for i in range(1, n + 1):
        size[find(i)] += 1
    assert all(x in (0, 3) for x in size)


def expected_program(t, i):
    if t == 1:
        if i <= 2: return 'partial_direct_T1'
        if i <= 4: return 'partial_enum_T1'
        if i <= 6: return 'partial_cube_T1'
        if i <= 8: return 'partial_mid_T1'
        return {9:'partial_zero_T1',10:'partial_singleton_T1',11:'partial_cover_T1',
                12:'partial_disjoint_T1',13:'partial_only_fourth_T1',14:'partial_sum_T1'}.get(i,'T1')
    if t == 2:
        if i <= 2: return 'partial_T2'
        if i <= 4: return 'partial_subset_T2'
        if i <= 8 or i == 12: return 'partial_mid_T2'
        return {9:'partial_impossible_T2',10:'partial_pure_T2',11:'partial_triples_T2',
                13:'partial_alternating_T2',14:'partial_impossible_T2'}.get(i,'T2')
    if t == 3:
        if i <= 2: return 'partial_brute_T3'
        if i <= 8: return 'partial_T3'
        if i <= 10: return 'partial_consecutive_T3'
        if i <= 12: return 'partial_neighbor_T3'
        return 'T3'
    if i <= 2: return 'partial_brute_T4'
    if i <= 8: return 'partial_T4'
    return {9:'partial_unchanged_T4',10:'partial_unchanged_T4',11:'partial_unchanged_T4',
            12:'partial_increasing_T4',13:'partial_first_T4',14:'partial_pair_T4'}.get(i,'T4')


for t in range(1, 5):
    for i in range(1, 21):
        folder = BUILT / f'T{t}' / 'data'
        raw = (folder / f'{i}.in').read_text(encoding='utf-8')
        exp = (folder / f'{i}.out').read_text(encoding='utf-8')
        got, sec = invoke(f'T{t}', raw)
        assert got == exp, (t, i, 'std mismatch')
        z = list(map(int, raw.split()))
        n = z[0]
        if t == 1:
            assert 4 <= n <= 100000 and len(z) == n + 5
            assert all(-1000000000 <= x <= 1000000000 for x in z[5:])
            assert all(0 <= x < (1 << 30) for x in z[1:5])
        if t == 2:
            check2(raw, exp)
        if t == 3:
            assert 1 <= n <= 199999 and len(z) == 1 + n + 2 * (n - 1)
            assert len(set(z[1:n + 1])) == n
            assert all(0 <= x < (1 << 30) for x in z[1:n + 1])
        if t == 4:
            assert 1 <= n <= 100000 and 0 <= z[1] <= n and len(z) == n + 2
            assert all(1 <= x < 1000000000 for x in z[2:])
            check4(raw, exp)
        name = expected_program(t, i)
        part, _ = invoke(name, raw)
        assert part == exp, (t, i, name, 'partial mismatch', part[:200], exp[:200])
    print(f'T{t}: 20 inputs valid, std exact, stated partial methods exact', flush=True)

for t, name, i in [(1,'partial_direct_T1',3),(1,'partial_enum_T1',5),
                   (1,'partial_cube_T1',7),(1,'partial_mid_T1',15),
                   (2,'partial_T2',3),(2,'partial_subset_T2',5),(2,'partial_mid_T2',15),
                   (3,'partial_brute_T3',3),(3,'partial_T3',13),
                   (4,'partial_brute_T4',3),(4,'partial_T4',15)]:
    raw = (BUILT / f'T{t}' / 'data' / f'{i}.in').read_text(encoding='utf-8')
    result, elapsed = invoke(name, raw, timeout=2 if t == 1 else 4)
    assert result == 'TLE', (t, i, name, result[:100] if isinstance(result, str) else result)
    print(f'{name} TLE on higher-tier point {i}: {elapsed:.2f}s', flush=True)

for t in range(1, 5):
    src = BUILT / f'T{t}' / 'attachment_source'
    raw = (src / 'attachment1.in').read_text(encoding='utf-8')
    exp = (src / 'attachment1.out').read_text(encoding='utf-8')
    got, _ = invoke(f'T{t}', raw)
    assert got == exp
    if t == 2:
        check2(raw, exp)
    if t == 4:
        check4(raw, exp)
print('attachments valid', flush=True)
