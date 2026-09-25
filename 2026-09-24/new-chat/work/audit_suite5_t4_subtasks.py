from pathlib import Path
import hashlib

ROOT = Path(__file__).parent
BASE = ROOT/'built/suite5_full/T4/data'
seen = {}
for point in range(1,21):
    body = (BASE/f'{point}.in').read_bytes()
    lines = body.decode().splitlines()
    n,m,k = map(int,lines[0].split())
    sx,sy = map(int,lines[1].split())
    ex,ey = map(int,lines[2].split())
    adjacent = abs(sx-ex)+abs(sy-ey) == 1
    corners = (sx,sy)==(0,0) and (ex,ey)==(n-1,m-1)
    if point <= 2:
        assert n<=50 and m<=50 and k<=10
    elif point <= 4:
        assert k==1
    elif point <= 6:
        assert k<=10
    elif point <= 8:
        assert adjacent
    elif point <= 10:
        assert corners
    else:
        assert k>10 and not adjacent and not corners
    digest = hashlib.sha256(body).hexdigest()
    assert digest not in seen,(point,seen.get(digest))
    seen[digest] = point
    print(f'{point}: {n}x{m}, k={k}, adjacent={adjacent}, corners={corners}',flush=True)
print('T4 subtask properties and 20 distinct inputs: PASS',flush=True)
