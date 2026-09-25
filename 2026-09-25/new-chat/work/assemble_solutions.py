from pathlib import Path
from source_map import SOURCES

root = Path(__file__).parent
built = root / 'built'
all_parts = []
for t in range(1, 5):
    notes = (root / f'notes_T{t}.md').read_text(encoding='utf-8')
    std = (root / f'T{t}.cpp').read_text(encoding='utf-8').rstrip()
    final = notes
    for tag, filename in SOURCES[t]:
        marker = '{{' + tag + '}}'
        assert final.count(marker) == 1, (t, marker)
        source = (root / filename).read_text(encoding='utf-8').rstrip()
        final = final.replace(marker, '```cpp\n' + source + '\n```')
    assert '{{' not in final
    (built / f'T{t}' / 'solution.md').write_text(final, encoding='utf-8')
    (built / f'T{t}' / 'std.cpp').write_text(std + '\n', encoding='utf-8')
    all_parts.append(final.rstrip())
(built / 'solution.md').write_text('\n\n'.join(all_parts) + '\n', encoding='utf-8')
print('assembled solutions, C++ code copied exactly')
