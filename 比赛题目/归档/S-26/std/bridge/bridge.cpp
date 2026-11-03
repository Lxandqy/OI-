#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, a[maxn], b[maxn], ans[maxn];
bool vis[maxn], used[maxn];
struct Edge { int v, id; };
vector<Edge> G[maxn];
void dfs(int u) {
	vis[u] = 1;
	for(Edge e : G[u]) {
		int v = e.v, id = e.id;
		if(used[id]) continue;
		used[id] = 1;
		ans[id] = (u == a[id]);
		if(!vis[v]) dfs(v);
	}
}
int main() {
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) {
		cin >> b[i];
		G[a[i]].push_back({b[i], i});
		G[b[i]].push_back({a[i], i});
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i);
	for(int i = 1; i <= m; i++) cout << ans[i];
	cout << '\n';
	return 0;
}
