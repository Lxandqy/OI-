from pathlib import Path
from random import Random
import subprocess

p = Path(__file__).parent
rng = Random(92841)


def run(name, raw):
    z = subprocess.run([str(p / (name + '.exe'))], input=raw, text=True,
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=10)
    assert z.returncode == 0, (name, z.stderr)
    return z.stdout


for n in range(4, 12):
    for _ in range(30):
        a = [rng.randint(-20, 20) for _ in range(n)]
        b = [rng.randrange(16) for _ in range(4)]
        raw = f'{n} {" ".join(map(str,b))}\n' + ' '.join(map(str,a)) + '\n'
        assert run('partial_mid_T1',raw) == run('T1',raw), ('T1',raw)
print('T1 middle random exact', flush=True)

for n in range(3, 16):
    for _ in range(50):
        e = [(i,rng.randrange(i)) for i in range(1,n)]
        have = {tuple(sorted(x)) for x in e}
        extra = [(i,j) for i in range(n) for j in range(i + 1,n) if (i,j) not in have]
        e.append(rng.choice(extra))
        rng.shuffle(e)
        raw = str(n) + '\n' + ''.join(f'{u + 1} {v + 1}\n' for u,v in e)
        assert run('partial_mid_T2',raw) == run('T2',raw), ('T2',raw)
print('T2 middle random exact', flush=True)

for n in range(1, 13):
    for _ in range(50):
        a = rng.sample(range(128),n)
        e = [(i,rng.randrange(i)) for i in range(1,n)]
        raw = str(n) + '\n' + ' '.join(map(str,a)) + '\n'
        raw += ''.join(f'{u + 1} {v + 1}\n' for u,v in e)
        assert run('partial_brute_T3',raw) == run('T3',raw), ('T3',raw)
print('T3 brute random exact', flush=True)

for n in range(1, 9):
    for _ in range(50):
        a = [rng.randint(1,20) for _ in range(n)]
        k = rng.randrange(3)
        raw = f'{n} {k}\n' + ' '.join(map(str,a)) + '\n'
        assert run('partial_brute_T4',raw) == run('T4',raw), ('T4',raw,run('partial_brute_T4',raw),run('T4',raw))
print('T4 brute random exact', flush=True)
