from pathlib import Path
import re
root=Path(__file__).parent/'built'
bad=[]
patterns=[r'\bauto\b',r'\bdecltype\b',r'\bstd::function\b',r'\bstd::bind\b',r'\bclass\b',r'\[\s*&?\s*\]\s*\(',r'#define\s+int\s+long\s+long',r'\bsigned\s+main\s*\(',r'\bboost\b']
for p in root.glob('suite*_full/T*/solution.md'):
    for j,code in enumerate(re.findall(r'```cpp\n(.*?)\n```',p.read_text(encoding='utf-8'),re.S)):
        code=re.sub(r'//[^\n]*','',code)
        code=re.sub(r'/\*[\s\S]*?\*/','',code)
        code=re.sub(r'"(?:\\.|[^"\\])*"','""',code)
        for pat in patterns:
            if re.search(pat,code): bad.append((p.parent.parent.name,p.parent.name,j,pat))
print('BANNED',bad,'TOTAL',len(bad))
