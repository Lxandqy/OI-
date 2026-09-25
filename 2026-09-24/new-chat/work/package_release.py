from pathlib import Path
import hashlib
import shutil
import zipfile
import sys

ROOT=Path(__file__).parent.resolve()
BUILT=ROOT/'built'
OUT=ROOT.parent/'outputs'
OUT.mkdir(exist_ok=True)
LABEL={4:'第四套',5:'第五套',6:'第六套',7:'第七套'}

def digest(data): return hashlib.sha256(data).hexdigest()

def zip_tree(source,target):
    with zipfile.ZipFile(target,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=6) as z:
        for p in sorted(source.rglob('*')):
            if p.is_file(): z.write(p,p.relative_to(source).as_posix())

def safe_clear(path):
    p=path.resolve()
    if p.parent!=ROOT or not p.name.startswith('player_suite'):
        raise ValueError(f'unsafe stage: {p}')
    if p.exists(): shutil.rmtree(p)

suites=[int(sys.argv[1])] if len(sys.argv)==2 else range(4,8)
for s in suites:
    full=BUILT/f'suite{s}_full'
    player=ROOT/f'player_suite{s}'
    safe_clear(player)
    player.mkdir()
    assert set(x.name for x in full.iterdir())=={'T1','T2','T3','T4','solution.md','solution.pdf','题目汇总.pdf'}
    shutil.copy2(full/'题目汇总.pdf',player/'题目汇总.pdf')
    for t in range(1,5):
        task=full/f'T{t}'
        assert set(x.name for x in task.iterdir())=={'statement.md','statement.pdf','std.cpp','solution.md','data','data.zip','attachment.zip'}
        target=player/f'T{t}';target.mkdir()
        for name in ['statement.md','statement.pdf','attachment.zip']:
            shutil.copy2(task/name,target/name)
        assert set(x.name for x in target.iterdir())=={'statement.md','statement.pdf','attachment.zip'}
        for name in ['statement.md','statement.pdf','attachment.zip']:
            assert (task/name).read_bytes()==(target/name).read_bytes()
        files=list((task/'data').iterdir())
        assert len(files) in (20,40)
        expected={p.name for p in files}
        with zipfile.ZipFile(task/'data.zip') as z:
            assert z.testzip() is None
            assert set(z.namelist())==expected and len(z.namelist())==len(expected)
            for name in expected: assert z.read(name)==(task/'data'/name).read_bytes()
        with zipfile.ZipFile(task/'attachment.zip') as z:
            assert z.testzip() is None
            assert sorted(z.namelist())==['attachment1.in','attachment1.out','attachment2.in','attachment2.out']
            assert all('/' not in name and not name.endswith('.zip') for name in z.namelist())
    assert (full/'题目汇总.pdf').read_bytes()==(player/'题目汇总.pdf').read_bytes()
    complete_zip=OUT/f'{LABEL[s]}_V3.8_完整重构包.zip'
    player_zip=OUT/f'{LABEL[s]}_V3.8_选手下发包.zip'
    zip_tree(full,complete_zip)
    zip_tree(player,player_zip)
    with zipfile.ZipFile(complete_zip) as z:
        assert z.testzip() is None
        complete_names=set(z.namelist())
        assert not any(name.endswith('.zip') and not (name.endswith('/data.zip') or name.endswith('/attachment.zip')) for name in complete_names)
        for name in complete_names:
            assert not name.startswith('/') and '..' not in Path(name).parts
    with zipfile.ZipFile(player_zip) as z:
        assert z.testzip() is None
        names=set(z.namelist())
        expected={'题目汇总.pdf'}
        for t in range(1,5):
            expected|={f'T{t}/statement.md',f'T{t}/statement.pdf',f'T{t}/attachment.zip'}
        assert names==expected
        assert not any(x in name for name in names for x in ('solution','std.cpp','data.zip','/data/'))
        with zipfile.ZipFile(complete_zip) as fullzip:
            for name in names: assert z.read(name)==fullzip.read(name)
    print(f'{complete_zip.name} SHA256 {digest(complete_zip.read_bytes())} bytes={complete_zip.stat().st_size}',flush=True)
    print(f'{player_zip.name} SHA256 {digest(player_zip.read_bytes())} bytes={player_zip.stat().st_size}',flush=True)
