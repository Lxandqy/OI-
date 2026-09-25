from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).parent
GPP = Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')

for suite,task in [(4,2),(4,3),(4,4),(5,3),(5,4),(7,4)]:
    code = ROOT / 'new_std' / f's{suite}t{task}.cpp'
    exe = ROOT / 'bin' / f'new_s{suite}t{task}.exe'
    p = subprocess.run([str(GPP),'-std=c++14','-O2',str(code),'-o',str(exe)],capture_output=True,text=True)
    if p.returncode:
        print(f'COMPILE FAIL {suite} {task}\n{p.stderr[:1000]}', flush=True)
        continue
    inp_dir = ROOT / f'source{suite}' / f'T{task}' / 'judge/data'
    ins = sorted(inp_dir.glob('*.in'),key=lambda x:int(x.stem))
    bad=[]
    max_time=0
    for inp in ins:
        start=time.perf_counter()
        if (suite,task) in [(4,4),(5,4)]:
            io_name = 'eval' if (suite,task)==(4,4) else 'green'
            scratch=ROOT/'check_io'
            scratch.mkdir(exist_ok=True)
            (scratch/f'{io_name}.in').write_bytes(inp.read_bytes())
            p=subprocess.run([str(exe)],cwd=scratch,capture_output=True,timeout=30)
            actual=(scratch/f'{io_name}.out').read_text().split() if p.returncode==0 else []
        else:
            p=subprocess.run([str(exe)],input=inp.read_bytes(),capture_output=True,timeout=30)
            actual=p.stdout.decode().split() if p.returncode==0 else []
        max_time=max(max_time,time.perf_counter()-start)
        expected=inp.with_suffix('.out').read_text().split()
        if actual != expected:
            bad.append((inp.stem,p.returncode,' '.join(expected)[:80],' '.join(actual)[:80],p.stderr.decode(errors='replace')[:80]))
    print(f'S{suite} T{task} maxsec={max_time:.3f} bad={len(bad)} {bad[:3]}',flush=True)
