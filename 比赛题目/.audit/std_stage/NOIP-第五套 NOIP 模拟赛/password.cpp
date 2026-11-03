#include<bits/stdc++.h>
using namespace std;
const int N = 5010,MOD = 998244353;
int n,m,k,a[N],p[N],pos[N],pre[N],l[N],r[N];
long long f[N],g[N];
int main(){
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		p[i] = a[i];
	}
	long long total = 1;
	for(int i = 1; i <= m; i++){
		cin >> l[i] >> r[i];
		total = total * (r[i] - l[i] + 1) % MOD;
	}
	sort(p + 1,p + n + 1);
	int d = unique(p + 1,p + n + 1) - p - 1;
	for(int i = 1; i <= d; i++) pos[i] = 0;
	for(int i = 1; i <= n; i++){
		int x = lower_bound(p + 1,p + d + 1,a[i]) - p;
		pre[i] = pos[x];
		pos[x] = i;
	}
	for(int i = 0; i <= n; i++) f[i] = 1;
	for(int t = 1; t <= m; t++){
		g[0] = 0;
		for(int i = 1; i <= n; i++){
			g[i] = g[i - 1];
			if(l[t] <= a[i] && a[i] <= r[t]){
				long long value = f[i - 1];
				if(pre[i] > 0) value -= f[pre[i] - 1];
				g[i] = (g[i] + value + MOD) % MOD;
			}
		}
		for(int i = 0; i <= n; i++) f[i] = g[i];
	}
	cout << (total - f[n] + MOD) % MOD << '\n';
	return 0;
}
