#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e3 + 10;
const ll inf = 4e18;
int n, c[maxn], d[maxn];
ll dis[maxn][maxn], f[maxn][maxn], g[maxn];
struct Edge { int v, w; };
vector<Edge> G[maxn];
void dfs(int u, int fa, int rt) {
	for(Edge e : G[u]) if(e.v != fa) dis[rt][e.v] = dis[rt][u] + e.w, dfs(e.v, u, rt);
}
void solve(int u, int fa) {
	for(int i = 1; i <= n; i++) f[u][i] = dis[u][i] <= d[u] ? c[i] : inf;
	for(Edge e : G[u]) if(e.v != fa) {
		int v = e.v; solve(v, u);
		for(int i = 1; i <= n; i++) if(f[u][i] < inf)
			f[u][i] += min(g[v], f[v][i] - c[i]);
	}
	g[u] = *min_element(f[u] + 1, f[u] + n + 1);
}
int main() {
	freopen("dye.in", "r", stdin);
	freopen("dye.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> c[i], G[i].clear();
		for(int i = 1; i <= n; i++) cin >> d[i];
		for(int i = 1; i < n; i++) {
			int u, v, w; cin >> u >> v >> w;
			G[u].push_back({v, w}), G[v].push_back({u, w});
		}
		for(int i = 1; i <= n; i++) dis[i][i] = 0, dfs(i, 0, i);
		solve(1, 0);
		cout << g[1] << '\n';
	}
	return 0;
}
