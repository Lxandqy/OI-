from pathlib import Path

root = Path(__file__).parent
source = (root / 'partial_mid_T2.cpp').read_text(encoding='utf-8')
old = 'for(int cut = 1; cut <= len; cut++)'
assert source.count(old) == 1
source = source.replace(old, 'for(int cut = 1; cut <= min(len,3); cut++)')
(root / 'partial_pattern_T2.cpp').write_text(source, encoding='utf-8')
