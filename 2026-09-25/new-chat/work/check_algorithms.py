from collections import deque
from fractions import Fraction
from itertools import combinations, product
from random import Random


def t1_fast(a, masks):
    n = len(a)
    phase = [0, masks[0], 0, masks[1], 0, masks[2], 0, masks[3], 0]
    neg = -10**30
    dp = [[neg] * 3 for _ in range(9)]
    dp[0][0] = 0
    for x in a:
        nd = [[neg] * 3 for _ in range(9)]
        for p in range(9):
            for q in range(3):
                for np in (p, p + 1, p + 2):
                    if np >= 9 or (np == p + 2 and (p % 2 != 1 or p >= 7)):
                        continue
                    if np == p and p % 2 and dp[p][q] == neg:
                        continue
                    # Entering odd phase consumes this element. Moving odd->even
                    # consumes a non-XOR element. Moving odd->next odd skips a gap.
                    if np == p + 1 and p % 2 == 0 and np > 7:
                        continue
                    v = x ^ phase[np]
                    for nq in (q, q + 1):
                        if nq >= 3 or (q == 0 and nq == 2):
                            continue
                        if q == 0 and nq == 0:
                            z = 0
                        elif q == 0 and nq == 1:
                            z = v
                        elif q == 1 and nq == 1:
                            z = dp[p][q] + v
                        elif q == 1 and nq == 2:
                            z = dp[p][q]
                        else:
                            z = dp[p][q]
                        if dp[p][q] != neg:
                            nd[np][nq] = max(nd[np][nq], z)
        dp = nd
    return max(dp[p][q] for p in (7, 8) for q in (1, 2))


def t1_brute(a, masks):
    n = len(a)
    best = -10**30
    def rec(start, j, b):
        nonlocal best
        if j == 4:
            best = max(best, max(sum(b[l:r]) for l in range(n) for r in range(l + 1, n + 1)))
            return
        for l in range(start, n):
            for r in range(l + 1, n + 1):
                c = b[:]
                for i in range(l, r):
                    c[i] ^= masks[j]
                rec(r, j + 1, c)
    rec(0, 0, list(a))
    return best


def t2_brute(n, edges):
    m = len(edges)
    if n % 3:
        return None
    best = None
    for mask in range(1 << m):
        par = list(range(n))
        def find(x):
            while x != par[x]:
                x = par[x]
            return x
        for i, (u, v) in enumerate(edges):
            if not (mask >> i & 1):
                par[find(u)] = find(v)
        sizes = [0] * n
        for i in range(n):
            sizes[find(i)] += 1
        if any(s and s != 3 for s in sizes):
            continue
        cut = [i + 1 for i in range(m) if mask >> i & 1]
        if best is None or cut < best:
            best = cut
    return best


def t2_fast(n, edges):
    if n % 3:
        return None
    adj = [[] for _ in range(n)]
    for i, (u, v) in enumerate(edges, 1):
        adj[u].append((v, i))
        adj[v].append((u, i))
    deg = [len(x) for x in adj]
    q = deque(i for i in range(n) if deg[i] == 1)
    order = []
    oncyc = [True] * n
    peel_parent = [(-1, -1)] * n
    while q:
        u = q.popleft()
        oncyc[u] = False
        order.append(u)
        for v, eid in adj[u]:
            if oncyc[v]:
                peel_parent[u] = (v, eid)
                deg[v] -= 1
                if deg[v] == 1:
                    q.append(v)
    weight = [1] * n
    forced = []
    for u in order:
        if peel_parent[u][0] == -1 or weight[u] > 3:
            return None
        v, eid = peel_parent[u]
        if weight[u] == 3:
            forced.append(eid)
        else:
            weight[v] += weight[u]
            if weight[v] > 3:
                return None
    cyc = [i for i in range(n) if oncyc[i]]
    start = cyc[0]
    nodes = [start]
    ce = []
    prev = -1
    u = start
    while True:
        opts = [(v, eid) for v, eid in adj[u] if oncyc[v] and v != prev]
        if not opts:
            return None
        v, eid = opts[0]
        ce.append(eid)
        if v == start:
            break
        nodes.append(v)
        prev, u = u, v
    best = None
    if len(nodes) == 3 and sum(weight[v] for v in nodes) == 3:
        best = sorted(forced)
    pref = 0
    residues = []
    for v in nodes:
        pref += weight[v]
        residues.append(pref % 3)
    for r in range(3):
        chosen = [i for i, x in enumerate(residues) if x == r]
        if not chosen:
            continue
        # Positive weights guarantee each group has sum three if adjacent
        # boundary prefix sums differ by exactly three.
        z = [0] * len(nodes)
        for i in chosen:
            z[i] = 1
        first = chosen[0]
        total = 0
        okay = True
        i = (first + 1) % len(nodes)
        while True:
            total += weight[nodes[i]]
            if z[i]:
                if total != 3:
                    okay = False
                total = 0
            i = (i + 1) % len(nodes)
            if i == (first + 1) % len(nodes):
                break
        if okay:
            cut = sorted(forced + [ce[i] for i in chosen])
            if best is None or cut < best:
                best = cut
    return best


def partner(a):
    f = []
    for i, x in enumerate(a):
        f.append(min((x ^ y, j) for j, y in enumerate(a) if i != j)[1])
    return f


