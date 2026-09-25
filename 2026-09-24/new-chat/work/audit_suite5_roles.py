from pathlib import Path
import subprocess

ROOT = Path(__file__).parent
BASE = ROOT/'built/suite5_full/T4'
GPP = Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
old = 'cin >> n >> m >> k;'
code = (BASE/'std.cpp').read_text(encoding='utf-8')
assert code.count(old) == 1
code = code.replace(old,old+'\n\tswap(n,m);')
source = ROOT/'suite5_t4_swap_dimensions.cpp'
exe = ROOT/'suite5_t4_swap_dimensions.exe'
source.write_text(code,encoding='utf-8')
subprocess.run([str(GPP),'-std=c++14','-O2',str(source),'-o',str(exe)],check=True)
scratch = ROOT/'suite5_role_io'
scratch.mkdir(exist_ok=True)
failures = []
for point in range(1,21):
    path = BASE/'data'/f'{point}.in'
    (scratch/'green.in').write_bytes(path.read_bytes())
    p = subprocess.run([str(exe)],cwd=scratch,capture_output=True,timeout=5)
    actual = (scratch/'green.out').read_text(encoding='utf-8').split() if p.returncode==0 else []
    expected = path.with_suffix('.out').read_text(encoding='utf-8').split()
    if actual != expected:
        failures.append(point)
print('T4 swap n,m killed by',failures,'count',len(failures),flush=True)
assert failures
