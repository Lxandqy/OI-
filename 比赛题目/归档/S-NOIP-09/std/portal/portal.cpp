#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, s, c[maxn], a[maxn], step[maxn];
ll dis[maxn];
struct Edge {
	int u, l, r, w;
}e[maxn];
struct Node {
	int pos;
	ll dis;
	int cnt;
	bool operator < (const Node &x) const {
		if(dis == x.dis) return cnt > x.cnt;
		return x.dis < dis;
	}
};
vector<int> G[maxn];
priority_queue<Node> q;
set<int> p, seg;
void del(int x) {
	auto it = p.find(x), r = next(it);
	int u = it == p.begin() ? 0 : *prev(it);
	int v = r == p.end() ? n + 1 : *r;
	p.erase(it);
	seg.erase(x);
	// 删去 x 后，只有后继是否为段首可能变化。
	if(v <= n) {
		if(u && c[u] == c[v]) seg.erase(v);
		else seg.insert(v);
	}
}
void update(int u, ll d, int cnt) {
	dis[u] = d;
	step[u] = cnt;
	for(int id : G[u]) q.push({id, d + e[id].w, cnt + 1});
}
void dij() {
	del(s);
	update(s, 0, 0);
	while(!q.empty()) {
		Node now = q.top(); q.pop();
		Edge cur = e[now.pos];
		auto it = p.lower_bound(cur.l);
		while(it != p.end() && *it <= cur.r) {
			int v = *it;
			if(c[v] == c[cur.u]) {
				// 整段都不能到达，跳到下一个段首。
				auto nxt = seg.upper_bound(v);
				if(nxt == seg.end() || *nxt > cur.r) break;
				it = p.find(*nxt);
			}
			else {
				del(v);
				update(v, now.dis + a[v], now.cnt);
				it = p.lower_bound(v);
			}
		}
	}
}
void solve() {
	cin >> n >> m >> s;
	p.clear(); seg.clear();
	for(int i = 1; i <= n; i++) {
		G[i].clear();
		dis[i] = step[i] = -1;
		cin >> c[i];
		p.insert(i);
		if(i == 1 || c[i] != c[i - 1]) seg.insert(i);
	}
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) {
		cin >> e[i].u >> e[i].l >> e[i].r >> e[i].w;
		G[e[i].u].push_back(i);
	}
	dij();
	for(int i = 1; i <= n; i++) cout << dis[i] << ' ' << step[i] << '\n';
}
int main() {
	freopen("portal.in", "r", stdin);
	freopen("portal.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
