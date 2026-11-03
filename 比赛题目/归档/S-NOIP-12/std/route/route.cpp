#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, f[maxn][19], dep[maxn], a[maxn], b[maxn];
int up[maxn], down[maxn], id[maxn];
bool vis[maxn];
struct Edge {
	int v, w;
};
vector<Edge> G[maxn];
vector<int> g[maxn];
void dfs(int u, int fa) {
	f[u][0] = fa, dep[u] = dep[fa] + 1;
	for(Edge e : G[u]) {
		if(e.v == fa) continue;
		a[e.v] = e.w;
		dfs(e.v, u);
	}
}
int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	for(int i = 18; i >= 0; i--)
		if(dep[y] - (1 << i) >= dep[x]) y = f[y][i];
	if(x == y) return x;
	for(int i = 18; i >= 0; i--)
		if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
int get(int x, int u) {
	for(int i = 18; i >= 0; i--)
		if(dep[f[x][i]] > dep[u]) x = f[x][i];
	return x;
}
void build(int u, int fa) {
	for(Edge e : G[u]) {
		if(e.v == fa) continue;
		build(e.v, u);
		up[u] += up[e.v], down[u] += down[e.v];
	}
	if(up[u]) g[u].push_back(fa);
	if(down[u]) g[fa].push_back(u);
}
void paint(int u, int w) {
	vis[u] = 1, b[u] = w;
	for(int v : g[u])
		if(!vis[v]) paint(v, w);
}
bool cmp(int x, int y) {
	return a[x] > a[y];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			G[i].clear(), g[i].clear();
			up[i] = down[i] = vis[i] = a[i] = 0;
			id[i] = i;
		}
		for(int i = 1; i < n; i++) {
			int u, v, w; cin >> u >> v >> w;
			G[u].push_back({v, w}), G[v].push_back({u, w});
		}
		dfs(1, 0);
		for(int j = 1; j <= 18; j++)
			for(int i = 1; i <= n; i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
		while(m--) {
			int u, v; cin >> u >> v;
			int w = lca(u, v), p = 0, q = 0;
			if(u != w) {
				p = get(u, w);
				up[u]++, up[p]--;
			}
			if(v != w) {
				q = get(v, w);
				down[v]++, down[q]--;
			}
			if(p && q) g[p].push_back(q);
		}
		build(1, 0);
		sort(id + 2, id + n + 1, cmp);
		for(int i = 2; i <= n; i++)
			if(!vis[id[i]]) paint(id[i], a[id[i]]);
		ll ans = 0;
		for(int i = 2; i <= n; i++) ans += b[i] - a[i];
		cout << ans << '\n';
	}
	return 0;
}
