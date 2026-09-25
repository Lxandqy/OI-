from collections import deque
from pathlib import Path
import subprocess
import zipfile

ROOT = Path(__file__).parent
BASE = ROOT/'built/suite5_full/T4'
SCRATCH = ROOT/'suite5_t4_special_io'
SCRATCH.mkdir(exist_ok=True)

def brute_at(n,m,centers,start,goal,r):
    blocked = bytearray(n*m)
    for cx,cy in centers:
        for x in range(max(0,cx-r+1),min(n-1,cx+r-1)+1):
            for y in range(max(0,cy-r+1),min(m-1,cy+r-1)+1):
                blocked[x*m+y] = 1
    area = sum(blocked)
    si = start[0]*m+start[1]
    ei = goal[0]*m+goal[1]
    if blocked[si] or blocked[ei]:
        return False,area
    queue = deque([si])
    blocked[si] = 2
    while queue:
        v = queue.popleft()
        if v == ei:
            return True,area
        x,y = divmod(v,m)
        for u,valid in ((v-m,x>0),(v+m,x+1<n),(v-1,y>0),(v+1,y+1<m)):
            if valid and blocked[u] == 0:
                blocked[u] = 2
                queue.append(u)
    return False,area

def run(exe,body):
    (SCRATCH/'green.in').write_text(body,encoding='utf-8',newline='\n')
    p = subprocess.run([str(exe)],cwd=SCRATCH,capture_output=True,timeout=15)
    assert p.returncode == 0,(exe,p.stderr[:200])
    return (SCRATCH/'green.out').read_text(encoding='utf-8').strip()

cases = {
    2:(50,50,(0,0),(49,49),[(25,y) for y in [0,7,14,21,28,35,42,49]]+[(35,20),(35,30)],4),
    4:(900,1000,(450,10),(450,990),[(450,500)],451),
}
for point,(n,m,start,goal,centers,fail_r) in cases.items():
    assert len(centers)==len(set(centers)) and start not in centers and goal not in centers
    feasible,area = brute_at(n,m,centers,start,goal,fail_r-1)
    blocked,_ = brute_at(n,m,centers,start,goal,fail_r)
    assert feasible and not blocked,(point,feasible,blocked)
    body = '\n'.join([f'{n} {m} {len(centers)}',f'{start[0]} {start[1]}',f'{goal[0]} {goal[1]}']
                     + [f'{x} {y}' for x,y in centers])+'\n'
    std = run(ROOT/'suite5_t4_candidate.exe',body)
    other = run(ROOT/'green_bench'/'paint_binary.exe',body)
    assert std == other == str(area),(point,std,other,area)
    (BASE/'data'/f'{point}.in').write_text(body,encoding='utf-8',newline='\n')
    (BASE/'data'/f'{point}.out').write_text(std+'\n',encoding='utf-8',newline='\n')
    print(f'{point}: max_radius={fail_r-1} area={area} independently verified',flush=True)

with zipfile.ZipFile(BASE/'data.zip','w',compression=zipfile.ZIP_DEFLATED) as z:
    for point in range(1,21):
        for suffix in ('in','out'):
            path = BASE/'data'/f'{point}.{suffix}'
            z.write(path,path.name)
print('T4 points 2 and 4 installed; data.zip rebuilt',flush=True)
