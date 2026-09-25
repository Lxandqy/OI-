from pathlib import Path
import subprocess
from PIL import Image,ImageDraw,ImageFont
from pypdf import PdfReader

ROOT=Path(__file__).parent
BUILT=ROOT/'built'
STAGE=ROOT/'pdf_stage'/'contact_pages'
POP=Path('C:/Users/Administrator/.cache/codex-runtimes/codex-primary-runtime/dependencies/native/poppler/Library/bin/pdftoppm.exe')
STAGE.mkdir(parents=True,exist_ok=True)
font=ImageFont.truetype('C:/Windows/Fonts/arial.ttf',15)

for suite in range(4,8):
    base=BUILT/f'suite{suite}_full'
    pdfs=[base/f'T{t}'/'statement.pdf' for t in range(1,5)]
    pdfs.extend([base/'题目汇总.pdf',base/'solution.pdf'])
    pages=[]
    for pdf in pdfs:
        count=len(PdfReader(pdf).pages)
        prefix=STAGE/f's{suite}_{pdf.parent.name}_{pdf.stem}'
        subprocess.run([str(POP),'-jpeg','-scale-to','650',str(pdf),str(prefix)],check=True,capture_output=True)
        for j in range(1,count+1):
            page_number=str(j).zfill(len(str(count)))
            img=Image.open(f'{prefix}-{page_number}.jpg').convert('RGB')
            pages.append((f'{pdf.parent.name}/{pdf.name} p{j}',img))
    width=4*260
    row_height=400
    rows=(len(pages)+3)//4
    sheet=Image.new('RGB',(width,rows*row_height),(232,236,240))
    draw=ImageDraw.Draw(sheet)
    for i,(label,img) in enumerate(pages):
        x=(i%4)*260+13
        y=(i//4)*row_height+30
        img.thumbnail((234,335))
        sheet.paste(img,(x,y))
        draw.text((x,y-20),label,fill=(10,24,40),font=font)
    out=ROOT/'pdf_stage'/f'suite{suite}_contact.jpg'
    sheet.save(out,quality=86)
    print(f'suite{suite} {len(pages)} pages {out}',flush=True)
