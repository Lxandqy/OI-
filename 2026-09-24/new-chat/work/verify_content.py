from pathlib import Path
import re
import subprocess
import time
import zipfile
import hashlib
import sys

ROOT=Path(__file__).parent
BUILT=ROOT/'built'
GPP=Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
BIN=ROOT/'verified_bin'
BIN.mkdir(exist_ok=True)
partial_results=[]
errors=[]
LIMITS={4:[1,2,1,1],5:[1,2,2,1],6:[1,1,2,2],7:[1,1,1,2]}

def run(exe,s,t,inp,timeout=5):
    if (s,t) in [(4,4),(5,4)]:
        name='eval' if (s,t)==(4,4) else 'green'
        scratch=ROOT/'verify_io'; scratch.mkdir(exist_ok=True)
        (scratch/f'{name}.in').write_bytes(inp.read_bytes())
        p=subprocess.run([str(exe)],cwd=scratch,capture_output=True,timeout=timeout)
        if p.returncode: raise RuntimeError(f'exit {p.returncode} {p.stderr[:150]}')
        return (scratch/f'{name}.out').read_text(encoding='utf-8').split()
    with inp.open('rb') as stream:
        p=subprocess.run([str(exe)],stdin=stream,capture_output=True,timeout=timeout)
    if p.returncode: raise RuntimeError(f'exit {p.returncode} {p.stderr[:150]}')
    return p.stdout.decode().split()

suites=[int(sys.argv[1])] if len(sys.argv)==2 else range(4,8)
for s in suites:
    suite=BUILT/f'suite{s}_full'
    pieces=[]
    for t in range(1,5):
        base=suite/f'T{t}'
        std=(base/'std.cpp').read_text(encoding='utf-8')
        sol=(base/'solution.md').read_text(encoding='utf-8')
        pieces.append(sol)
        blocks=re.findall(r'```cpp\n(.*?)\n```',sol,re.S)
        if not blocks or blocks[-1].rstrip() != std.rstrip(): errors.append((s,t,'std differs from solution'))
        ins=sorted((base/'data').glob('*.in'),key=lambda p:int(p.stem))
        for i,block in enumerate(blocks):
            source=BIN/f's{s}t{t}b{i}.cpp'; source.write_text(block+'\n',encoding='utf-8')
            exe=BIN/f's{s}t{t}b{i}.exe'
            c=subprocess.run([str(GPP),'-std=c++14','-O2',str(source),'-o',str(exe)],capture_output=True,text=True)
            if c.returncode:
                errors.append((s,t,f'block {i} compile',c.stderr[:200])); continue
            if i==len(blocks)-1:
                passed=0
                for inp in ins:
                    try:
                        actual=run(exe,s,t,inp,timeout=15)
                        expected=inp.with_suffix('.out').read_text(encoding='utf-8').split()
                        if actual==expected: passed+=1
                        else: errors.append((s,t,inp.stem,'std WA'))
                    except Exception as e: errors.append((s,t,inp.stem,f'std {type(e).__name__}: {e}'))
                print(f'FULL s{s}t{t} {passed}/{len(ins)}',flush=True)
            else:
                score=0
                first_fail=None
                for inp in ins:
                    try:
                        actual=run(exe,s,t,inp,timeout=LIMITS[s][t-1]+0.15)
                        expected=inp.with_suffix('.out').read_text(encoding='utf-8').split()
                        if actual==expected: score+=1
                        elif first_fail is None: first_fail=(inp.stem,'WA')
                    except subprocess.TimeoutExpired:
                        if first_fail is None: first_fail=(inp.stem,'TLE')
                    except Exception as e:
                        if first_fail is None: first_fail=(inp.stem,type(e).__name__)
                partial_results.append((s,t,i,score,len(ins),first_fail))
                print(f'PART s{s}t{t} block{i} {score}/{len(ins)} first={first_fail}',flush=True)
        with zipfile.ZipFile(base/'data.zip') as z:
            names=z.namelist()
            expected={p.name for p in (base/'data').iterdir()}
            if set(names)!=expected or len(names)!=len(expected): errors.append((s,t,'data.zip members'))
            for name in names:
                if z.read(name)!=(base/'data'/name).read_bytes(): errors.append((s,t,'data.zip mismatch',name))
            if z.testzip(): errors.append((s,t,'data.zip corrupt'))
        with zipfile.ZipFile(base/'attachment.zip') as z:
            if z.testzip(): errors.append((s,t,'attachment.zip corrupt'))
            if sorted(z.namelist())!=['attachment1.in','attachment1.out','attachment2.in','attachment2.out']:
                errors.append((s,t,'attachment members'))
            for j in (1,2):
                iname=f'attachment{j}.in'; oname=f'attachment{j}.out'
                scratch=ROOT/'attachment_check'; scratch.mkdir(exist_ok=True)
                p=scratch/iname; p.write_bytes(z.read(iname))
                try:
                    exe=BIN/f's{s}t{t}b{len(blocks)-1}.exe'
                    got=run(exe,s,t,p,timeout=15)
                    want=z.read(oname).decode().split()
                    if got!=want: errors.append((s,t,'attachment WA',j))
                except Exception as e: errors.append((s,t,'attachment error',j,str(e)[:100]))
    root_sol=(suite/'solution.md').read_text(encoding='utf-8')
    if root_sol.strip()!='\n\n'.join(p.strip() for p in pieces).strip(): errors.append((s,'root solution mismatch'))

print('PARTIAL_RESULTS',partial_results)
print('ERRORS',errors[:30],'TOTAL',len(errors))
