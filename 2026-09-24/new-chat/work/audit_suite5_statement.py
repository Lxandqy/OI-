from collections import deque
from datetime import date, timedelta
from pathlib import Path
import re

ROOT = Path(__file__).parent
SOURCE = ROOT / 'source5'
BUILT = ROOT / 'built/suite5_full'

def valid_input(task, text, point=None):
    a = list(map(int, text.split()))
    if task == 1:
        assert len(a) == 3
        y, m, d = a
        assert 2000 <= y <= 7000
        date(y, m, d)
        if point is not None and point <= 3:
            assert y <= 2200
        if point is not None and point <= 6:
            assert y <= 4000
    elif task == 2:
        n, m, k = a[:3]
        assert 1 <= n <= 1000 and 1 <= m <= 3000 and 1 <= k <= 3000
        assert len(a) == 3 + 2*n
        assert all(1 <= x <= 100000 for x in a[3:])
        if point is not None and point <= 2:
            assert n <= 20
        if point is not None and 3 <= point <= 5:
            assert m <= 300
    elif task == 3:
        q = a[0]
        assert 1 <= q <= 10 and len(a) == 1 + 2*q
        ranges = list(zip(a[1::2], a[2::2]))
        assert sum(hi for _, hi in ranges) <= 200000
        assert all(1 <= lo < hi <= 100000 for lo, hi in ranges)
        if point is not None and point <= 2:
            assert all(hi-lo <= 20 for lo, hi in ranges)
        if point is not None and 3 <= point <= 5:
            assert all(hi <= 2000 for _, hi in ranges)
    else:
        n, m, k = a[:3]
        assert 2 <= n <= 1000 and 2 <= m <= 1000
        assert 1 <= k <= min(n*m-2, 1000)
        assert len(a) == 7 + 2*k
        points = list(zip(a[3::2], a[4::2]))
        assert len(points) == k+2 and len(set(points)) == len(points)
        assert all(0 <= x < n and 0 <= y < m for x, y in points)
        if point is not None:
            if point <= 2:
                assert n <= 50 and m <= 50 and k <= 10
            elif point <= 4:
                assert k == 1
            elif point <= 6:
                assert k <= 10
            elif point <= 8:
                (sx,sy),(ex,ey) = points[:2]
                assert abs(sx-ex)+abs(sy-ey) == 1
            elif point <= 10:
                assert points[0] == (0,0) and points[1] == (n-1,m-1)
    return a

def independent_sample_answer(task, text):
    a = valid_input(task, text)
    if task == 1:
        cur = date(*a)
        while True:
            cur += timedelta(days=1)
            s = str(cur.year)+str(cur.month)+str(cur.day)
            if s == s[::-1]:
                return f'{cur.year} {cur.month} {cur.day}'
    if task == 2:
        n,m,k = a[:3]
        items = list(zip(a[3::2], a[4::2]))
        assert n <= 20
        answer = 0
        for mask in range(1 << n):
            weight = score = 0
            for i,(w,v) in enumerate(items):
                if mask >> i & 1:
                    weight += w
                    score += v-k
            if weight <= m:
                answer = max(answer,score)
        return str(answer)
    if task == 3:
        lines = []
        for lo,hi in zip(a[1::2], a[2::2]):
            best = count = 0
            def dfs(x, length):
                nonlocal best,count
                if length > best:
                    best,count = length,1
                elif length == best:
                    count += 1
                for y in range(2*x,hi+1,x):
                    dfs(y,length+1)
            for x in range(lo,hi+1):
                dfs(x,1)
            lines.append(f'{best} {count}')
        return '\n'.join(lines)
    n,m,k = a[:3]
    start = (a[3],a[4])
    goal = (a[5],a[6])
    centers = list(zip(a[7::2],a[8::2]))
    answer = 0
    for r in range(1,max(n,m)+1):
        blocked = [[False]*m for _ in range(n)]
        for cx,cy in centers:
            for x in range(max(0,cx-r+1),min(n-1,cx+r-1)+1):
                for y in range(max(0,cy-r+1),min(m-1,cy+r-1)+1):
                    blocked[x][y] = True
        if blocked[start[0]][start[1]] or blocked[goal[0]][goal[1]]:
            break
        q = deque([start])
        seen = {start}
        while q:
            x,y = q.popleft()
            for nx,ny in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                if 0 <= nx < n and 0 <= ny < m and not blocked[nx][ny] and (nx,ny) not in seen:
                    seen.add((nx,ny))
                    q.append((nx,ny))
        if goal not in seen:
            break
        answer = sum(sum(row) for row in blocked)
    return str(answer)

errors = []
for task in range(1,5):
    src = SOURCE / f'T{task}'
    md = (src/'release/statement.md').read_text(encoding='utf-8')
    blocks = re.findall(r'```text\s*\n(.*?)\n```',md,re.S)
    pairs = list(zip(blocks[::2],blocks[1::2]))
    assert len(blocks) % 2 == 0
    sample_files = sorted((src/'release/sample').glob('sample*.in'))
    assert len(pairs) == len(sample_files)
    for i,((sample_input,sample_output),path) in enumerate(zip(pairs,sample_files),1):
        try:
            assert sample_input.split() == path.read_text(encoding='utf-8').split()
            assert sample_output.split() == path.with_suffix('.out').read_text(encoding='utf-8').split()
            actual = independent_sample_answer(task,sample_input)
            assert actual.split() == sample_output.split(),(actual,sample_output)
        except Exception as exc:
            errors.append((task,'sample',i,str(exc)))
    for label,base in [('source',src/'judge/data'),('built',BUILT/f'T{task}'/'data')]:
        inputs = sorted(base.glob('*.in'),key=lambda p:int(p.stem))
        expected_count = 20 if task == 4 else 10
        if len(inputs) != expected_count:
            errors.append((task,label,'input count',len(inputs)))
        for path in inputs:
            try:
                values = valid_input(task,path.read_text(encoding='utf-8'),int(path.stem))
                output = path.with_suffix('.out').read_text(encoding='utf-8').split()
                assert len(output) == (3 if task == 1 else 2*values[0] if task == 3 else 1)
                assert all(re.fullmatch(r'-?\d+',x) for x in output)
            except Exception as exc:
                errors.append((task,label,path.name,str(exc)))
    print(f'T{task}: {len(pairs)} independent samples; source/built formal inputs checked',flush=True)
print('ERRORS',errors,'TOTAL',len(errors),flush=True)
