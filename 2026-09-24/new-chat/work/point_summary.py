from pathlib import Path
import re
ROOT=Path(__file__).parent
for suite in range(4,8):
    for task in range(1,5):
        d=ROOT/f'source{suite}'/f'T{task}'/'judge/data'
        parts=[]
        for p in sorted(d.glob('*.in'),key=lambda x:int(x.stem)):
            s=p.read_text(encoding='utf-8').split()
            if (suite,task)==(7,1):
                desc=f'len={len(s[0])} distinct={len(set(s[0]))}'
            elif (suite,task)==(4,4):
                z=s[0]
                desc=f'len={len(z)} plus={z.count("+")} mult={z.count("*")}'
            elif (suite,task)==(4,3):
                desc=f'n={s[0]} colors={len(set(s[1]))}'
            elif (suite,task)==(5,1):
                desc='-'.join(s[:3])
            else:
                desc=' '.join(s[:min(4,len(s))])
            parts.append(f'{p.stem}:{desc}')
        print(f'S{suite} T{task} '+' | '.join(parts))
