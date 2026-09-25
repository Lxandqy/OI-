from collections import deque
from pathlib import Path
import subprocess
import sys
import zipfile

ROOT = Path(__file__).parent
BASE = ROOT / 'built/suite5_full/T4'
SCRATCH = ROOT / 'suite5_t4_general_io'
SCRATCH.mkdir(exist_ok=True)
CASES = [
    (1000,1000,210,'horizontal'),
    (850,920,250,'vertical'),
    (1000,1000,220,'horizontal'),
    (850,1000,225,'vertical'),
    (1000,920,230,'horizontal'),
    (850,1000,235,'vertical'),
    (1000,1000,240,'horizontal'),
    (850,920,245,'vertical'),
    (1000,1000,250,'horizontal'),
    (850,1000,255,'vertical'),
]

def make_case(n,m,q,direction):
    points = []
    if direction == 'horizontal':
        ys = list(range(0,m,2*q-1))
        if ys[-1] != m-1:
            ys.append(m-1)
        points = [(n//2,y) for y in ys]
    else:
        xs = list(range(0,n,2*q-1))
        if xs[-1] != n-1:
            xs.append(n-1)
        points = [(x,m//2) for x in xs]
    used = set(points)
    start, goal = (1,1),(n-2,m-2)
    if direction == 'horizontal':
        x0,y0 = n//2-25,m//2+q//2
    else:
        x0,y0 = n//2+q//2,m//2-25
    for x in range(x0,x0+50):
        for y in range(y0,y0+50):
            if len(points) == 1000:
                break
            if (x,y) not in used and (x,y) not in (start,goal):
                points.append((x,y))
                used.add((x,y))
        if len(points) == 1000:
            break
    assert len(points) == len(used) == 1000
    assert start not in used and goal not in used
    body = '\n'.join([f'{n} {m} 1000',f'{start[0]} {start[1]}',f'{goal[0]} {goal[1]}']
                     + [f'{x} {y}' for x,y in points]) + '\n'
    return body,points,start,goal

def brute_at(n,m,points,start,goal,r):
    grid = bytearray(n*m)
    for cx,cy in points:
        x1 = max(0,cx-r+1)
        x2 = min(n-1,cx+r-1)
        y1 = max(0,cy-r+1)
        y2 = min(m-1,cy+r-1)
        mark = b'\x01' * (y2-y1+1)
        for x in range(x1,x2+1):
            base = x*m
            grid[base+y1:base+y2+1] = mark
    area = sum(grid)
    si = start[0]*m+start[1]
    ei = goal[0]*m+goal[1]
    if grid[si] or grid[ei]:
        return False,area
    queue = deque([si])
    grid[si] = 2
    while queue:
        v = queue.popleft()
        if v == ei:
            return True,area
        x,y = divmod(v,m)
        for u,valid in ((v-m,x>0),(v+m,x+1<n),(v-1,y>0),(v+1,y+1<m)):
            if valid and grid[u] == 0:
                grid[u] = 2
                queue.append(u)
    return False,area

def run(exe,body):
    (SCRATCH/'green.in').write_text(body,encoding='utf-8',newline='\n')
    p = subprocess.run([str(exe)],cwd=SCRATCH,capture_output=True,timeout=15)
    assert p.returncode == 0,(exe,p.stderr[:200])
    return (SCRATCH/'green.out').read_text(encoding='utf-8').strip()

prepared = {}
for point,(n,m,q,direction) in enumerate(CASES,11):
    body,centers,start,goal = make_case(n,m,q,direction)
    feasible,area = brute_at(n,m,centers,start,goal,q-1)
    blocked,_ = brute_at(n,m,centers,start,goal,q)
    assert feasible and not blocked,(point,q,feasible,blocked)
    std = run(ROOT/'suite5_t4_candidate.exe',body)
    other = run(ROOT/'green_bench'/'paint_binary.exe',body)
    assert std == other == str(area),(point,q,area,std,other)
    prepared[point] = (body,std)
    print(f'{point}: {direction} max_radius={q-1} area={area} independent=OK',flush=True)

if '--write' in sys.argv:
    for point,(body,answer) in prepared.items():
        (BASE/'data'/f'{point}.in').write_text(body,encoding='utf-8',newline='\n')
        (BASE/'data'/f'{point}.out').write_text(answer+'\n',encoding='utf-8',newline='\n')
    with zipfile.ZipFile(BASE/'data.zip','w',compression=zipfile.ZIP_DEFLATED) as z:
        for point in range(1,21):
            for suffix in ('in','out'):
                path = BASE/'data'/f'{point}.{suffix}'
                z.write(path,path.name)
    print('T4 points 11-20 installed; data.zip rebuilt',flush=True)
