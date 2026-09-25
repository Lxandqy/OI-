from bisect import bisect_right
from calendar import monthrange
from datetime import date
from pathlib import Path
import random
import subprocess

ROOT = Path(__file__).parent
BASE = ROOT/'built/suite5_full/T1'
EXE = ROOT/'suite5_t1_candidate.exe'

def palindrome(y,m,d):
    s = f'{y}{m}{d}'
    return s == s[::-1]

actual = []
simple = []
for y in range(2000,7011):
    for m in range(1,13):
        for d in range(1,monthrange(y,m)[1]+1):
            if palindrome(y,m,d):
                actual.append(date(y,m,d))
        for d in range(1,28):
            if palindrome(y,m,d):
                simple.append(date(y,m,d))
assert actual == simple
assert actual[-1] >= date(7010,10,7)
assert actual[bisect_right(actual,date(7000,12,31))] == date(7010,10,7)

cases = []
for inp in sorted((BASE/'data').glob('*.in'),key=lambda p:int(p.stem)):
    cases.append((inp.read_text(encoding='utf-8'),inp.with_suffix('.out').read_text(encoding='utf-8').split()))
for inp in (ROOT/'source5/T1/release/sample').glob('*.in'):
    cases.append((inp.read_text(encoding='utf-8'),inp.with_suffix('.out').read_text(encoding='utf-8').split()))
for x in (date(2000,1,1),date(2000,2,28),date(2000,2,29),date(2018,10,2),date(7000,12,31)):
    y,m,d = x.year,x.month,x.day
    nxt = actual[bisect_right(actual,x)]
    cases.append((f'{y} {m} {d}\n',[str(nxt.year),str(nxt.month),str(nxt.day)]))
rng = random.Random(20260924)
for _ in range(100):
    y = rng.randint(2000,7000)
    m = rng.randint(1,12)
    d = rng.randint(1,monthrange(y,m)[1])
    nxt = actual[bisect_right(actual,date(y,m,d))]
    cases.append((f'{y} {m} {d}\n',[str(nxt.year),str(nxt.month),str(nxt.day)]))
for i,(body,expected) in enumerate(cases,1):
    p = subprocess.run([str(EXE)],input=body,text=True,capture_output=True,timeout=3)
    assert p.returncode == 0 and p.stdout.split() == expected,(i,body,expected,p.stdout,p.stderr)
print(f'Gregorian dates 2000..7010 agree with 1..27 enumeration; {len(cases)} executable cases PASS',flush=True)