def t3_brute(n, edges, f):
    best = 0
    for mask in range(1, 1 << n):
        ids = [i for i in range(n) if mask >> i & 1]
        if any(not mask >> f[i] & 1 for i in ids):
            continue
        a = [[] for _ in range(n)]
        b = [[] for _ in range(n)]
        for u, v in edges:
            if mask >> u & 1 and mask >> v & 1:
                a[u].append(v)
                a[v].append(u)
        assoc = set()
        for i in ids:
            assoc.add(tuple(sorted((i, f[i]))))
        if len(assoc) != len(ids) - 1:
            continue
        for u, v in assoc:
            b[u].append(v)
            b[v].append(u)
        def reachable(g):
            seen = {ids[0]}
            q = [ids[0]]
            for u in q:
                for v in g[u]:
                    if v not in seen:
                        seen.add(v)
                        q.append(v)
            return len(seen) == len(ids)
        if reachable(a) and reachable(b):
            best = max(best, len(ids))
    return best


def t3_fast(n, edges, f):
    if n == 1:
        return 1
    par = list(range(n))
    def find(x):
        while par[x] != x:
            par[x] = par[par[x]]
            x = par[x]
        return x
    for i in range(n):
        par[find(i)] = find(f[i])
    comp = [find(i) for i in range(n)]
    original = [[] for _ in range(n)]
    backward = [[] for _ in range(n)]
    for u, v in edges:
        original[u].append(v)
        original[v].append(u)
    for i in range(n):
        backward[f[i]].append(i)
    root = [-1] * n
    for i in range(n):
        if i < f[i] and f[f[i]] == i:
            root[comp[i]] = i
    vis = [False] * n
    best = 0
    for c in set(comp):
        p = root[c]
        q = f[p]
        branch = [p]
        vis[p] = True
        parent = [-1] * n
        for u in branch:
            for v in original[u]:
                if not vis[v] and comp[v] == c:
                    vis[v] = True
                    parent[v] = u
                    branch.append(v)
        if not vis[q]:
            continue
        inside = set(branch)
        bad = set(u for u in branch if f[u] not in inside)
        queue = list(bad)
        for u in queue:
            for v in original[u]:
                if parent[v] == u and v not in bad:
                    bad.add(v)
                    queue.append(v)
            for v in backward[u]:
                if v in inside and v not in bad:
                    bad.add(v)
                    queue.append(v)
        best = max(best, len(branch) - len(bad))
    return best


def t4_brute(a, k):
    n = len(a)
    states = {tuple(map(Fraction, a)): []}
    for _ in range(k):
        nxt = dict(states)
        for x, plan in states.items():
            for l in range(n):
                for r in range(l + 1, n):
                    y = list(x)
                    mean = sum(y[l:r + 1]) / (r - l + 1)
                    y[l:r + 1] = [mean] * (r - l + 1)
                    y = tuple(y)
                    if y not in nxt or (len(plan) + 1, plan + [(l, r)]) < (len(nxt[y]), nxt[y]):
                        nxt[y] = plan + [(l, r)]
        states = nxt
    x = max(states)
    return x, states[x]


def t4_fast(a, k):
    n = len(a)
    result = list(map(Fraction, a))
    ops = []
    start = 0
    while start < n and len(ops) < k:
        total = 0
        best = Fraction(-1)
        end = start
        for j in range(start, n):
            total += a[j]
            mean = Fraction(total, j - start + 1)
            if mean >= best:
                best, end = mean, j
        if end > start and any(Fraction(a[j]) != best for j in range(start, end + 1)):
            last_different = max(j for j in range(start, end + 1) if Fraction(a[j]) != best)
            ops.append((start, last_different))
            for j in range(start, end + 1):
                result[j] = best
        start = end + 1
    return tuple(result), ops


rng = Random(42)
for n in range(4, 9):
    for z in range(100):
        a = [rng.randrange(-8, 9) for _ in range(n)]
        masks = [rng.randrange(0, 8) for _ in range(4)]
        x = t1_fast(a, masks)
        y = t1_brute(a, masks)
        assert x == y, ('T1', a, masks, x, y)
    print('T1', n, 'ok', flush=True)
for n in range(3, 11):
    for z in range(200):
        e = [(i, rng.randrange(i)) for i in range(1, n)]
        u, v = rng.sample(range(n), 2)
        if (min(u, v), max(u, v)) in {tuple(sorted(x)) for x in e}:
            continue
        e.append((u, v))
        rng.shuffle(e)
        x = t2_fast(n, e)
        y = t2_brute(n, e)
        assert x == y, ('T2', n, e, x, y)
    print('T2', n, 'ok', flush=True)
for n in range(2, 11):
    for z in range(400):
        e = [(i, rng.randrange(i)) for i in range(1, n)]
        a = rng.sample(range(0, 64), n)
        f = partner(a)
        x = t3_fast(n, e, f)
        y = t3_brute(n, e, f)
        assert x == y, ('T3', n, e, a, f, x, y)
    print('T3', n, 'ok', flush=True)
for n in range(2, 7):
    for z in range(200):
        a = [rng.randrange(1, 8) for _ in range(n)]
        for k in range(0, min(n, 3) + 1):
            x = t4_fast(a, k)
            y = t4_brute(a, k)
            assert x[0] == y[0] and len(x[1]) == len(y[1]), ('T4', n, a, k, x, y)
            if x[1] != y[1]:
                print('T4 LEX PLAN DIFF', n, a, k, x, y, flush=True)
                raise SystemExit
    print('T4', n, 'ok', flush=True)
