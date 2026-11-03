#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 3010, maxm = 8010;
const ll inf = 4e18;
int n, q, x[maxn], y[maxn], fa[maxn], tot, best;
ll dis[maxn], ans;
bool vis[maxn], used[maxm];
struct Edge { int u, v; ll w; }e[maxm];
vector<int> G[maxn];
ll cal(int u, int v) {
	ll a = abs(x[u] - x[v]), b = abs(y[u] - y[v]);
	return a * a * a + b * b * b;
}
void add(int u, int v, ll w) {
	e[++tot] = {u, v, w}, used[tot] = 1;
	G[u].push_back(tot), G[v].push_back(tot);
}
void prim() {
	for(int i = 1; i <= n; i++) dis[i] = inf;
	dis[1] = 0;
	for(int i = 1; i <= n; i++) {
		int u = 0;
		for(int j = 1; j <= n; j++) if(!vis[j] && (!u || dis[j] < dis[u])) u = j;
		vis[u] = 1, ans += dis[u];
		if(fa[u]) add(u, fa[u], dis[u]);
		for(int v = 1; v <= n; v++) if(!vis[v] && cal(u, v) < dis[v]) dis[v] = cal(u, v), fa[v] = u;
	}
}
bool dfs(int u, int fa, int v) {
	if(u == v) return 1;
	for(int id : G[u]) if(used[id]) {
		int to = e[id].u ^ e[id].v ^ u;
		if(to == fa) continue;
		if(dfs(to, u, v)) {
			if(!best || e[id].w > e[best].w) best = id;
			return 1;
		}
	}
	return 0;
}
int main() {
	freopen("logistics.in", "r", stdin);
	freopen("logistics.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	prim(); cout << ans << '\n';
	while(q--) {
		int u, v; ll w; cin >> u >> v >> w;
		best = 0; dfs(u, 0, v);
		if(best && w < e[best].w) ans += w - e[best].w, used[best] = 0, add(u, v, w);
		cout << ans << '\n';
	}
	return 0;
}
