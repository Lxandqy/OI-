#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
struct Edge {
	int v, w;
};
int n, q, d[maxn], f[maxn], g[maxn], h[maxn], ans[maxn], cnt[maxn];
vector<Edge> G[maxn];
// d 是子树内走到 u 的最大总消耗，f 是这些路程所需体力的最大值。
void dfs(int u, int p) {
	for(Edge e : G[u]) if(e.v != p) {
		dfs(e.v, u);
		int x = d[e.v] - e.w;
		d[u] = max(d[u], x);
		f[u] = max(f[u], max(f[e.v], x));
	}
}
void update(int x, int &a, int &b) {
	if(x >= a) b = a, a = x;
	else b = max(b, x);
}
// g、h 对应从子树外出发的路程；g 允许为负。
void dfs2(int u, int p) {
	// 0 对应从 u 出发的空路径；次大值允许与最大值相等。
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	update(g[u], x1, x2); update(h[u], y1, y2);
	for(Edge e : G[u]) if(e.v != p) {
		int x = d[e.v] - e.w, y = max(f[e.v], x);
		update(x, x1, x2); update(y, y1, y2);
	}
	ans[u] = y1;
	for(Edge e : G[u]) if(e.v != p) {
		int x = d[e.v] - e.w, y = max(f[e.v], x);
		// 去掉当前儿子的贡献，再接上 u 到儿子的这条边。
		g[e.v] = (x == x1 ? x2 : x1) + e.w;
		h[e.v] = max(y == y1 ? y2 : y1, g[e.v]);
		dfs2(e.v, u);
	}
}
int main() {
	freopen("hill.in", "r", stdin);
	freopen("hill.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back({v, 1}); G[v].push_back({u, -1});
	}
	dfs(1, 0); dfs2(1, 0);
	for(int i = 1; i <= n; i++) cnt[ans[i]]++;
	for(int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
	while(q--) {
		int k; cin >> k;
		cout << cnt[min(k, n - 1)] << '\n';
	}
	return 0;
}
