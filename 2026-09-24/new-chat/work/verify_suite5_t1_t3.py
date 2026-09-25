from datetime import date,timedelta
from pathlib import Path
import random
import subprocess
import time

ROOT = Path(__file__).parent
EXE = {1:ROOT/'suite5_t1_full.exe',3:ROOT/'suite5_t3_full.exe'}

def run(task,text):
    start = time.perf_counter()
    p = subprocess.run([str(EXE[task])],input=text.encode(),capture_output=True,check=True,timeout=5)
    return p.stdout.decode().split(),time.perf_counter()-start

for task in (1,3):
    for label,base in [('source',ROOT/f'source5/T{task}/judge/data'),
                       ('built',ROOT/f'built/suite5_full/T{task}/data')]:
        max_time = 0
        files = sorted(base.glob('*.in'),key=lambda p:int(p.stem))
        for path in files:
            actual,elapsed = run(task,path.read_text(encoding='utf-8'))
            expected = path.with_suffix('.out').read_text(encoding='utf-8').split()
            assert actual == expected,(task,label,path.name,actual,expected)
            max_time = max(max_time,elapsed)
        print(f'T{task} {label}: {len(files)} formal points passed; max={max_time:.3f}s',flush=True)

rng = random.Random(51753)
for z in range(40):
    y = rng.randint(2000,3000)
    m = rng.randint(1,12)
    while True:
        try:
            d = rng.randint(1,31)
            cur = date(y,m,d)
            break
        except ValueError:
            pass
    text = f'{y} {m} {d}\n'
    while True:
        cur += timedelta(days=1)
        s = str(cur.year)+str(cur.month)+str(cur.day)
        if s == s[::-1]:
            break
    actual,_ = run(1,text)
    assert actual == [str(cur.year),str(cur.month),str(cur.day)],(z,text,actual,cur)
print('T1: 40 random dates matched independent calendar search',flush=True)

for z in range(100):
    lo = rng.randint(1,100)
    hi = rng.randint(lo+1,150)
    length = [1]*(hi+1)
    count = [1]*(hi+1)
    for x in range(lo,hi+1):
        for y in range(2*x,hi+1,x):
            candidate = length[x]+1
            if candidate > length[y]:
                length[y],count[y] = candidate,count[x]
            elif candidate == length[y]:
                count[y] += count[x]
    best = max(length[lo:])
    ways = sum(count[x] for x in range(lo,hi+1) if length[x] == best)
    actual,_ = run(3,f'1\n{lo} {hi}\n')
    assert actual == [str(best),str(ways)],(z,lo,hi,actual,best,ways)
print('T3: 100 random intervals matched independent divisibility DP',flush=True)
