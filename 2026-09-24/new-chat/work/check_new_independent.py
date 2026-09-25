from pathlib import Path
import subprocess

ROOT=Path(__file__).parent
BUILT=ROOT/'built'

for point in range(3,11):
    inp=BUILT/'suite5_full/T2/data'/f'{point}.in'
    vals=list(map(int,inp.read_text().split()))
    n,m,k=vals[:3]
    dp=[0]*(m+1)
    for i in range(n):
        w,v=vals[3+2*i:5+2*i]
        next_dp=dp[:]
        for c in range(m-w+1):
            gain=dp[c]+v-k
            if gain>next_dp[c+w]: next_dp[c+w]=gain
        dp=next_dp
    result=max(dp)
    want=int(inp.with_suffix('.out').read_text())
    assert result==want,(point,result,want)
    print('knapsack',point,result,flush=True)

exe=ROOT/'verified_bin/s7t2b0.exe'
for point in [7,8,10]:
    inp=BUILT/'suite7_full/T2/data'/f'{point}.in'
    with inp.open('rb') as stream:
        result=subprocess.run([str(exe)],stdin=stream,capture_output=True,check=True,timeout=10).stdout.decode().strip()
    want=inp.with_suffix('.out').read_text().strip()
    assert result==want,(point,result,want)
    print('quadruple cubic',point,result,flush=True)

for point in [7,8]:
    inp=BUILT/'suite6_full/T4/data'/f'{point}.in'
    parts=list(map(int,inp.read_text().split()))
    n,k=parts[:2]
    INF=10**9
    global_dp=[INF]*k
    global_dp[0]=0
    cache={}
    for number in parts[2:]:
        if number not in cache:
            s=str(number)
            length=len(s)
            local=[[INF]*k for _ in range(length+1)]
            local[0][0]=0
            for pos in range(length):
                value=0
                for end in range(pos+1,length+1):
                    value=(value*10+ord(s[end-1])-48)%k
                    cost=int(end<length)
                    target=local[end]
                    for rem,prior in enumerate(local[pos]):
                        if prior<INF:
                            new_rem=(rem+value)%k
                            if prior+cost<target[new_rem]: target[new_rem]=prior+cost
            cache[number]=[(r,c) for r,c in enumerate(local[length]) if c<INF]
        next_dp=[INF]*k
        for r,c in enumerate(global_dp):
            if c>=INF: continue
            for add,cut in cache[number]:
                nr=(r+add)%k
                if c+cut<next_dp[nr]: next_dp[nr]=c+cut
        global_dp=next_dp
    result=-1 if global_dp[0]>=INF else global_dp[0]
    want=int(inp.with_suffix('.out').read_text())
    assert result==want,(point,result,want)
    print('cut factorized',point,result,flush=True)
