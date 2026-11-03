#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10, mod = 1e9 + 7;
int n, m, f[maxn][19], dep[maxn], siz[maxn];
ll dis[maxn];
struct Edge { int v, w; };
vector<Edge> G[maxn];
void dfs(int u, int fa) {
	f[u][0] = fa, dep[u] = dep[fa] + 1, siz[u] = 1;
	for(int j = 1; j <= 18; j++) f[u][j] = f[f[u][j - 1]][j - 1];
	for(Edge e : G[u]) if(e.v != fa) dfs(e.v, u), siz[u] += siz[e.v];
}
void dfs2(int u, int fa) {
	for(Edge e : G[u]) if(e.v != fa) {
		dis[e.v] = (dis[u] + 1ll * siz[e.v] * (n - siz[e.v]) % mod * e.w) % mod;
		dfs2(e.v, u);
	}
}
int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	for(int j = 18; j >= 0; j--) if(dep[y] - (1 << j) >= dep[x]) y = f[y][j];
	if(x == y) return x;
	for(int j = 18; j >= 0; j--) if(f[x][j] != f[y][j]) x = f[x][j], y = f[y][j];
	return f[x][0];
}
int main() {
	freopen("patrol.in", "r", stdin);
	freopen("patrol.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back({v, w}), G[v].push_back({u, w});
	}
	dfs(1, 0), dfs2(1, 0);
	cin >> m;
	ll cur = 0, ans = 0;
	while(m--) {
		int opt; cin >> opt;
		if(opt == 1) {
			int u, v, c; cin >> u >> v >> c;
			ll sum = (dis[u] + dis[v] - 2 * dis[lca(u, v)] + 2 * mod) % mod;
			cur = (cur + sum * c) % mod;
		}
		else ans = (ans + cur) % mod;
	}
	cout << ans << '\n';
	return 0;
}
