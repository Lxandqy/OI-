from pathlib import Path
import subprocess
root=Path(__file__).parent
exe=root/'bin/harden_s6t4.exe'
types=[10**17,2*10**17,3*10**17,4*10**17]
for k in range(380,401):
    for p in [2,3,4]:
        vals=[types[i%p] for i in range(400)]
        total=sum(vals)
        if total%k==0: continue
        if any((total+int(str(x)[:j])+int(str(x)[j:])-x)%k==0 for x in types[:p] for j in range(1,18)): continue
        body=f'400 {k}\n'+'\n'.join(map(str,vals))+'\n'
        out=subprocess.run([str(exe)],input=body.encode(),capture_output=True,timeout=5,check=True).stdout.decode().strip()
        print(k,p,out,flush=True)
        if out not in ('-1','0','1'):
            (root/'cut_hard.in').write_text(body,encoding='utf-8')
            raise SystemExit
