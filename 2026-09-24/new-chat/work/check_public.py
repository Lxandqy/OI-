from pathlib import Path
import hashlib
import re
import subprocess
import zipfile

ROOT=Path(__file__).parent
BUILT=ROOT/'built'
errors=[]

for s in range(4,8):
    for t in range(1,5):
        source=ROOT/f'source{s}'/f'T{t}'
        base=BUILT/f'suite{s}_full'/f'T{t}'
        samples=sorted((source/'release/sample').glob('*.in'))
        attachments=sorted((source/'release/attachment').glob('*.in'))
        formal=sorted((base/'data').glob('*.in'))
        seen={}
        for category,files in [('sample',samples),('attachment',attachments),('formal',formal)]:
            for p in files:
                digest=hashlib.sha256(p.read_bytes().strip()).hexdigest()
                if digest in seen and category!=seen[digest][0]:
                    errors.append((s,t,'input duplicate',seen[digest],(category,p.name)))
                else: seen[digest]=(category,p.name)
        md=(base/'statement.md').read_text(encoding='utf-8')
        for p in samples:
            content=p.read_text(encoding='utf-8').strip()
            if content not in md: errors.append((s,t,'sample not in statement',p.name))
        exe=ROOT/'verified_bin'/f's{s}t{t}b{len(re.findall(r"```cpp\n",(base/"solution.md").read_text(encoding="utf-8")))-1}.exe'
        if not exe.exists(): continue
        for p in samples:
            if (s,t) in [(4,4),(5,4)]:
                io='eval' if (s,t)==(4,4) else 'green'
                scratch=ROOT/'sample_io';scratch.mkdir(exist_ok=True)
                (scratch/f'{io}.in').write_bytes(p.read_bytes())
                subprocess.run([str(exe)],cwd=scratch,capture_output=True,check=True,timeout=10)
                got=(scratch/f'{io}.out').read_text().split()
            else:
                with p.open('rb') as stream:
                    got=subprocess.run([str(exe)],stdin=stream,capture_output=True,check=True,timeout=10).stdout.decode().split()
            want=p.with_suffix('.out').read_text(encoding='utf-8').split()
            if got!=want: errors.append((s,t,'sample WA',p.name,want,got))
        with zipfile.ZipFile(base/'attachment.zip') as z:
            for p in (source/'release/attachment').iterdir():
                if z.read(p.name)!=p.read_bytes(): errors.append((s,t,'attachment changed',p.name))
        print(f'S{s}T{t} samples={len(samples)} attachment_pairs={len(attachments)} formal={len(formal)}',flush=True)

print('ERRORS',errors[:30],'TOTAL',len(errors))
