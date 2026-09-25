from pathlib import Path
import subprocess

p = Path(__file__).parent
gpp = r'D:\Dev-Cpp\MinGW64\bin\g++.exe'

src1 = (p / 'T1.cpp').read_text(encoding='utf-8')
assert 'cout << ans <<' in src1
mut1 = src1.replace("\tcout << ans << '\\n';", "\tcout << max(ans,0LL) << '\\n';")

src2 = (p / 'T2.cpp').read_text(encoding='utf-8')
assert 'if(len == 3 && sz[cyc[1]] == 1' in src2
mut2 = src2.replace('if(len == 3 && sz[cyc[1]] == 1', 'if(false && len == 3 && sz[cyc[1]] == 1')

src3 = (p / 'T3.cpp').read_text(encoding='utf-8')
needle3 = '\tfor(int i = 1; i <= n; i++) comp[i] = findRoot(i);'
assert needle3 in src3
mut3 = src3.replace(needle3, "\tint only = 0;\n\tfor(int i = 1; i <= n; i++) only = max(only,sizeD[findRoot(i)]);\n\tcout << only << '\\n';\n\treturn 0;\n" + needle3)

src4 = (p / 'T4.cpp').read_text(encoding='utf-8')
assert '\tcin >> n >> k;' in src4
mut4 = src4.replace('\tcin >> n >> k;', '\tcin >> k >> n;')

for t, content in enumerate((mut1, mut2, mut3, mut4), 1):
    source = p / f'mutant_T{t}.cpp'
    binary = p / f'mutant_T{t}.exe'
    source.write_text(content, encoding='utf-8')
    subprocess.run([gpp, '-std=c++14', '-O2', str(source), '-o', str(binary)], check=True)

for t, point in ((1, 4), (2, 1), (3, 5), (4, 5)):
    folder = p / 'built' / f'T{t}' / 'data'
    raw = (folder / f'{point}.in').read_text(encoding='utf-8')
    exp = (folder / f'{point}.out').read_text(encoding='utf-8')
    proc = subprocess.run([str(p / f'mutant_T{t}.exe')], input=raw, text=True,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=10)
    assert proc.stdout != exp, (t, point, 'mutant survived')
    print(f'T{t} mutant rejected on point {point}: expected {exp[:40]!r}, got {proc.stdout[:40]!r}', flush=True)

# A local-neighbour averaging rule loses the first comparison on the long trap.
raw = (p / 'built' / 'T4' / 'data' / '9.in').read_text(encoding='utf-8')
z = list(map(int, raw.split()))
first_pair = (z[2] + z[3]) / 2
first_three = (z[2] + z[3] + z[4]) / 3
assert first_three > first_pair
print('T4 local-pair trap: first pair', first_pair, 'best prefix', first_three)
