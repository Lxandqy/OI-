import contextlib
import io
import random
import subprocess
import sys
from pathlib import Path

with contextlib.redirect_stdout(io.StringIO()):
    import check_algorithms as check

BASE = Path(__file__).parent
RNG = random.Random(9351)


def run(t, data):
    proc = subprocess.run([str(BASE / f'T{t}.exe')], input=data, text=True,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5)
    assert proc.returncode == 0, (t, data, proc.stderr)
    return proc.stdout


for n in range(4, 9):
    for _ in range(100):
        a = [RNG.randint(-15, 15) for _ in range(n)]
        m = [RNG.randrange(8) for _ in range(4)]
        data = f'{n} {" ".join(map(str, m))}\n' + ' '.join(map(str, a)) + '\n'
        got = int(run(1, data))
        exp = check.t1_brute(a, m)
        assert got == exp, ('T1', data, got, exp)
print('C++ T1 ok', flush=True)

for n in range(3, 13):
    for _ in range(100):
        e = [(i, RNG.randrange(i)) for i in range(1, n)]
        all_e = {tuple(sorted(x)) for x in e}
        avail = [(i, j) for i in range(n) for j in range(i + 1, n) if (i, j) not in all_e]
        u, v = RNG.choice(avail)
        e.append((u, v))
        RNG.shuffle(e)
        data = str(n) + '\n' + ''.join(f'{u + 1} {v + 1}\n' for u, v in e)
        got = run(2, data).strip().split()
        exp = check.t2_brute(n, e)
        if exp is None:
            assert got == ['-1'], ('T2', data, got, exp)
        else:
            assert int(got[0]) == len(exp) and list(map(int, got[1:])) == exp, ('T2', data, got, exp)
print('C++ T2 ok', flush=True)

for n in range(2, 12):
    for _ in range(150):
        e = [(i, RNG.randrange(i)) for i in range(1, n)]
        a = RNG.sample(range(128), n)
        f = check.partner(a)
        data = str(n) + '\n' + ' '.join(map(str, a)) + '\n'
        data += ''.join(f'{u + 1} {v + 1}\n' for u, v in e)
        got = int(run(3, data))
        exp = check.t3_brute(n, e, f)
        assert got == exp, ('T3', data, got, exp)
print('C++ T3 ok', flush=True)

for n in range(1, 7):
    for _ in range(20):
        a = [RNG.randint(1, 12) for _ in range(n)]
        k = RNG.randrange(n + 1)
        data = f'{n} {k}\n' + ' '.join(map(str, a)) + '\n'
        out = run(4, data).splitlines()
        use = int(out[0])
        from fractions import Fraction
        val = tuple(Fraction(z) for z in out[1].split())
        ops = []
        now = list(map(Fraction, a))
        for row in out[2:]:
            l, r = map(int, row.split())
            ops.append((l - 1, r - 1))
            avg = sum(now[l - 1:r]) / (r - l + 1)
            now[l - 1:r] = [avg] * (r - l + 1)
        assert use == len(ops) <= k and tuple(now) == val, ('T4 certificate', data, out)
        exp, plan = check.t4_brute(a, k)
        assert val == exp and use == len(plan), ('T4 optimum', data, out, exp, plan)
print('C++ T4 ok', flush=True)
