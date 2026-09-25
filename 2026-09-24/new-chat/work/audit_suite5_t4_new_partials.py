from pathlib import Path
import subprocess
import time

ROOT = Path(__file__).parent
BASE = ROOT / 'built/suite5_full/T4/data'
GPP = Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
SCRATCH = ROOT / 'suite5_t4_partial_audit_io'
SCRATCH.mkdir(exist_ok=True)

for kind in ('k10','adj'):
    cpp = ROOT / f'suite5_t4_partial_{kind}.cpp'
    exe = ROOT / f'suite5_t4_partial_{kind}.exe'
    subprocess.run([str(GPP),'-std=c++14','-O2',str(cpp),'-o',str(exe)],check=True)
    statuses = []
    for i in range(1,21):
        (SCRATCH / 'green.in').write_bytes((BASE / f'{i}.in').read_bytes())
        start = time.perf_counter()
        try:
            p = subprocess.run([str(exe)],cwd=SCRATCH,capture_output=True,timeout=1.15)
            got = (SCRATCH / 'green.out').read_text(encoding='utf-8').split() if p.returncode == 0 else []
            expected = (BASE / f'{i}.out').read_text(encoding='utf-8').split()
            status = 'PASS' if got == expected else 'WA/RE'
        except subprocess.TimeoutExpired:
            status = 'TLE'
        statuses.append(status)
        elapsed = time.perf_counter() - start
        print(f'{kind} {i:02d} {status} {elapsed:.3f}s',flush=True)
    print(kind, 'passed', sum(x == 'PASS' for x in statuses), 'of 20', statuses,flush=True)
