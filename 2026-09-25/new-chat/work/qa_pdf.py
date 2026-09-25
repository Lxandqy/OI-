from pathlib import Path
from subprocess import run
from PIL import Image, ImageDraw

root = Path(__file__).parent
pdfs = [root / 'built' / 'solution.pdf'] + [root / 'built' / f'T{i}' / 'statement.pdf' for i in range(1, 5)]
qa = root / 'qa_pdf'
qa.mkdir(exist_ok=True)
poppler = r'C:\Users\Administrator\.cache\codex-runtimes\codex-primary-runtime\dependencies\native\poppler\Library\bin\pdftoppm.exe'

for pdf in pdfs:
    prefix = qa / ('solution' if pdf.name == 'solution.pdf' else pdf.parent.name)
    run([poppler, '-scale-to', '480', '-png', str(pdf), str(prefix)], check=True)

images = sorted(qa.glob('solution-*.png'))
images += [next(qa.glob(f'T{i}-*.png')) for i in range(1, 5)]
for start in range(0, len(images), 12):
    batch = images[start:start + 12]
    sheet = Image.new('RGB', (4 * 350, 3 * 515), 'white')
    draw = ImageDraw.Draw(sheet)
    for j, file in enumerate(batch):
        im = Image.open(file).convert('RGB')
        im.thumbnail((340, 480))
        x = (j % 4) * 350 + (350 - im.width) // 2
        y = (j // 4) * 515 + 25
        sheet.paste(im, (x, y))
        draw.text(((j % 4) * 350 + 5, (j // 4) * 515 + 5), file.stem, fill='black')
    name = qa / f'sheet_{start // 12 + 1}.png'
    sheet.save(name)
    print(name)
