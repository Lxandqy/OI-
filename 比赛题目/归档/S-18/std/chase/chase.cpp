#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, q, dep[maxn], f[maxn][19];
vector<int> G[maxn];
void dfs(int u, int fa) {
	f[u][0] = fa, dep[u] = dep[fa] + 1;
	for(int v : G[u]) if(v != fa) dfs(v, u);
}
int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	for(int j = 18; j >= 0; j--) if(dep[y] - (1 << j) >= dep[x]) y = f[y][j];
	if(x == y) return x;
	for(int j = 18; j >= 0; j--) if(f[x][j] != f[y][j]) x = f[x][j], y = f[y][j];
	return f[x][0];
}
int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
int jump(int u, int k) {
	for(int j = 18; j >= 0; j--) if(k >> j & 1) u = f[u][j];
	return u;
}
int walk(int x, int y, int k) {
	int p = lca(x, y), len = dep[x] - dep[p];
	if(k <= len) return jump(x, k);
	return jump(y, len + dep[y] - dep[p] - k);
}
int main() {
	freopen("chase.in", "r", stdin);
	freopen("chase.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1, 0);
	for(int j = 1; j <= 18; j++) for(int i = 1; i <= n; i++) f[i][j] = f[f[i][j - 1]][j - 1];
	while(q--) {
		int s, t, p; cin >> s >> t >> p;
		if(dis(s, t) < dis(p, t)) cout << dis(p, t) << ' ' << t << '\n';
		else {
			int ans = (dis(s, p) + 1) / 2;
			cout << ans << ' ' << walk(s, t, ans) << '\n';
		}
	}
	return 0;
}
