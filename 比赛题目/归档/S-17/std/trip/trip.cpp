#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e4 + 10;
int n, m, s, t, k, c[maxn];
struct Edge {
	int v, w;
	bool bad;
};
vector<Edge> G[maxn];
struct Node {
	int pos, k;
	ll dis;
	bool operator < (const Node &x) const {
		return x.dis < dis;
	}
};
priority_queue<Node> q;
ll dis[maxn][21];
bool vis[maxn][21];
void modify(int u, int h, ll d) {
	if(dis[u][h] > d) {
		dis[u][h] = d;
		q.push({u, h, d});
	}
}
ll dij() {
	memset(dis, 0x3f, sizeof(dis));
	modify(s, 0, 0);
	while(!q.empty()) {
		Node tp = q.top(); q.pop();
		int u = tp.pos, h = tp.k;
		if(vis[u][h]) continue;
		vis[u][h] = 1;
		if(u == t) return tp.dis;
		if(c[u] && h < k) modify(u, h + 1, tp.dis + c[u]);
		for(Edge e : G[u]) {
			int w = (e.w + (1 << h) - 1) >> h;
			modify(e.v, e.bad ? 0 : h, tp.dis + w);
		}
	}
	return -1;
}
int main() {
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> s >> t;
	int mx = 1;
	for(int i = 1; i <= m; i++) {
		int u, v, w; char ch; cin >> u >> v >> w >> ch;
		G[u].push_back({v, w, ch == 'B'});
		mx = max(mx, w);
	}
	while((1 << k) < mx) k++;
	int p; cin >> p;
	while(p--) {
		int u, w; cin >> u >> w;
		if(!c[u] || c[u] > w) c[u] = w;
	}
	cout << dij() << '\n';
	return 0;
}
