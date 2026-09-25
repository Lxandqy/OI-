from pathlib import Path
from random import Random
import subprocess
import time
import json

ROOT = Path(__file__).parent
BUILT = ROOT / 'built'
RNG = Random(20260925)
LOG = []


def run(t, raw):
    start = time.perf_counter()
    p = subprocess.run([str(ROOT / f'T{t}.exe')], input=raw, text=True,
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=25)
    elapsed = time.perf_counter() - start
    assert p.returncode == 0, (t, p.stderr)
    return p.stdout, elapsed


def write(t, i, raw, purpose, attachment=False):
    folder = BUILT / f'T{t}' / ('attachment_source' if attachment else 'data')
    folder.mkdir(parents=True, exist_ok=True)
    out, elapsed = run(t, raw)
    name = f'attachment{i}' if attachment else str(i)
    (folder / (name + '.in')).write_text(raw, encoding='utf-8')
    (folder / (name + '.out')).write_text(out, encoding='utf-8')
    LOG.append(dict(task=t, point=name, n=int(raw.split()[0]), seconds=round(elapsed, 4), purpose=purpose))


def arr1(a, masks):
    return f'{len(a)} {" ".join(map(str, masks))}\n' + ' '.join(map(str, a)) + '\n'


def tree2(n, c, style='plain', shuffle=False):
    edges = [(i, i + 1) for i in range(1, c)] + [(c, 1)]
    if style == 'triples':
        for i in range(1, c + 1):
            first = c + 2 * i - 1
            edges.append((i, first))
            edges.append((first, first + 1))
    elif style == 'twos':
        for i in range(1, c + 1):
            edges.append((i, c + i))
    elif style == 'alternating':
        for i in range(2, c + 1, 2):
            edges.append((i, c + i // 2))
    elif style in ('mixed', 'mixed_rev', 'mixed_rot'):
        nxt = c + 1
        order = {'mixed': (1, 2, 3), 'mixed_rev': (1, 3, 2), 'mixed_rot': (3, 1, 2)}[style]
        for i in range(1, c + 1):
            wanted = order[(i - 1) % 3]
            prev = i
            for _ in range(wanted - 1):
                edges.append((prev, nxt))
                prev = nxt
                nxt += 1
    elif style == 'longtail':
        for x in range(c + 1, n + 1):
            edges.append((1 if x == c + 1 else x - 1, x))
    elif style == 'bad_four':
        for x in range(c + 1, n + 1):
            edges.append((1, x))
    if shuffle:
        RNG.shuffle(edges)
    assert len(edges) == n
    return str(n) + '\n' + ''.join(f'{u} {v}\n' for u, v in edges)


def tree3(a, kind):
    n = len(a)
    if kind == 'chain':
        edges = [(i - 1, i) for i in range(2, n + 1)]
    elif kind == 'star':
        edges = [(1, i) for i in range(2, n + 1)]
    elif kind == 'binary':
        edges = [(i // 2, i) for i in range(2, n + 1)]
    elif kind == 'random':
        edges = [(RNG.randrange(1, i), i) for i in range(2, n + 1)]
    else:
        raise ValueError(kind)
    return str(n) + '\n' + ' '.join(map(str, a)) + '\n' + ''.join(f'{u} {v}\n' for u, v in edges)


def core3(n, kind, seed):
    core = [0] + [1 << i for i in range(29)]
    Random(seed).shuffle(core)
    a = core + [(1 << 29) + 2 * i for i in range(n - len(core))]
    edges = [(i - 1, i) for i in range(2, len(core) + 1)]
    for i in range(len(core) + 1, n + 1):
        if kind == 'chain':
            parent = i - 1
        elif kind == 'binary':
            parent = i // 2
        elif kind == 'star':
            parent = 1
        elif kind == 'random':
            parent = RNG.randrange(1, i)
        else:
            parent = len(core) if i == len(core) + 1 else i - 1
        edges.append((parent, i))
    return str(n) + '\n' + ' '.join(map(str, a)) + '\n' + ''.join(f'{u} {v}\n' for u, v in edges)


def trap3(n, seed):
    local = Random(seed)
    small = [0, 1, 2, 4, 8]
    local.shuffle(small)
    large = [(1 << 29) + v for v in [0, 1] + [1 << i for i in range(1, 28)]]
    first_bulk = len(small) + len(large) + 1
    bulk = local.sample(range(1 << 28, 1 << 29), n - first_bulk + 1)
    a = small + large + bulk
    edges = [(i - 1, i) for i in range(2, len(small) + 1)]
    edges.append((len(small), first_bulk))
    for i in range(first_bulk + 1, n + 1):
        edges.append((local.randrange(first_bulk, i), i))
    for i in range(len(small) + 1, first_bulk):
        edges.append((local.randrange(first_bulk, n + 1), i))
    assert len(edges) == n - 1
    return str(n) + '\n' + ' '.join(map(str, a)) + '\n' + ''.join(f'{u} {v}\n' for u, v in edges)


def arr4(a, k):
    return f'{len(a)} {k}\n' + ' '.join(map(str, a)) + '\n'


# T1: four scale tiers, six guaranteed optimum shapes, six unrestricted cases.
write(1, 1, arr1([-5, 3, -2, 6], [1, 2, 4, 8]), 'smallest four nonempty segments')
write(1, 2, arr1([7, -9, 1, 4, -5, 8, -11, 3, -2, 9], [7, 0, 12, 5]), 'small enumeration; zero mask')
n = 100000
write(1, 3, arr1([((i * 41) % 83) - 40 for i in range(30)], [13, 27, 55, 81]), 'n thirty; interval-summary enumeration')
write(1, 4, arr1([-1000 + i % 19 for i in range(30)], [1, 3, 7, 15]), 'n thirty; negative boundary')
write(1, 5, arr1([((i * 53) % 101) - 50 for i in range(100)], [1, 7, 31, 63]), 'n hundred; cubic DP')
write(1, 6, arr1([(-10000 if i % 3 else 9999) for i in range(100)], [5, 11, 17, 23]), 'n hundred; alternating signs')
write(1, 7, arr1([((i * 48271) % 1999999) - 1000000 for i in range(500)], [123, 456, 789, 1023]), 'n five hundred; quadratic DP')
write(1, 8, arr1([-1000000000 + i % 97 for i in range(500)], [1, 2, 4, 8]), 'n five hundred; all negative')
write(1, 9, arr1([((i * 43) % 201) - 100 for i in range(n)], [0, 0, 0, 0]), 'all masks zero; Kadane')
base = (1 << 24) - 1
single_masks = [1 << 20, 1 << 21, 1 << 22, 1 << 23]
single = [base] * n
for j, pos in enumerate([0, n // 3, 2 * n // 3, n - 1]):
    single[pos] ^= single_masks[j]
write(1, 10, arr1(single, single_masks), 'optimum has four singleton operations')
write(1, 11, arr1([(i * 97) % 99991 for i in range(n)], single_masks), 'optimum operations cover all positions')
disjoint = [-1000000000] * n
disjoint[n // 3:2 * n // 3] = [999999999] * (n // 3)
write(1, 12, arr1(disjoint, [1, 2, 4, 3]), 'optimum answer interval avoids four operations')
fourth = [-1000] * 3 + [100] * (n // 2 - 3) + [(1 << 29) + 100] * (n - n // 2)
write(1, 13, arr1(fourth, [0, 0, 0, 1 << 29]), 'only fourth mask nonzero')
write(1, 14, arr1([i % 1000 + 1 for i in range(n)], [0, 0, 0, 0]), 'all nonnegative and masks zero')
write(1, 15, arr1([((i * 48271) % 1999999999) - 1000000000 for i in range(n)], [123456789, 987654321, 1, 7777777]), 'structured modular values; large masks')
four_zones = [base] * n
for j, left in enumerate([5000, 29000, 53000, 77000]):
    for i in range(left, left + 16000):
        four_zones[i] ^= single_masks[j]
write(1, 16, arr1(four_zones, single_masks), 'four long xor zones separated by positive untouched gaps')
write(1, 17, arr1([900000000 if i in (0, n - 1) else -((i * 11) % 101 + 1) for i in range(n)], [5, 11, 17, 23]), 'both endpoints affect best subarray')
large_zones = [999999999] * n
for j, left in enumerate([1000, 26000, 51000, 76000]):
    for i in range(left, left + 18000):
        large_zones[i] ^= 1 << j
write(1, 18, arr1(large_zones, [1, 2, 4, 8]), 'near-maximum positive values; 64-bit sum and four long zones')
write(1, 19, arr1([((i % 8) - 4) * 11111111 for i in range(n)], [333, 777, 1023, 555]), 'adjacent and separated segments')
write(1, 20, arr1([(-1000 if i % 17 == 0 else (i * 13) % 2001 - 1000) for i in range(n)], [42, 201, 7777, 12345]), 'fourth segment may end at n')
write(1, 1, arr1([4, -8, 12, -3, 6, -4, 9, -5, 11, -7, 2, 3], [1, 5, 2, 6]), 'public larger example', True)

# T2: global subsets, bounded cycle subsets, per-cut scan, special cycle structures.
write(2, 1, tree2(3, 3), 'triangle retained; zero cuts')
write(2, 2, tree2(12, 6, 'mixed', True), 'small mixed cycle residues and lex order')
big = 199998
write(2, 3, tree2(300, 12, 'longtail', True), 'bounded cycle subset; long attachment')
write(2, 4, tree2(300, 15, 'longtail', True), 'cycle subset with fifteen ring edges')
write(2, 5, tree2(1500, 750, 'mixed', True), 'per-cut scan on mixed residual sizes')
write(2, 6, tree2(1800, 1800, shuffle=True), 'per-cut scan on cycle')
write(2, 7, tree2(3000, 1500, 'mixed', True), 'per-cut scan upper range')
write(2, 8, tree2(3000, 3000), 'per-cut scan upper range natural numbering')
write(2, 9, tree2(199999, 199999), 'n not divisible by three')
write(2, 10, tree2(big, big, shuffle=True), 'pure cycle; three offsets')
write(2, 11, tree2(big, big // 3, 'triples', True), 'each ring vertex has a path of two')
write(2, 12, tree2(big, 3, 'longtail', True), 'triangle cycle with long tree tail')
write(2, 13, tree2(big, big * 2 // 3, 'alternating', True), 'alternating cycle weights one and two')
write(2, 14, tree2(big, big // 2, 'twos', True), 'all ring weights two; impossible')
write(2, 15, tree2(big, big // 2, 'mixed', True), 'mixed residual sizes one two three')
write(2, 16, tree2(big, big // 2, 'mixed'), 'mixed pattern natural edge numbering')
write(2, 17, tree2(big, big - 3, 'longtail', True), 'short tree tail attached to very long cycle')
write(2, 18, tree2(big, big - 6, 'longtail', True), 'two forced triples before huge cycle')
write(2, 19, tree2(big, big // 2, 'mixed_rev', True), 'mixed residual pattern one three two')
write(2, 20, tree2(big, big // 2, 'mixed_rot', True), 'mixed residual pattern three one two')
write(2, 1, tree2(24, 12, 'mixed', True), 'public larger example', True)

# T3: subset search, quadratic xor, consecutive-weight and local-edge guarantees.
write(3, 1, tree3([5], 'chain'), 'single node has no partner')
write(3, 2, tree3([0, 1, 2, 4, 8, 16, 32, 1024, 1025, 2048, 2049, 4096, 8192, 8193, 16384], 'chain'), 'small core pair and association closure')
write(3, 3, tree3([1 << i for i in range(30)], 'star'), 'distinct highest bits imply at most thirty values')
write(3, 4, tree3([(i * 1103515245) % (1 << 30) for i in range(3000)], 'chain'), 'quadratic partial upper range')
write(3, 5, tree3([(i * 9137) % (1 << 30) for i in range(3000)], 'star'), 'quadratic star')
write(3, 6, tree3([(i * 65537) % (1 << 30) for i in range(3000)], 'binary'), 'quadratic balanced tree')
write(3, 7, tree3(RNG.sample(range(1 << 30), 3000), 'random'), 'quadratic random original tree')
write(3, 8, tree3(list(range(3000)), 'chain'), 'quadratic consecutive weights')
n = 199998
even_then_odd = list(range(0, n, 2)) + list(range(1, n, 2))
write(3, 9, tree3(even_then_odd, 'chain'), 'consecutive values with no partner edge; answer zero')
write(3, 10, tree3(list(range(n)), 'chain'), 'consecutive values with partner edges')
sparse_pairs = [4 * (i // 2) + i % 2 for i in range(n)]
write(3, 11, tree3(sparse_pairs, 'chain'), 'nearest-xor edges are original chain edges')
pair_edges = [(2 * j + 1, 2 * j + 2) for j in range(n // 2)]
pair_edges += [(2 * j + 1, 2 * (j - 1) + 1) for j in range(1, n // 2)]
RNG.shuffle(pair_edges)
write(3, 12, str(n) + '\n' + ' '.join(map(str, sparse_pairs)) + '\n' + ''.join(f'{u} {v}\n' for u, v in pair_edges), 'nearest-xor edges included in random-order tree')
n = 199999
write(3, 13, core3(n, 'random', 0), 'connected sparse xor core with random outside tree')
write(3, 14, tree3([(i * 9137) % (1 << 30) for i in range(n)], 'star'), 'large star')
write(3, 15, core3(n, 'chain', 7), 'permuted xor core and long chain')
write(3, 16, core3(n, 'binary', 19), 'permuted xor core and binary outside tree')
write(3, 17, core3(n, 'star', 29), 'permuted xor core and large star outside')
write(3, 18, core3(n, 'longtail', 53), 'connected thirty-node nearest-xor core')
write(3, 19, tree3(RNG.sample(range(1 << 30), n), 'binary'), 'random values on binary tree')
write(3, 20, trap3(n, 0), 'random bulk weights and tree; disconnected large xor component trap')
write(3, 1, tree3([0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384], 'chain'), 'public larger example', True)

# T4: operation search, quadratic scans, six easy but distinct structures.
write(4, 1, arr4([1, 2, 4], 2), 'exact average; one operation despite k two')
write(4, 2, arr4([3, 1, 5, 2, 1, 1, 1, 1, 1, 1], 1), 'small equal-prefix tie and canonical interval')
n = 100000
write(4, 3, arr4([123456789] * 2000, 1), 'all equal medium point; brute still enumerates intervals')
write(4, 4, arr4([999999999 - i for i in range(2000)], 1), 'quadratic upper range; strictly decreasing')
write(4, 5, arr4([500000000 - 10 * j + d for j in range(1000) for d in (-2, 2)], 2), 'two thousand positions in descending pair blocks')
write(4, 6, arr4([i + 1 for i in range(2000)], 1), 'strictly increasing medium range')
write(4, 7, arr4([((i * 53) % 997) + 1 for i in range(2000)], 2), 'mixed values with two operations')
write(4, 8, arr4([1, 100000, 999999999] + [333000000 - i for i in range(1997)], 1), 'long prefix-average trap')
write(4, 9, arr4([((i * 48271) % 999999997) + 1 for i in range(n)], 0), 'zero budget; original sequence')
write(4, 10, arr4([123456789] * n, n), 'all equal; zero operations')
write(4, 11, arr4([999999999 - i for i in range(n)], n), 'strictly decreasing; zero operations')
write(4, 12, arr4([i + 1 for i in range(n)], n), 'strictly increasing; one full interval')
trap = [1, 100000, 999999999]
for j in range(1, 49999):
    base = 333000000 - 5 * j
    trap.extend([base - 10, base + 10])
write(4, 13, arr4(trap, 1), 'one operation; first element is strict minimum')
pair = [v for j in range(50000) for v in (1000000000 - 4 * j - 2, 1000000000 - 4 * j - 1)]
write(4, 14, arr4(pair, 30000), 'strictly descending pair means')
thirds = []
for j in range(33333):
    base = 900000000 - 5 * j
    thirds.extend([base - 2, base - 1, base + 4])
write(4, 15, arr4(thirds, 33333), 'many rational thirds; quadratic scans must fail')
write(4, 16, arr4([800000000 - 6 * j + d for j in range(25000) for d in (-3, -1, 2, 4)], 25000), 'descending four-element blocks')
write(4, 17, arr4([700000000 - 7 * j + d for j in range(33333) for d in (-1, 2, -3)], 20000), 'paired blocks interleaved with singletons')
write(4, 18, arr4([650000000 - 10 * j + d for j in range(16666) for d in (-5, -3, -1, 2, 3, 6)], 16000), 'six-element rational blocks')
write(4, 19, arr4(trap, 2), 'first distant prefix choice then second operation')
write(4, 20, arr4([v for j in range(20000) for v in (500000000 - 20 * j - 2, 500000000 - 20 * j + 1, 500000000 - 20 * j - 9, 500000000 - 20 * j - 7, 500000000 - 20 * j - 5)], 30000), 'alternating pair and triple blocks')
write(4, 1, arr4([3, 1, 5, 8, 1, 9, 2, 6, 4, 7, 1, 10], 3), 'public larger example', True)

(ROOT / 'data_log.json').write_text(json.dumps(LOG, ensure_ascii=False, indent=2), encoding='utf-8')
for t in range(1, 5):
    x = [row for row in LOG if row['task'] == t and row['point'].isdigit()]
    print('T', t, 'points', len(x), 'max_seconds', max(row['seconds'] for row in x), flush=True)
