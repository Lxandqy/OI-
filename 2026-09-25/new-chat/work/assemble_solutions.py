from pathlib import Path

root = Path(__file__).parent
built = root / 'built'
all_parts = []
for t in range(1, 5):
    notes = (root / f'notes_T{t}.md').read_text(encoding='utf-8')
    brute_name = f'partial_T{t}.cpp' if t <= 2 else f'partial_brute_T{t}.cpp'
    mid_name = f'partial_mid_T{t}.cpp' if t <= 2 else f'partial_T{t}.cpp'
    brute = (root / brute_name).read_text(encoding='utf-8').rstrip()
    mid = (root / mid_name).read_text(encoding='utf-8').rstrip()
    std = (root / f'T{t}.cpp').read_text(encoding='utf-8').rstrip()
    brute_tag = '{{PARTIAL}}' if t <= 2 else '{{BRUTE}}'
    assert notes.count(brute_tag) == 1 and notes.count('{{MID}}') == 1 and notes.count('{{STD}}') == 1
    final = notes.replace(brute_tag, '```cpp\n' + brute + '\n```')
    final = final.replace('{{MID}}', '```cpp\n' + mid + '\n```')
    final = final.replace('{{STD}}', '```cpp\n' + std + '\n```')
    (built / f'T{t}' / 'solution.md').write_text(final, encoding='utf-8')
    (built / f'T{t}' / 'std.cpp').write_text(std + '\n', encoding='utf-8')
    all_parts.append(final.rstrip())
(built / 'solution.md').write_text('\n\n'.join(all_parts) + '\n', encoding='utf-8')
print('assembled solutions, C++ code copied exactly')
