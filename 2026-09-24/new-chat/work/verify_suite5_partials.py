from pathlib import Path
import re
import subprocess
import time

ROOT = Path(__file__).parent
BASE = ROOT/'built/suite5_full'
GPP = Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
SCRATCH = ROOT/'suite5_partial_io'
SCRATCH.mkdir(exist_ok=True)
LIMIT = {2:2.15,3:2.15,4:1.15}
TARGET = {2:2,3:5,4:2}

for task in (2,3,4):
    solution = (BASE/f'T{task}/solution.md').read_text(encoding='utf-8')
    source = re.findall(r'```cpp\n(.*?)\n```',solution,re.S)[0]
    cpp = ROOT/f'suite5_t{task}_partial.cpp'
    exe = ROOT/f'suite5_t{task}_partial.exe'
    cpp.write_text(source+'\n',encoding='utf-8')
    subprocess.run([str(GPP),'-std=c++14','-O2',str(cpp),'-o',str(exe)],check=True)
    statuses = []
    for point in range(1,21 if task==4 else 11):
        path = BASE/f'T{task}/data/{point}.in'
        expected = path.with_suffix('.out').read_text(encoding='utf-8').split()
        start = time.perf_counter()
        try:
            if task == 4:
                (SCRATCH/'green.in').write_bytes(path.read_bytes())
                p = subprocess.run([str(exe)],cwd=SCRATCH,capture_output=True,timeout=LIMIT[task])
                actual = (SCRATCH/'green.out').read_text(encoding='utf-8').split() if p.returncode==0 else []
            else:
                p = subprocess.run([str(exe)],input=path.read_bytes(),capture_output=True,timeout=LIMIT[task])
                actual = p.stdout.decode().split() if p.returncode==0 else []
            status = 'PASS' if actual==expected else 'WA/RE'
        except subprocess.TimeoutExpired:
            status = 'TLE'
        elapsed = time.perf_counter()-start
        statuses.append(status)
        print(f'T{task} point{point:02d}: {status} {elapsed:.3f}s',flush=True)
    assert statuses[:TARGET[task]] == ['PASS']*TARGET[task],(task,statuses)
    assert statuses[TARGET[task]:] == ['TLE']*(len(statuses)-TARGET[task]),(task,statuses)
    print(f'T{task}: target {TARGET[task]}/{len(statuses)} points, every later point TLE',flush=True)
