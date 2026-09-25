from pathlib import Path
import re
import subprocess
import time

ROOT = Path(__file__).parent
BASE = ROOT / 'built/suite5_full/T4'
GPP = Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
WORK = ROOT / 'green_bench'
WORK.mkdir(exist_ok=True)

lines = ['1000 1000 1000', '0 0', '999 999']
for x in range(484, 516):
    for y in range(484, 516):
        lines.append(f'{x} {y}')
        if len(lines) == 1003:
            break
    if len(lines) == 1003:
        break
body = '\n'.join(lines) + '\n'
(WORK / 'green.in').write_text(body, encoding='utf-8')

solution = (BASE / 'solution.md').read_text(encoding='utf-8')
partial = re.findall(r'```cpp\n(.*?)\n```', solution, re.S)[0]
slow = partial.replace(
    'int answer = 0;\n\tfor(int r = 1; r <= max(n,m); r++){\n\t\tint area;\n\t\tif(!check(r,area)) break;\n\t\tanswer = area;\n\t}\n\tcout << answer',
    'int lo = 0, hi = max(n,m) + 1;\n\twhile(lo + 1 < hi){\n\t\tint mid = (lo + hi) / 2;\n\t\tint area;\n\t\tif(check(mid,area)) lo = mid;\n\t\telse hi = mid;\n\t}\n\tint answer = 0;\n\tif(lo > 0) check(lo,answer);\n\tcout << answer',
)
assert slow != partial
for name, source in [('std', (BASE / 'std.cpp').read_text(encoding='utf-8')),
                     ('paint_binary', slow), ('paint_linear', partial)]:
    src = WORK / f'{name}.cpp'
    exe = WORK / f'{name}.exe'
    src.write_text(source, encoding='utf-8')
    subprocess.run([str(GPP), '-O2', '-std=c++14', str(src), '-o', str(exe)], check=True)
    start = time.perf_counter()
    try:
        subprocess.run([str(exe)], cwd=WORK, check=True, timeout=3.0)
        result = (WORK / 'green.out').read_text(encoding='utf-8').strip()
        status = f'answer={result}'
    except subprocess.TimeoutExpired:
        status = 'TLE after 3.0s'
    print(name, round(time.perf_counter()-start, 3), status, flush=True)
