from pathlib import Path
from hashlib import sha256
from zipfile import ZipFile, ZIP_DEFLATED
from tempfile import mkdtemp
import shutil
import re
import subprocess
from pypdf import PdfReader
from source_map import SOURCES

root = Path(__file__).parent
built = root / 'built'
output = root.parent / 'outputs'
output.mkdir(parents=True, exist_ok=True)


def digest(data):
    return sha256(data).hexdigest()


for t in range(1, 5):
    folder = built / f'T{t}'
    solution = (folder / 'solution.md').read_text(encoding='utf-8')
    blocks = re.findall(r'```cpp\n(.*?)\n```', solution, re.S)
    assert len(blocks) == len(SOURCES[t]), (t, len(blocks))
    for block, (_, filename) in zip(blocks, SOURCES[t]):
        assert block + '\n' == (root / filename).read_text(encoding='utf-8')
    assert blocks[-1] + '\n' == (folder / 'std.cpp').read_text(encoding='utf-8')
    assert '{{' not in solution
    statement = (folder / 'statement.md').read_text(encoding='utf-8')
    found = re.findall(r'```text\n(.*?)\n```', statement, re.S)
    assert len(found) == 2, (t, 'sample blocks', len(found))
    sample_in, sample_out = found
    got = subprocess.check_output([str(root / f'T{t}.exe')], input=sample_in + '\n', text=True)
    assert got.split() == sample_out.split(), (t, got, sample_out)
    assert len(PdfReader(folder / 'statement.pdf').pages) == 1
    for label, source in [('data', folder / 'data'), ('attachment', folder / 'attachment_source')]:
        target = folder / ('data.zip' if label == 'data' else 'attachment.zip')
        members = sorted(source.glob('*'))
        assert len(members) == (40 if label == 'data' else 2)
        with ZipFile(target, 'w', ZIP_DEFLATED, compresslevel=8) as z:
            for item in members:
                z.write(item, item.name)
        with ZipFile(target) as z:
            assert z.testzip() is None
            assert set(z.namelist()) == {x.name for x in members}
            for item in members:
                assert z.read(item.name) == item.read_bytes()
    print('T', t, 'sample/code/PDF/inner ZIP exact', flush=True)

parts = [(built / f'T{t}' / 'solution.md').read_text(encoding='utf-8').rstrip() for t in range(1, 5)]
assert (built / 'solution.md').read_text(encoding='utf-8') == '\n\n'.join(parts) + '\n'
assert len(PdfReader(built / '题目汇总.pdf').pages) == 4
assert len(PdfReader(built / 'solution.pdf').pages) >= 4

stage_full = Path(mkdtemp(prefix='full_', dir=root))
stage_player = Path(mkdtemp(prefix='player_', dir=root))
for t in range(1, 5):
    src = built / f'T{t}'
    dst = stage_full / f'T{t}'
    dst.mkdir()
    for name in ('statement.md','statement.pdf','std.cpp','solution.md','data.zip','attachment.zip'):
        shutil.copy2(src / name, dst / name)
    shutil.copytree(src / 'data', dst / 'data')
    pub = stage_player / f'T{t}'
    pub.mkdir()
    for name in ('statement.md','statement.pdf','attachment.zip'):
        shutil.copy2(src / name, pub / name)
for name in ('solution.md','solution.pdf','题目汇总.pdf'):
    shutil.copy2(built / name, stage_full / name)
shutil.copy2(built / '题目汇总.pdf', stage_player / '题目汇总.pdf')

for t in range(1, 5):
    names = sorted(x.name for x in (stage_full / f'T{t}').iterdir())
    assert names == sorted(['statement.md','statement.pdf','std.cpp','solution.md','data','data.zip','attachment.zip'])
    names_pub = sorted(x.name for x in (stage_player / f'T{t}').iterdir())
    assert names_pub == sorted(['statement.md','statement.pdf','attachment.zip'])


def outer(stage, target):
    with ZipFile(target, 'w', ZIP_DEFLATED, compresslevel=8) as z:
        for item in sorted(stage.rglob('*')):
            if item.is_file():
                z.write(item, item.relative_to(stage).as_posix())
    with ZipFile(target) as z:
        assert z.testzip() is None
        names = z.namelist()
        assert len(names) == len(set(names))
        assert all(not x.startswith('/') and '..' not in Path(x).parts for x in names)
        assert not any(x.endswith('.zip') and x.count('/') > 1 for x in names)
    return digest(target.read_bytes())


full_zip = output / '四题新编_完整重构包.zip'
player_zip = output / '四题新编_选手下发包.zip'
full_hash = outer(stage_full, full_zip)
player_hash = outer(stage_player, player_zip)
with ZipFile(full_zip) as full, ZipFile(player_zip) as player:
    player_names = set(player.namelist())
    assert len(player_names) == 13
    assert all(name in full.namelist() and full.read(name) == player.read(name) for name in player_names)
    assert all('/data/' not in name and 'solution' not in name and 'std.cpp' not in name for name in player_names)
    for t in range(1, 5):
        with ZipFile(stage_player / f'T{t}' / 'attachment.zip') as nested:
            assert set(nested.namelist()) == {'attachment1.in','attachment1.out'}
            assert nested.testzip() is None

manifest = f'''完整包：{full_zip.name}\nSHA-256：{full_hash}\n选手包：{player_zip.name}\nSHA-256：{player_hash}\n'''
(output / 'SHA256.txt').write_text(manifest, encoding='utf-8')
print(manifest, flush=True)
print('release whitelist and public-file identity PASS', flush=True)
