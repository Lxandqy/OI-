from pathlib import Path
import subprocess,time,random
root=Path(__file__).parent
exe=root/'verified_bin/s7t2b0.exe'
std=root/'verified_bin/s7t2b1.exe'

cases={}
rng=random.Random(741)
a=list(range(-1000,1000));rng.shuffle(a)
a[0]=-1000000000;a[-1]=1000000000
cases['shuffle_unique']=a
rng=random.Random(842)
a=[]
for block in range(20):
    seq=[(x+block*17)%97-48 for x in range(100)]
    rng.shuffle(seq)
    a.extend(seq)
a[0]=-1000000000;a[-1]=1000000000
cases['shuffle_blocks']=a
a=[];x=1937
for i in range(2000):
    x=(x*1103515245+12345)&0x7fffffff
    a.append(x%2001-1000)
for j,seq in [(101,[-1000000000,800,0,900]),(1901,[-1000000000,700,-1,1000000000])]:
    a[j:j+4]=seq
cases['lcg_motifs']=a
for name,a in cases.items():
    body='2000\n'+' '.join(map(str,a))+'\n'
    times=[]
    for _ in range(3):
        start=time.perf_counter()
        p=subprocess.run([str(exe)],input=body.encode(),capture_output=True,check=True)
        times.append(round(time.perf_counter()-start,3))
    correct=subprocess.run([str(std)],input=body.encode(),capture_output=True,check=True).stdout.decode().strip()
    print(name,times,correct,flush=True)
    (root/f'trial_{name}.in').write_text(body,encoding='utf-8')
