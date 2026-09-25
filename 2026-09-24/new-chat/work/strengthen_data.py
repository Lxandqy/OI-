from pathlib import Path
import subprocess
import zipfile
import random

ROOT=Path(__file__).parent
BUILT=ROOT/'built'
GPP=Path('D:/Dev-Cpp/MinGW64/bin/g++.exe')

def write_case(s,t,point,body):
    base=BUILT/f'suite{s}_full'/f'T{t}'
    inp=base/'data'/f'{point}.in'
    out=base/'data'/f'{point}.out'
    inp.write_text(body,encoding='utf-8',newline='\n')
    exe=ROOT/'bin'/f'harden_s{s}t{t}.exe'
    if not exe.exists():
        subprocess.run([str(GPP),'-std=c++14','-O2',str(base/'std.cpp'),'-o',str(exe)],check=True)
    with inp.open('rb') as stream:
        p=subprocess.run([str(exe)],stdin=stream,capture_output=True,check=True,timeout=20)
    out.write_bytes(p.stdout)
    print(f'hardened s{s}t{t} point{point} answer={p.stdout.decode().strip()}',flush=True)

# 在各公开子域内让容量限制真实起作用；参数式构造覆盖不同规模、
# 小容量、k=1、正负单件收益和不同权重分布。
cases={
    3:(200,100,50,lambda i:1+i%4,lambda i:1+i*29%100),
    4:(1000,300,3000,lambda i:1+i%7,lambda i:2600+i*37%701),
    5:(999,299,1000,lambda i:1+(i*i+3*i)%9,lambda i:700+i*53%601),
    6:(100,301,100,lambda i:1+i%9,lambda i:1+i*131%300),
    7:(500,1500,500,lambda i:1+i*3%11,lambda i:350+i*17%301),
    8:(1000,3000,3000,lambda i:1+i*7%11,lambda i:2820+i*37%401),
    9:(1000,2999,1,lambda i:1+i*7%13,lambda i:1+i*997%10000),
    10:(999,3000,1500,lambda i:1+i*i%17,lambda i:1320+i*47%401),
}
for point,(n,m,k,weight,value) in cases.items():
    lines=[f'{n} {m} {k}']
    for i in range(1,n+1): lines.append(f'{weight(i)} {value(i)}')
    write_case(5,2,point,'\n'.join(lines)+'\n')

# 在最大位数、最大商品数和接近最大模数下保留多样的尾部数字。
lines=['400 389']
for i in range(1,401):
    value=900000000000000000+(i*71123456789123)%99999999999999999
    lines.append(str(value))
write_case(6,4,7,'\n'.join(lines)+'\n')
lines=['400 381']
for i in range(400):
    value=100000000000000000 if i%2==0 else 200000000000000000
    lines.append(str(value))
write_case(6,4,8,'\n'.join(lines)+'\n')

# 大规模交错序列使三重计数的内层条件经常成立；三种构造
# 分别核对首尾极值、重复值、分块与局部陷阱。
rng=random.Random(741)
a=list(range(-1000,1000))
rng.shuffle(a)
a[0]=-1000000000
a[-1]=1000000000
assert len(set(a))==2000 and a[0]<min(a[1:]) and a[-1]>max(a[:-1])
write_case(7,2,7,'2000\n'+' '.join(map(str,a))+'\n')
rng=random.Random(842)
a=[]
for block in range(20):
    seq=[(x+block*17)%97-48 for x in range(100)]
    rng.shuffle(seq)
    a.extend(seq)
a[0]=-1000000000
a[-1]=1000000000
assert len(set(a))<200 and a[0]<min(a[1:]) and a[-1]>max(a[:-1])
write_case(7,2,8,'2000\n'+' '.join(map(str,a))+'\n')
a=[]
x=1937
for i in range(2000):
    x=(x*1103515245+12345)&0x7fffffff
    a.append(x%2001-1000)
for j,seq in [(101,[-1000000000,800,0,900]),(1901,[-1000000000,700,-1,1000000000])]:
    a[j:j+4]=seq
assert a[101]==-1000000000 and a[1904]==1000000000 and len(set(a))>1000
write_case(7,2,10,'2000\n'+' '.join(map(str,a))+'\n')

for s,t in [(5,2),(6,4),(7,2)]:
    base=BUILT/f'suite{s}_full'/f'T{t}'
    files=sorted((base/'data').iterdir(),key=lambda p:(int(p.stem),p.suffix))
    with zipfile.ZipFile(base/'data.zip','w',compression=zipfile.ZIP_DEFLATED,compresslevel=6) as z:
        for p in files: z.write(p,p.name)
