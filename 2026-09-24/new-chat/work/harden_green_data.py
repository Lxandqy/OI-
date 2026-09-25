from pathlib import Path
import subprocess
import sys
import time
import zipfile

ROOT = Path(__file__).parent
BASE = ROOT / 'built/suite5_full/T4'
BIN = ROOT / 'green_bench'
WRITE = '--write' in sys.argv

def centers(n, m, k, place, dx=0, dy=0):
    if k == 1:
        return [(n // 2 + dx, m // 2 + dy)]
    if k == 10:
        rows, cols = 2, 5
    else:
        rows, cols = 40, 25
    if place == 'center':
        x0 = n // 2 - rows // 2 + dx
        y0 = m // 2 - cols // 2 + dy
    elif place == 'northwest':
        x0, y0 = 0, 0
    elif place == 'southeast':
        x0, y0 = n - rows, m - cols
    else:
        raise ValueError(place)
    result = [(x0 + i, y0 + j) for i in range(rows) for j in range(cols)]
    assert len(result) == k and len(set(result)) == k
    return result

def testcase(n, m, k, place, start, goal, dx=0, dy=0):
    pts = centers(n, m, k, place, dx, dy)
    assert start != goal and start not in pts and goal not in pts
    assert all(0 <= x < n and 0 <= y < m for x, y in pts)
    return '\n'.join([f'{n} {m} {k}', f'{start[0]} {start[1]}',
                      f'{goal[0]} {goal[1]}'] +
                     [f'{x} {y}' for x, y in pts]) + '\n'

CASES = {
    3: testcase(1000, 800, 1, 'center', (0, 0), (999, 799)),
    5: testcase(1000, 1000, 10, 'center', (0, 0), (999, 999)),
    6: testcase(800, 900, 10, 'center', (0, 0), (799, 899)),
    7: testcase(1000, 1000, 1000, 'northwest', (999, 998), (999, 999)),
    8: testcase(777, 999, 1000, 'center', (0, 0), (0, 1)),
    9: testcase(1000, 1000, 1000, 'center', (0, 0), (999, 999)),
    10: testcase(900, 800, 1000, 'center', (0, 0), (899, 799)),
    11: testcase(1000, 1000, 1000, 'southeast', (0, 0), (0, 1)),
    12: testcase(850, 920, 1000, 'center', (0, 230), (849, 690)),
    13: testcase(1000, 1000, 1000, 'center', (0, 0), (999, 999), 25, -25),
    14: testcase(850, 1000, 1000, 'northwest', (849, 998), (849, 999)),
    15: testcase(1000, 920, 1000, 'center', (250, 0), (750, 919)),
    16: testcase(850, 1000, 1000, 'southeast', (0, 0), (0, 999)),
    17: testcase(1000, 1000, 1000, 'center', (0, 0), (999, 999), -30, 30),
    18: testcase(850, 920, 1000, 'northwest', (849, 918), (849, 919)),
    19: testcase(1000, 1000, 1000, 'southeast', (0, 100), (100, 0)),
    20: testcase(850, 1000, 1000, 'center', (0, 333), (849, 666)),
}

selected = [int(arg.split('=', 1)[1]) for arg in sys.argv if arg.startswith('--point=')]
if selected:
    assert len(selected) == 1 and selected[0] in CASES
    CASES = {selected[0]:CASES[selected[0]]}

def run(name, body, limit):
    scratch = BIN / 'run'
    scratch.mkdir(exist_ok=True)
    (scratch / 'green.in').write_text(body, encoding='utf-8')
    start = time.perf_counter()
    try:
        subprocess.run([str(BIN / f'{name}.exe')], cwd=scratch,
                       capture_output=True, check=True, timeout=limit)
    except subprocess.TimeoutExpired:
        return None, time.perf_counter() - start
    return (scratch / 'green.out').read_text(encoding='utf-8').split(), time.perf_counter() - start

answers = {}
for point, body in CASES.items():
    expected, std_time = run('std', body, 5)
    other, binary_time = run('paint_binary', body, 5)
    assert expected is not None and other == expected, (point, expected, other)
    simple, simple_time = run('paint_linear', body, 1.15)
    assert simple is None or simple == expected, (point, expected, simple)
    print(f'{point:2d}: std={std_time:.3f}s paint_binary={binary_time:.3f}s '
          f'linear={simple_time:.3f}s {"TLE" if simple is None else "pass"} '
          f'answer={expected[0]}', flush=True)
    answers[point] = expected[0]

if WRITE:
    for point, body in CASES.items():
        (BASE / 'data' / f'{point}.in').write_text(body, encoding='utf-8', newline='\n')
        (BASE / 'data' / f'{point}.out').write_text(answers[point] + '\n',
                                                   encoding='utf-8', newline='\n')
    with zipfile.ZipFile(BASE / 'data.zip', 'w', compression=zipfile.ZIP_DEFLATED) as z:
        for point in range(1, 21):
            for suffix in ('in', 'out'):
                path = BASE / 'data' / f'{point}.{suffix}'
                z.write(path, path.name)
    print('installed', len(CASES), 'cases and rebuilt data.zip', flush=True)
