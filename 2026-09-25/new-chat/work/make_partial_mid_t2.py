from pathlib import Path

p = Path(__file__).parent
s = (p / 'T2.cpp').read_text(encoding='utf-8')
s = s.replace('int cyc[N],ce[N],residue[N],forced[N],fcnt;\nbool alive[N],mark[N];',
              'int cyc[N],ce[N],forced[N],fcnt;\nbool alive[N];')
start = s.index('\tint prefix = 0;')
end = s.index('\tif(acnt == -1){', start)
replacement = '''\tfor(int cut = 1; cut <= len; cut++){
\t\tccnt = 0;
\t\tfor(int j = 1; j <= fcnt; j++) candidate[++ccnt] = forced[j];
\t\tint sum = 0;
\t\tbool good = true;
\t\tfor(int step = 1; step <= len; step++){
\t\t\tint j = (cut + step - 1) % len + 1;
\t\t\tsum += sz[cyc[j]];
\t\t\tif(sum > 3){
\t\t\t\tgood = false;
\t\t\t\tbreak;
\t\t\t}
\t\t\tif(sum == 3){
\t\t\t\tcandidate[++ccnt] = ce[j];
\t\t\t\tsum = 0;
\t\t\t}
\t\t}
\t\tif(good && sum == 0) consider();
\t}
'''
s = s[:start] + replacement + s[end:]
(p / 'partial_mid_T2.cpp').write_text(s, encoding='utf-8')
