from pathlib import Path

root = Path(__file__).parent
source = (root / 'partial_mid_T2.cpp').read_text(encoding='utf-8')
begin = source.index('\tacnt = -1;')
end = source.index('\tif(acnt == -1){', begin)
replace = '''\tacnt = -1;
\tfor(int mask = 0; mask < (1 << len); mask++){
\t\tccnt = 0;
\t\tfor(int i = 1; i <= fcnt; i++) candidate[++ccnt] = forced[i];
\t\tif(mask == 0){
\t\t\tint total = 0;
\t\t\tfor(int i = 1; i <= len; i++) total += sz[cyc[i]];
\t\t\tif(total == 3) consider();
\t\t\tcontinue;
\t\t}
\t\tint first = 0;
\t\tfor(int i = 1; i <= len; i++){
\t\t\tif(mask & (1 << (i - 1))){
\t\t\t\tfirst = i;
\t\t\t\tbreak;
\t\t\t}
\t\t}
\t\tint sum = 0;
\t\tbool good = true;
\t\tfor(int step = 1; step <= len; step++){
\t\t\tint j = (first + step - 1) % len + 1;
\t\t\tsum += sz[cyc[j]];
\t\t\tif(sum > 3){
\t\t\t\tgood = false;
\t\t\t\tbreak;
\t\t\t}
\t\t\tif(mask & (1 << (j - 1))){
\t\t\t\tif(sum != 3){
\t\t\t\t\tgood = false;
\t\t\t\t\tbreak;
\t\t\t\t}
\t\t\t\tcandidate[++ccnt] = ce[j];
\t\t\t\tsum = 0;
\t\t\t}
\t\t}
\t\tif(good && sum == 0) consider();
\t}
'''
assert len(source[begin:end]) > 100
(root / 'partial_subset_T2.cpp').write_text(source[:begin] + replace + source[end:], encoding='utf-8')
