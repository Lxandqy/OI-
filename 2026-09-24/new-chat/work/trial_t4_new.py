from itertools import product
from fractions import Fraction
import sys


def all_intervals(n):
    return [(l, r) for l in range(n) for r in range(l + 1, n)]


def do(a, lr):
    l, r = lr
    b = list(a)
    v = sum(b[l:r + 1]) / (r - l + 1) if '--exact' in sys.argv else sum(b[l:r + 1]) // (r - l + 1)
    b[l:r + 1] = [v] * (r - l + 1)
    return tuple(b)


def optimum(a, k):
    states = {a: []}
    for _ in range(k):
        nextstates = dict(states)
        for s, plan in states.items():
            for lr in all_intervals(len(a)):
                t = do(s, lr)
                if t not in nextstates or len(plan) + 1 < len(nextstates[t]):
                    nextstates[t] = plan + [lr]
        states = nextstates
    best = max(states)
    return best, states[best]


def disjoint_optimum(a, k):
    states = [(a, [], -1)]
    best, plan = a, []
    for _ in range(k):
        nextstates = []
        for s, used, right in states:
            for lr in all_intervals(len(a)):
                if lr[0] <= right:
                    continue
                t = do(s, lr)
                z = used + [lr]
                nextstates.append((t, z, lr[1]))
                if t > best or (t == best and len(z) < len(plan)):
                    best, plan = t, z
        states = nextstates
    return best, plan


for n in (3, 4, 5):
    for a in product(range(1, 5), repeat=n):
        if '--exact' in sys.argv:
            a = tuple(map(Fraction, a))
        for k in (1, 2, 3):
            x, xp = optimum(a, k)
            y, yp = disjoint_optimum(a, k)
            if x != y:
                print('counterexample', n, a, k, 'full', x, xp, 'disjoint', y, yp)
                raise SystemExit
    print('passed n=', n, flush=True)
print('no counterexample')
