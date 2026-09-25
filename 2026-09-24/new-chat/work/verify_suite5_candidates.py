from collections import deque
from pathlib import Path
import random
import subprocess
import time

ROOT = Path(__file__).parent
SCRATCH = ROOT / 'suite5_candidate_io'
SCRATCH.mkdir(exist_ok=True)
EXE = {2:ROOT/'suite5_t2_candidate.exe',4:ROOT/'suite5_t4_candidate.exe'}

def run(task, body, limit=5):
    start = time.perf_counter()
    if task == 4:
        (SCRATCH/'green.in').write_text(body,encoding='utf-8')
        subprocess.run([str(EXE[task])],cwd=SCRATCH,capture_output=True,check=True,timeout=limit)
        output = (SCRATCH/'green.out').read_text(encoding='utf-8').strip()
    else:
        result = subprocess.run([str(EXE[task])],input=body.encode(),capture_output=True,check=True,timeout=limit)
        output = result.stdout.decode().strip()
    return output,time.perf_counter()-start

for task in (2,4):
    for label,base in [('source',ROOT/f'source5/T{task}/judge/data'),
                       ('built',ROOT/f'built/suite5_full/T{task}/data')]:
        max_time = 0
        for path in sorted(base.glob('*.in'),key=lambda p:int(p.stem)):
            actual,elapsed = run(task,path.read_text(encoding='utf-8'),5)
            expected = path.with_suffix('.out').read_text(encoding='utf-8').strip()
            assert actual.split() == expected.split(),(task,label,path.name,actual,expected)
            max_time = max(max_time,elapsed)
        print(f'T{task} {label}: {len(list(base.glob("*.in")))} formal points passed; max={max_time:.3f}s',flush=True)

rng = random.Random(95024)
for z in range(100):
    n = rng.randint(1,12)
    m = rng.randint(1,30)
    k = rng.randint(1,15)
    items = [(rng.randint(1,35),rng.randint(1,40)) for _ in range(n)]
    body = '\n'.join([f'{n} {m} {k}']+[f'{w} {v}' for w,v in items])+'\n'
    answer = 0
    for mask in range(1<<n):
        weight = score = 0
        for i,(w,v) in enumerate(items):
            if mask>>i&1:
                weight += w
                score += v-k
        if weight <= m:
            answer = max(answer,score)
    actual,_ = run(2,body)
    assert actual == str(answer),(z,body,answer,actual)
print('T2: 100 random small cases matched exhaustive subsets',flush=True)

def brute_green(n,m,start,goal,centers):
    result = 0
    for r in range(1,max(n,m)+1):
        blocked = [[False]*m for _ in range(n)]
        for cx,cy in centers:
            for x in range(max(0,cx-r+1),min(n-1,cx+r-1)+1):
                for y in range(max(0,cy-r+1),min(m-1,cy+r-1)+1):
                    blocked[x][y] = True
        if blocked[start[0]][start[1]] or blocked[goal[0]][goal[1]]:
            break
        q = deque([start]); seen = {start}
        while q:
            x,y = q.popleft()
            for nx,ny in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
                if 0 <= nx < n and 0 <= ny < m and not blocked[nx][ny] and (nx,ny) not in seen:
                    seen.add((nx,ny)); q.append((nx,ny))
        if goal not in seen:
            break
        result = sum(sum(row) for row in blocked)
    return result

for z in range(100):
    n = rng.randint(2,7)
    m = rng.randint(2,7)
    pts = rng.sample([(x,y) for x in range(n) for y in range(m)],rng.randint(3,min(n*m,11)))
    start,goal = pts[:2]
    centers = pts[2:]
    body = '\n'.join([f'{n} {m} {len(centers)}',f'{start[0]} {start[1]}',
                      f'{goal[0]} {goal[1]}']+[f'{x} {y}' for x,y in centers])+'\n'
    answer = brute_green(n,m,start,goal,centers)
    actual,_ = run(4,body)
    assert actual == str(answer),(z,body,answer,actual)
print('T4: 100 random small cases matched independent painting+BFS',flush=True)
