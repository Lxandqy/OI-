#include<bits/stdc++.h>
using namespace std;
const int maxn = 4005, maxm = 8005;
int n, m, dis[maxn];
bool vis[maxn];
struct Edge { int u, v, w; }e[maxm];
vector<int> G[maxn], R[maxn];
bool check(int sign) {
	fill(dis + 1, dis + n + 1, 0);
	for(int i = 1; i <= n; i++) {
		bool flag = 0;
		for(int j = 1; j <= m; j++) {
			int u = e[j].u, v = e[j].v, w = e[j].w * sign;
			if(dis[v] > dis[u] + w) dis[v] = dis[u] + w, flag = 1;
		}
		if(!flag) return 0;
	}
	return 1;
}
void dfs(int u, vector<int> *g) {
	vis[u] = 1;
	for(int v : g[u]) if(!vis[v]) dfs(v, g);
}
bool connected(int sign) {
	for(int i = 1; i <= m; i++) {
		int u = e[i].u, v = e[i].v;
		if(dis[u] + e[i].w * sign == dis[v]) G[u].push_back(v), R[v].push_back(u);
	}
	dfs(1, G);
	for(int i = 1; i <= n; i++) if(!vis[i]) return 0;
	fill(vis + 1, vis + n + 1, 0);
	dfs(1, R);
	for(int i = 1; i <= n; i++) if(!vis[i]) return 0;
	return 1;
}
int main() {
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		char c; cin >> e[i].u >> e[i].v >> c;
		e[i].w = c == '(' ? 1 : -1;
	}
	bool ans;
	if(!check(1)) ans = connected(1);
	else if(!check(-1)) ans = connected(-1);
	else ans = 1;
	cout << (ans ? "Yes" : "No") << '\n';
	return 0;
}
