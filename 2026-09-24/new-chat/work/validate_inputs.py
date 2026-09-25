from pathlib import Path
import re
from datetime import date

ROOT=Path(__file__).parent/'built'

def check(s,t,path):
    data=path.read_text(encoding='utf-8').split()
    values=list(map(int,data)) if (s,t) not in [(4,3),(4,4),(6,4),(7,1),(7,3)] else None
    if (s,t)==(4,1):
        n=values[0]; assert 1<=n<=100000 and len(values)==n+1
        assert all(1<=x<=100000 for x in values[1:])
    elif (s,t)==(4,2):
        n,k=values[:2]; a=values[2:]; assert 2<=n<=200000 and 1<=k<=10**9 and len(a)==n
        assert all(1<=x<=10**9 for x in a)
        counts={}
        for x in a:
            r=x*x%k; counts[r]=counts.get(r,0)+1
        assert any(counts.get((-r)%k,0)>(r==(-r)%k) for r in counts)
    elif (s,t)==(4,3):
        n=int(data[0]); st=data[1]; assert len(data)==2 and 2<=n<=10**6 and len(st)==n and set(st)<={'r','g','b'}
    elif (s,t)==(4,4):
        st=data[0]; assert len(data)==1 and 1<=len(st)<=5000
        assert re.fullmatch(r'[1-9][0-9]*(?:[+*][1-9][0-9]*)*',st)
    elif (s,t)==(5,1):
        y,m,d=values; assert 2000<=y<=7000; date(y,m,d)
    elif (s,t)==(5,2):
        n,m,k=values[:3]; assert 1<=n<=1000 and 1<=m,k<=3000 and len(values)==3+2*n
        assert all(1<=values[i]<=100000 for i in range(3,len(values)))
    elif (s,t)==(5,3):
        q=values[0]; assert 1<=q<=10 and len(values)==1+2*q
        pairs=list(zip(values[1::2],values[2::2])); assert sum(r for l,r in pairs)<=200000
        assert all(1<=l<r<=100000 for l,r in pairs)
    elif (s,t)==(5,4):
        n,m,k=values[:3]; assert 2<=n,m<=1000 and 1<=k<=min(n*m-2,1000) and len(values)==7+2*k
        points=list(zip(values[3::2],values[4::2])); assert len(points)==k+2 and len(set(points))==len(points)
        assert all(0<=x<n and 0<=y<m for x,y in points)
    elif (s,t)==(6,1):
        n,k=values[:2]; assert 1<=n<=10000 and 1<=k<=100000 and len(values)==n+2
        assert all(1<=x<=10**7 for x in values[2:])
    elif (s,t)==(6,2):
        n,x=values[:2]; assert 1<=n<=100000 and 1<=x<=min(n,10) and len(values)==2+n+x
        assert all(-10**8<=v<=10**8 for v in values[2:])
    elif (s,t)==(6,3):
        n=values[0]; assert 1<=n<=100000 and len(values)==1+3*n
        assert all(1<=v<=10**9 for v in values[1:])
    elif (s,t)==(6,4):
        n,k=map(int,data[:2]); assert 1<=n,k<=400 and len(data)==n+2
        assert all(re.fullmatch(r'[1-9][0-9]*',x) and 1<=int(x)<=10**18 for x in data[2:])
    elif (s,t)==(7,1):
        assert len(data)==1 and 1<=len(data[0])<=10**6 and re.fullmatch('[a-z]+',data[0])
    elif (s,t)==(7,2):
        n=values[0]; assert 4<=n<=2000 and len(values)==n+1
        assert all(-10**9<=x<=10**9 for x in values[1:])
    elif (s,t)==(7,3):
        q=int(data[0]); assert 1<=q<=100
        p=1
        for z in range(q):
            n=int(data[p]); p+=1; assert 1<=n<=10
            edges=[(data[p+2*i],data[p+2*i+1]) for i in range(n)]; p+=2*n
            assert len(edges)==len(set(edges))
            parent={}
            for a,b in edges:
                assert a!=b
                assert 1<=len(a)<=20 and 1<=len(b)<=20
                assert re.fullmatch(r'[A-Za-z0-9.()\-]+',a) and re.fullmatch(r'[A-Za-z0-9.()\-]+',b)
                assert b not in parent or parent[b]==a
                parent[b]=a
        assert p==len(data)
    elif (s,t)==(7,4):
        q=values[0]; assert 1<=q<=10
        p=1
        for z in range(q):
            n=values[p]; p+=1; assert 2<=n<=100000
            parent=list(range(n+1))
            def find(x):
                while parent[x]!=x:
                    parent[x]=parent[parent[x]]; x=parent[x]
                return x
            for i in range(n-1):
                a,b=values[p:p+2]; p+=2
                assert 1<=a<=n and 1<=b<=n and a!=b
                fa,fb=find(a),find(b); assert fa!=fb; parent[fa]=fb
        assert p==len(values)

issues=[]
for s in range(4,8):
    for t in range(1,5):
        base=ROOT/f'suite{s}_full'/f'T{t}'
        for p in list((base/'data').glob('*.in')):
            try: check(s,t,p)
            except Exception as e: issues.append((s,t,p.name,str(e)))
        print(f's{s}t{t} checked {len(list((base/"data").glob("*.in")))}')
print('ISSUES',issues[:30],'TOTAL',len(issues))
