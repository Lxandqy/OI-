from pathlib import Path
import subprocess

root = Path(__file__).parent
cases = {
    1: ['partial_zero_T1', 'partial_singleton_T1', 'partial_cover_T1',
        'partial_disjoint_T1', 'partial_only_fourth_T1', 'partial_sum_T1'],
    3: ['partial_consecutive_T3', 'partial_neighbor_T3'],
    4: ['partial_unchanged_T4', 'partial_increasing_T4',
        'partial_first_T4', 'partial_pair_T4'],
}

for t, names in cases.items():
    for name in names:
        passed = []
        for i in range(9, 21):
            folder = root / 'built' / f'T{t}' / 'data'
            raw = (folder / f'{i}.in').read_text(encoding='utf-8')
            expected = (folder / f'{i}.out').read_text(encoding='utf-8')
            try:
                proc = subprocess.run([str(root / (name + '.exe'))], input=raw,
                                      text=True, capture_output=True, timeout=2 if t == 1 else 4)
                if proc.returncode == 0 and proc.stdout == expected:
                    passed.append(i)
            except subprocess.TimeoutExpired:
                pass
        print(name, passed, flush=True)
