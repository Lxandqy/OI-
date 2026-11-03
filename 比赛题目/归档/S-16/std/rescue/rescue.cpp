#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, rt, a[maxn], siz[maxn];
bool vis[maxn];
ll sum, d[maxn], d1[maxn], d2[maxn], ans[maxn];
struct Edge {
	int v, w;
};
vector<Edge> G[maxn];
void dfs(int u, int fa) {
	siz[u] = vis[u];
	for(Edge e : G[u]) {
		int v = e.v;
		if(v == fa) continue;
		d[v] = d[u] + e.w;
		dfs(v, u);
		siz[u] += siz[v];
		if(siz[v]) sum += e.w;
	}
}
void getdis(int u, int fa, ll *dis) {
	for(Edge e : G[u]) {
		int v = e.v;
		if(v == fa) continue;
		dis[v] = dis[u] + e.w;
		getdis(v, u, dis);
	}
}
void solve(int u, int fa, ll len) {
	ans[u] = len - max(d1[u], d2[u]);
	for(Edge e : G[u]) {
		int v = e.v;
		if(v == fa) continue;
		// 根本身是标记点，只有没有标记点的分支会增加往返路程。
		solve(v, u, len + (siz[v] ? 0 : 2ll * e.w));
	}
}
int main() {
	freopen("rescue.in", "r", stdin);
	freopen("rescue.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back({v, w}), G[v].push_back({u, w});
	}
	for(int i = 1; i <= k; i++) cin >> a[i], vis[a[i]] = 1;
	rt = a[1];
	dfs(rt, 0);
	int x = rt, y = rt;
	for(int i = 1; i <= k; i++) if(d[a[i]] > d[x]) x = a[i];
	getdis(x, 0, d1);
	for(int i = 1; i <= k; i++) if(d1[a[i]] > d1[y]) y = a[i];
	getdis(y, 0, d2);
	solve(rt, 0, 2 * sum);
	for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
	return 0;
}
