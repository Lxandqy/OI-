from pathlib import Path

p = Path(__file__).parent
s = (p / 'T3.cpp').read_text(encoding='utf-8')
s = s.replace('const int M = 6000005;\nint trie[M][2],cnt[M],nodes = 1;\n', '')
start = s.index('void insertValue(')
end = s.index('int findRoot(', start)
s = s[:start] + s[end:]
s = s.replace('\t\tinsertValue(a[i],i);\n', '')
s = s.replace('\t\tf[i] = nearest(a[i]);\n',
'''\t\tint best = -1;
\t\tfor(int j = 1; j <= n; j++){
\t\t\tif(i == j) continue;
\t\t\tif(best == -1 || (a[i] ^ a[j]) < (a[i] ^ a[best])) best = j;
\t\t}
\t\tf[i] = best;
''')
(p / 'partial_T3.cpp').write_text(s, encoding='utf-8')
