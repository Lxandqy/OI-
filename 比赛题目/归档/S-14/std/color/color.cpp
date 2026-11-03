#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10, mod = 1e9 + 7;
int n, root, d1[maxn], d2[maxn], cnt[maxn], pw[maxn];
vector<int> G[maxn];
void dfs(int u, int fa, int *dis) {
	if(dis[u] > dis[root]) root = u;
	for(int v : G[u]) {
		if(v == fa) continue;
		dis[v] = dis[u] + 1;
		dfs(v, u, dis);
	}
}
int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	root = 1, dfs(1, 0, d1);
	int x = root;
	d1[x] = 0, dfs(x, 0, d1);
	int y = root, len = d1[y];
	dfs(y, 0, d2);
	int k = 0;
	for(int i = 1; i <= n; i++) {
		k = max(k, min(d1[i], d2[i]));
		cnt[max(d1[i], d2[i])]++;
	}
	pw[0] = 1;
	for(int i = 1; i <= n; i++) pw[i] = 2ll * pw[i - 1] % mod;
	ll ans = 1ll * len * pw[n] % mod;
	for(int i = 0; i < len; i++) {
		if(i) cnt[i] += cnt[i - 1];
		if(i >= k) ans = (ans - 2ll * pw[cnt[i]] % mod + mod) % mod;
	}
	cout << ans << '\n';
	return 0;
}
