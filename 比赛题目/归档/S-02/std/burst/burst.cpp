#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e4 + 10;
const ll inf = 4e18;
struct Edge { int v, w; };
struct Node {
	int pos; ll dis;
	bool operator < (const Node &x) const { return dis > x.dis; }
};
vector<Edge> G[maxn], a;
ll dis[maxn];
int n, m;
ll dij(int bit) {
	fill(dis + 1, dis + n + 1, inf);
	priority_queue<Node> q;
	for(int i = 0; i < (int)a.size(); i++) if(i >> bit & 1) {
		int u = a[i].v, w = a[i].w;
		if(dis[u] > w) dis[u] = w, q.push({u, w});
	}
	while(!q.empty()) {
		Node t = q.top(); q.pop();
		int u = t.pos;
		if(t.dis != dis[u]) continue;
		for(Edge e : G[u]) if(dis[e.v] > dis[u] + e.w) {
			dis[e.v] = dis[u] + e.w;
			q.push({e.v, dis[e.v]});
		}
	}
	ll ans = inf;
	for(int i = 0; i < (int)a.size(); i++) if(!(i >> bit & 1)) ans = min(ans, dis[a[i].v] + a[i].w);
	return ans;
}
int main() {
	freopen("burst.in", "r", stdin);
	freopen("burst.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) G[i].clear();
		a.clear();
		ll ans = inf;
		for(int i = 1; i <= m; i++) {
			int u, v, w; cin >> u >> v >> w;
			if(u == 1 && v == 1) ans = min(ans, 1ll * w);
			else if(u == 1) a.push_back({v, w});
			else if(v == 1) a.push_back({u, w});
			else G[u].push_back({v, w}), G[v].push_back({u, w});
		}
		for(int j = 0; (1 << j) < (int)a.size(); j++) ans = min(ans, dij(j));
		cout << (ans == inf ? -1 : ans) << '\n';
	}
	return 0;
}
