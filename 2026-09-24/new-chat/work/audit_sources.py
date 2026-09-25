from pathlib import Path
import subprocess
import sys
import time
sys.set_int_max_str_digits(0)

ROOT = Path(__file__).parent
GPP = Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')
BIN = ROOT / 'bin'
BIN.mkdir(exist_ok=True)

def expression_answer(data):
    s = data.strip()
    product = 1
    for block in s.split('*'):
        product *= sum(int(x) for x in block.split('+'))
    return str(product)

def divisibility_answer(data):
    vals = list(map(int, data.split()))
    t = vals[0]
    out = []
    for q in range(t):
        lo, hi = vals[1 + 2*q:3 + 2*q]
        length = [1] * (hi + 1)
        count = [1] * (hi + 1)
        for x in range(lo, hi + 1):
            for y in range(2*x, hi + 1, x):
                z = length[x] + 1
                if z > length[y]:
                    length[y], count[y] = z, count[x]
                elif z == length[y]:
                    count[y] += count[x]
        maximum = max(length[lo:])
        out.append(f'{maximum} {sum(count[x] for x in range(lo, hi+1) if length[x] == maximum)}')
    return '\n'.join(out)

for suite in range(4, 8):
    for task in range(1, 5):
        source = ROOT / f'source{suite}' / f'T{task}'
        code = source / 'judge/std.cpp'
        inputs = sorted((source / 'judge/data').glob('*.in'), key=lambda p: int(p.stem))
        if (suite,task) == (4,4):
            executable = None
            reference = expression_answer
        elif (suite,task) == (5,3):
            executable = None
            reference = divisibility_answer
        else:
            executable = BIN / f's{suite}t{task}.exe'
            result = subprocess.run([str(GPP), '-std=c++14', '-O2', str(code), '-o', str(executable)], capture_output=True, text=True)
            if result.returncode:
                print(f'COMPILE_FAIL {suite} {task}: {result.stderr[:300]}', flush=True)
                continue
            reference = None
        failures = []
        longest = 0
        for inp in inputs:
            expected = inp.with_suffix('.out').read_text(encoding='utf-8').split()
            try:
                started = time.perf_counter()
                if reference is not None:
                    actual = reference(inp.read_text(encoding='utf-8')).split()
                elif (suite,task) == (5,4):
                    scratch = ROOT / 'audit_fileio'
                    scratch.mkdir(exist_ok=True)
                    (scratch / 'green.in').write_bytes(inp.read_bytes())
                    subprocess.run([str(executable)], cwd=scratch, capture_output=True, timeout=30, check=True)
                    actual = (scratch / 'green.out').read_text().split()
                else:
                    p = subprocess.run([str(executable)], input=inp.read_bytes(), capture_output=True, timeout=30, check=True)
                    actual = p.stdout.decode().split()
                elapsed = time.perf_counter() - started
                longest = max(longest, elapsed)
                if actual != expected:
                    failures.append((inp.stem, 'WA', ' '.join(expected)[:100], ' '.join(actual)[:100]))
            except Exception as e:
                failures.append((inp.stem, type(e).__name__, str(e)[:100]))
        print(f'S{suite} T{task} points={len(inputs)} maxsec={longest:.3f} failures={failures[:5]} totalfails={len(failures)}', flush=True)
