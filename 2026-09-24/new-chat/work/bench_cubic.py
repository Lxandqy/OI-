from pathlib import Path
import subprocess,time
base=Path(__file__).parent
exe=base/'verified_bin/s7t2b0.exe'
std=base/'verified_bin/s7t2b1.exe'
for point in [7,8,10]:
    inp=base/'built/suite7_full/T2/data'/f'{point}.in'
    for name,p in [('cubic',exe),('std',std)]:
        times=[]
        for _ in range(3):
            start=time.perf_counter()
            with inp.open('rb') as stream:
                subprocess.run([str(p)],stdin=stream,capture_output=True,check=True)
            times.append(round(time.perf_counter()-start,3))
        print(point,name,times,flush=True)
