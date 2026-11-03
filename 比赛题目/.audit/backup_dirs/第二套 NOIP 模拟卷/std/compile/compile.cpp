#include<bits/stdc++.h>
using namespace std;

const int N = 60000 + 10;
const int K = 1200 + 10;
const long long INF = 4e18;
int n,k,a[N],id[K],type[K];
long long cold[K],hot[K],f[K][K],mn[K],g[K];

int main(){
	freopen("compile.in","r",stdin);
	freopen("compile.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		cin >> n >> k;
		for(int i = 1; i <= k; i++) id[i] = 0;
		int c = 0;
		for(int i = 1; i <= n; i++){
			int x;
			cin >> x;
			if(id[x] == 0){
				c++;
				id[x] = c;
				type[c] = x;
			}
			a[i] = id[x];
		}
		for(int i = 1; i <= k; i++) cin >> cold[i];
		for(int i = 1; i <= k; i++) cin >> hot[i];
		for(int j = 0; j <= c; j++){
			mn[j] = INF;
			for(int l = 0; l <= c; l++) f[j][l] = INF;
		}
		f[0][0] = 0;
		mn[0] = 0;
		a[0] = 0;
		long long add = 0;
		for(int i = 1; i <= n; i++){
			int x = a[i],p = a[i - 1],z = type[x];
			long long cost = cold[z];
			if(x == p) cost = hot[z];
			for(int j = 0; j <= c; j++){
				g[j] = INF;
				if(mn[j] == INF) continue;
				long long best = mn[j] + cold[z];
				if(f[x][j] != INF) best = min(best,f[x][j] + hot[z]);
				g[j] = best - cost;
			}
			for(int j = 0; j <= c; j++){
				long long best = min(f[p][j],g[j]);
				f[p][j] = best;
				f[j][p] = best;
				mn[j] = min(mn[j],best);
				mn[p] = min(mn[p],best);
			}
			add += cost;
		}
		long long ans = INF;
		for(int j = 0; j <= c; j++) ans = min(ans,mn[j]);
		cout << add + ans << '\n';
	}
	return 0;
}
