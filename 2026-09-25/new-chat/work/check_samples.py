from pathlib import Path
import subprocess

p = Path(__file__).parent
samples = {
    1: '5 1 2 3 4\n-4 5 -7 3 -2\n',
    2: '6\n1 2\n2 3\n3 1\n3 4\n4 5\n5 6\n',
    3: '4\n0 1 2 4\n1 2\n2 3\n3 4\n',
    4: '3 1\n3 1 5\n',
}
for t, raw in samples.items():
    out = subprocess.check_output([str(p / f'T{t}.exe')], input=raw, text=True)
    print('T', t, 'INPUT\n' + raw + 'OUTPUT\n' + out, flush=True)
