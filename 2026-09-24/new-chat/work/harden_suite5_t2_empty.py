from pathlib import Path
import subprocess
import zipfile

ROOT = Path(__file__).parent
BASE = ROOT/'built/suite5_full/T2'
DATA = BASE/'data'
lines = ['1000 3000 3000']
for i in range(1,1001):
    weight = 1 + (17*i) % 3000
    value = 1 + (71*i) % 2999
    assert value < 3000
    lines.append(f'{weight} {value}')
body = '\n'.join(lines)+'\n'
p = subprocess.run([str(ROOT/'suite5_t2_candidate.exe')],input=body.encode(),capture_output=True,check=True,timeout=5)
assert p.stdout.decode().strip() == '0',p.stdout
(DATA/'10.in').write_text(body,encoding='utf-8',newline='\n')
(DATA/'10.out').write_text('0\n',encoding='utf-8',newline='\n')
with zipfile.ZipFile(BASE/'data.zip','w',compression=zipfile.ZIP_DEFLATED) as z:
    for point in range(1,11):
        for suffix in ('in','out'):
            path = DATA/f'{point}.{suffix}'
            z.write(path,path.name)
print('T2 point10: all item gains are negative; 2D DP confirms answer 0; data.zip rebuilt',flush=True)
