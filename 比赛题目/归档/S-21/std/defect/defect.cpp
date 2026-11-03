#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, inf = 1e9;
int n, m, d, k, f[maxn][2], dis[maxn][2], pre[maxn][2];
vector<int> G[maxn];
queue<pair<int, int>> q;
void init() {
	for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = dis[i][0] = dis[i][1] = inf;
}
void bfs() {
	while(!q.empty()) {
		int u = q.front().first, p = q.front().second; q.pop();
		if(f[u][p] == d) continue;
		for(int v : G[u]) if(f[v][p ^ 1] == inf) {
			f[v][p ^ 1] = f[u][p] + 1;
			q.push({v, p ^ 1});
		}
	}
}
void solve() {
	dis[1][0] = 0; q.push({1, 0});
	while(!q.empty()) {
		int u = q.front().first, p = q.front().second; q.pop();
		if(u == n) {
			vector<int> path;
			int len = dis[u][p];
			while(u) { path.push_back(u); u = pre[u][p]; p ^= 1; }
			reverse(path.begin(), path.end());
			cout << len << '\n';
			for(int x : path) cout << x << ' ';
			cout << '\n'; return;
		}
		for(int v : G[u]) if(dis[v][p ^ 1] == inf && dis[u][p] + 1 < f[v][p ^ 1]) {
			dis[v][p ^ 1] = dis[u][p] + 1;
			pre[v][p ^ 1] = u;
			q.push({v, p ^ 1});
		}
	}
	cout << -1 << '\n';
}
int main() {
	freopen("defect.in", "r", stdin);
	freopen("defect.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m >> d;
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	init(); cin >> k;
	while(k--) {
		int u; cin >> u;
		f[u][0] = 0; q.push({u, 0});
	}
	bfs();
	for(int i = 1; i <= n; i++) sort(G[i].begin(), G[i].end());
	solve();
	return 0;
}
