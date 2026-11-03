#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const long long MOD = 998244353;
int n,fa[N],ord[N];
vector<int> e[N];
long long a[N],f[N],g[N],upf[N],upg[N];
long long ansf[N],ansg[N],way[N],pre[N];
long long addWays(long long x,long long c){
	if(x > 0) return c;
	if(x < 0) return 1;
	return (c + 1) % MOD;
}
int main(){
	freopen("region.in","r",stdin);
	freopen("region.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	// ord 中父亲先于孩子；逆序可先求出全部子树状态。
	ord[1] = 1;
	int cnt = 1;
	for(int i = 1; i <= n; i++){
		int u = ord[i];
		for(int j = 0; j < (int)e[u].size(); j++){
			int v = e[u][j];
			if(v == fa[u]) continue;
			fa[v] = u;
			ord[++cnt] = v;
		}
	}
	// f[u],g[u]：u 子树内、包含 u 的连通块的最优值及方案数。
	for(int i = n; i >= 1; i--){
		int u = ord[i];
		f[u] = a[u];
		g[u] = 1;
		for(int j = 0; j < (int)e[u].size(); j++){
			int v = e[u][j];
			if(v == fa[u]) continue;
			f[u] += max(0LL,f[v]);
			g[u] = g[u] * addWays(f[v],g[v]) % MOD;
		}
	}
	// upf[u],upg[u]：父亲方向、必须包含 fa[u] 的最优值及方案数。
	for(int i = 1; i <= n; i++){
		int u = ord[i];
		int k = e[u].size();
		long long sum = a[u];
		pre[0] = 1;
		for(int j = 0; j < k; j++){
			int v = e[u][j];
			long long x,c;
			if(v == fa[u]){
				x = upf[u];
				c = upg[u];
			}else{
				x = f[v];
				c = g[v];
			}
			sum += max(0LL,x);
			way[j] = addWays(x,c);
			pre[j + 1] = pre[j] * way[j] % MOD;
		}
		ansf[u] = sum;
		ansg[u] = pre[k];
		long long suf = 1;
		for(int j = k - 1; j >= 0; j--){
			int v = e[u][j];
			if(v != fa[u]){
				upf[v] = sum - max(0LL,f[v]);
				upg[v] = pre[j] * suf % MOD;
			}
			suf = suf * way[j] % MOD;
		}
	}
	for(int i = 1; i <= n; i++){
		cout << ansf[i] << ' ' << ansg[i] << '\n';
	}
	return 0;
}
