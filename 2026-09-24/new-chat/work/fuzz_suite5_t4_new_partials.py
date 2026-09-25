from collections import deque
from pathlib import Path
import random
import subprocess

ROOT = Path(__file__).parent
SCRATCH = ROOT/'suite5_t4_fuzz_io'
SCRATCH.mkdir(exist_ok=True)
BIN = ROOT/'verified_bin'
RNG = random.Random(20260924)

def brute(n,m,centers,start,goal):
    answer = 0
    for r in range(1,max(n,m)+1):
        blocked = [[False]*m for _ in range(n)]
        for cx,cy in centers:
            for x in range(max(0,cx-r+1),min(n-1,cx+r-1)+1):
                for y in range(max(0,cy-r+1),min(m-1,cy+r-1)+1):
                    blocked[x][y] = True
        if blocked[start[0]][start[1]] or blocked[goal[0]][goal[1]]:
            break
        queue = deque([start])
        seen = {start}
        while queue:
            x,y = queue.popleft()
            for nx,ny in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
                if 0<=nx<n and 0<=ny<m and not blocked[nx][ny] and (nx,ny) not in seen:
                    seen.add((nx,ny))
                    queue.append((nx,ny))
        if goal not in seen:
            break
        answer = sum(sum(row) for row in blocked)
    return answer

def run(exe,body):
    (SCRATCH/'green.in').write_text(body,encoding='utf-8',newline='\n')
    p = subprocess.run([str(exe)],cwd=SCRATCH,capture_output=True,timeout=5)
    assert p.returncode == 0,p.stderr
    return int((SCRATCH/'green.out').read_text(encoding='utf-8').strip())

for kind in ('k10','adj'):
    for case in range(100):
        n = RNG.randrange(2,9)
        m = RNG.randrange(2,9)
        cells = [(x,y) for x in range(n) for y in range(m)]
        RNG.shuffle(cells)
        if kind == 'adj':
            start = cells[0]
            choices = [(x,y) for x,y in cells[1:] if abs(x-start[0])+abs(y-start[1])==1]
            goal = RNG.choice(choices)
            other = [cell for cell in cells if cell not in (start,goal)]
        else:
            start,goal = cells[:2]
            other = cells[2:]
        k = RNG.randrange(1,min(10,len(other))+1)
        centers = other[:k]
        body = '\n'.join([f'{n} {m} {k}',f'{start[0]} {start[1]}',f'{goal[0]} {goal[1]}']
                         + [f'{x} {y}' for x,y in centers])+'\n'
        expected = brute(n,m,centers,start,goal)
        exe = BIN/('s5t4b1.exe' if kind=='k10' else 's5t4b2.exe')
        got = run(exe,body)
        assert got == expected,(kind,case,expected,got,body)
    print(kind, '100 independent random cases PASS',flush=True)
