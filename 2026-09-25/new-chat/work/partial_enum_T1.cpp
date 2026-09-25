#include<bits/stdc++.h>
using namespace std;

const int N = 35;
const long long NEG = -(1LL << 60);
struct Info{
	long long sum,pref,suf,best;
};
Info data[5][N][N];
int n,x[N],b[5];
long long answer = NEG;

Info emptyInfo(){
	Info z = {0,NEG,NEG,NEG};
	return z;
}

Info mergeInfo(Info a,Info c){
	if(a.best == NEG) return c;
	if(c.best == NEG) return a;
	Info z;
	z.sum = a.sum + c.sum;
	z.pref = max(a.pref,a.sum + c.pref);
	z.suf = max(c.suf,c.sum + a.suf);
	z.best = max(max(a.best,c.best),a.suf + c.pref);
	return z;
}

Info getInfo(int mask,int l,int r){
	if(l > r) return emptyInfo();
	return data[mask][l][r];
}

void dfs(int j,int start,Info cur){
	if(j == 5){
		Info all = mergeInfo(cur,getInfo(0,start,n));
		answer = max(answer,all.best);
		return;
	}
	for(int l = start; l <= n - (4 - j); l++){
		Info before = mergeInfo(cur,getInfo(0,start,l - 1));
		for(int r = l; r <= n - (4 - j); r++){
			Info now = mergeInfo(before,getInfo(j,l,r));
			dfs(j + 1,r + 1,now);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for(int j = 1; j <= 4; j++) cin >> b[j];
	for(int i = 1; i <= n; i++) cin >> x[i];
	for(int mask = 0; mask <= 4; mask++){
		for(int l = 1; l <= n; l++){
			long long sum = 0,bestEnd = NEG,best = NEG,pref = NEG;
			for(int r = l; r <= n; r++){
				long long v = x[r] ^ b[mask];
				sum += v;
				pref = max(pref,sum);
				bestEnd = max(v,bestEnd + v);
				best = max(best,bestEnd);
				Info z = {sum,pref,NEG,best};
				long long tail = 0;
				for(int i = r; i >= l; i--){
					tail += x[i] ^ b[mask];
					z.suf = max(z.suf,tail);
				}
				data[mask][l][r] = z;
			}
		}
	}
	dfs(1,1,emptyInfo());
	cout << answer << '\n';
	return 0;
}
