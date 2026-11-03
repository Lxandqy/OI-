#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, inf = 1e9;
struct Edge { int v, col; };
vector<Edge> G[maxn];
int n, a, b, dep[maxn], dis[maxn], chaser, runner;
bool vis[maxn];
void dfs(int u, int fa) {
	for(Edge e : G[u]) if(e.v != fa) dep[e.v] = dep[u] + 1, dfs(e.v, u);
}
void get(int u, int fa, int col) {
	for(Edge e : G[u]) if(e.v != fa && (!e.col || e.col == col))
		dis[e.v] = dis[u] + 1, get(e.v, u, col);
}
void check(int u, int fa, int col, int d) {
	if(d >= dis[u]) return;
	vis[u] = 1;
	for(Edge e : G[u]) if(e.v != fa && (!e.col || e.col == col)) check(e.v, u, col, d + 1);
}
int main() {
	freopen("dye.in", "r", stdin);
	freopen("dye.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> a >> b;
	for(int i = 1; i < n; i++) {
		int u, v; string s; cin >> u >> v >> s;
		int c = s == "black" ? 0 : s == "blue" ? 1 : 2;
		G[u].push_back({v, c}), G[v].push_back({u, c});
	}
	bool move = 0;
	for(Edge e : G[a]) if(e.v != b && e.col != 2) move = 1;
	if(!move) { cout << "Little Fang\n"; return 0; }
	move = 0;
	for(Edge e : G[b]) if(e.col != 1) move = 1;
	if(!move) { cout << "Cuber QQ\n"; return 0; }
	dfs(a, 0);
	chaser = dep[b] % 2 ? b : a, runner = chaser == a ? b : a;
	fill(dis + 1, dis + n + 1, inf);
	dis[chaser] = 0;
	get(chaser, 0, chaser == a ? 1 : 2);
	check(runner, 0, runner == a ? 1 : 2, 0);
	for(int u = 1; u <= n; u++) if(vis[u] && dis[u] == inf)
		for(Edge e : G[u]) if(vis[e.v] && dis[e.v] == inf && (!e.col || e.col == (runner == a ? 1 : 2))) {
			cout << "Draw\n"; return 0;
		}
	cout << (chaser == a ? "Cuber QQ\n" : "Little Fang\n");
	return 0;
}
