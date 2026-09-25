from pathlib import Path
import subprocess
import sys

ROOT=Path(__file__).parent
BUILT=ROOT/'built'
GPP=Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
TMP=ROOT/'mutants';TMP.mkdir(exist_ok=True)

MUTANTS={
    (4,1):('cnt[x] >= 2','cnt[x] >= 3','边界：必须只重复两张'),
    (4,2):('long long r = x * x % k;','long long r = x * x % n;','参数：把 k 当成 n'),
    (4,3):('if(last != first) ans','if(last == first) ans','边界：首尾颜色'),
    (4,4):("}else if(s[i] == '+'){","}else if(s[i] == '*'){",'运算符边界'),
    (5,1):('do {\n','if(palindromeDate(y,m,d)){\n\t\tcout << y << \' \' << m << \' \' << d << \'\\n\';\n\t\treturn 0;\n\t}\n\tdo {\n','边界：严格晚于'),
    (5,2):('cin >> n >> m >> k;','cin >> n >> m >> k;\n\tint oldm = m; m = (int)k; k = oldm;','参数：容量与扣减系数'),
    (5,3):('while(L * power * 2 <= R)','while(L * power * 2 < R)','边界：恰好二倍'),
    (5,4):('max(0,cx[i] - r + 1)','max(0,cx[i] - r)','边界：花圃左端'),
    (6,1):('cnt[r] > cnt[ans]','cnt[r] >= cnt[ans]','边界：并列取最小'),
    (6,2):("cout << dp[n][x] << '\\n';","cout << max(0LL,dp[n][x]) << '\\n';",'边界：恰好选满且负值'),
    (6,3):('while(r >= l','while(r > l','边界：允许自身配对'),
    (6,4):('if(j < rightEnd[i + 1])','if(j <= rightEnd[i + 1])','边界：原数末尾不切'),
    (7,1):('long long ans = 0;','int ans = 0;','数值边界：溢出'),
    (7,2):('if(a[k] < a[j])','if(a[k] <= a[j])','边界：严格比较'),
    (7,3):('if(i == 0 || i == (int)s.size())','if(i == (int)s.size())','名称边界：根须有字母'),
    (7,4):('leaf[u] + (degreeOld[u] == 2)','leaf[u]','边界：断边产生新叶子'),
}

for (s,t),(old,new,reason) in MUTANTS.items():
    if len(sys.argv)==2 and s!=int(sys.argv[1]):
        continue
    base=BUILT/f'suite{s}_full'/f'T{t}'
    code=(base/'std.cpp').read_text(encoding='utf-8')
    if old not in code:
        print(f'MISSING s{s}t{t} {old}',flush=True);continue
    code=code.replace(old,new,1)
    src=TMP/f's{s}t{t}.cpp';src.write_text(code,encoding='utf-8')
    exe=TMP/f's{s}t{t}.exe'
    c=subprocess.run([str(GPP),'-std=c++14','-O2',str(src),'-o',str(exe)],capture_output=True,text=True)
    if c.returncode:
        print(f'CE s{s}t{t} {c.stderr[:100]}',flush=True);continue
    first=None
    results=[]
    for inp in sorted((base/'data').glob('*.in'),key=lambda p:int(p.stem)):
        try:
            if (s,t) in [(4,4),(5,4)]:
                name='eval' if (s,t)==(4,4) else 'green'
                scratch=TMP/'io';scratch.mkdir(exist_ok=True)
                (scratch/f'{name}.in').write_bytes(inp.read_bytes())
                p=subprocess.run([str(exe)],cwd=scratch,capture_output=True,timeout=8)
                out=(scratch/f'{name}.out').read_text().split() if p.returncode==0 else []
            else:
                with inp.open('rb') as stream:
                    p=subprocess.run([str(exe)],stdin=stream,capture_output=True,timeout=8)
                out=p.stdout.decode().split() if p.returncode==0 else []
            want=inp.with_suffix('.out').read_text().split()
            status='OK' if out==want and p.returncode==0 else ('WA' if p.returncode==0 else 'RE')
        except subprocess.TimeoutExpired:
            status='TLE'
        results.append(status)
        if status!='OK' and first is None: first=(inp.stem,status)
    print(f'MUTANT s{s}t{t} {reason} first={first} killed={len([x for x in results if x!="OK"])}/{len(results)}',flush=True)
