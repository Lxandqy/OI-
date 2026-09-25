from pathlib import Path
from pypdf import PdfReader

ROOT=Path(__file__).parent/'built'
problems={4:['接龙','平方和','彩彩的三彩项链','表达式'],5:['上下五千年','采购','整除序列','绿野仙踪'],6:['最多求余','各乘一个','三元组','切割'],7:['回文串','交错四元组','文件判定','树与叶子']}
errors=[]
for s in range(4,8):
    base=ROOT/f'suite{s}_full'
    pdfs=[base/f'T{t}'/'statement.pdf' for t in range(1,5)] + [base/'题目汇总.pdf',base/'solution.pdf']
    for p in pdfs:
        reader=PdfReader(p)
        texts=[page.extract_text() or '' for page in reader.pages]
        for page in reader.pages:
            w=float(page.mediabox.width);h=float(page.mediabox.height)
            if not (590<w<600 and 838<h<846): errors.append((s,p.name,'not A4',w,h))
        if any(len(x.strip())<30 for x in texts): errors.append((s,p.name,'near blank page',[i+1 for i,x in enumerate(texts) if len(x.strip())<30]))
        joined='\n'.join(texts)
        if 'flowchart TB' in joined or 'classDef invalid' in joined: errors.append((s,p.name,'mermaid source leaked'))
        if p.name=='solution.pdf':
            for t,name in enumerate(problems[s],1):
                hits=[i+1 for i,x in enumerate(texts) if f'T{t} {name}' in x]
                if len(hits)!=1: errors.append((s,'solution title',name,hits))
            for i,x in enumerate(texts):
                if '左上角图例' in x and '叶子' not in x: errors.append((s,'diagram split',i+1))
        if p.name=='statement.pdf':
            if 'attachment.zip' not in joined: errors.append((s,p.parent.name,'attachment missing'))
        print(f's{s} {p.parent.name}/{p.name} pages={len(texts)} chars={sum(map(len,texts))}',flush=True)
print('PDF_ERRORS',errors,'TOTAL',len(errors))
