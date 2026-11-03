#include<bits/stdc++.h>
using namespace std;
const int maxn = 200005, maxm = 200005;
int n, m, a[100005], b[100005], dfn[maxn], low[maxn], timer;
bool bridge[maxm], covered[maxn];
vector<pair<int, int>> G[maxn];
void dfs(int u, int fa) {
	dfn[u] = low[u] = ++timer;
	for(auto e : G[u]) {
		int v = e.first, id = e.second;
		if(id == fa) continue;
		if(!dfn[v]) {
			dfs(v, id); low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) bridge[id] = 1;
		}
		else low[u] = min(low[u], dfn[v]);
	}
}
void init(int nodes, int edges) {
	for(int i = 1; i <= nodes; i++) G[i].clear(), dfn[i] = low[i] = 0;
	fill(bridge, bridge + edges + 1, 0); timer = 0;
}
void add(int u, int v, int id) {
	G[u].push_back({v, id}); G[v].push_back({u, id});
}
int count_bridge(int nodes, int edges) {
	for(int i = 1; i <= nodes; i++) if(!dfn[i]) dfs(i, 0);
	int ans = 0; for(int i = 1; i <= edges; i++) ans += bridge[i];
	return ans;
}
int optimum() {
	init(n, m);
	for(int i = 1; i <= m; i++) add(a[i], b[i], i);
	int ans = count_bridge(n, m);
	for(int i = 1; i <= m; i++) if(!bridge[i]) covered[a[i]] = covered[b[i]] = 1;
	for(int i = 1; i <= n; i++) ans += !covered[i];
	return ans;
}
int value(string s) {
	init(2 * n, n + m);
	for(int i = 1; i <= n; i++) add(i, i + n, i);
	for(int i = 1; i <= m; i++) {
		if(s[i - 1] == '0') add(a[i], b[i] + n, n + i);
		else add(a[i] + n, b[i], n + i);
	}
	return count_bridge(2 * n, n + m);
}
int main(int argc, char **argv) {
	if(argc != 7) return 1;
	ifstream in(argv[1]), out(argv[2]); ofstream score(argv[5]), message(argv[6]);
	in >> n >> m; for(int i = 1; i <= m; i++) in >> a[i]; for(int i = 1; i <= m; i++) in >> b[i];
	string s; char c; bool ok = 1;
	while(out >> c) { if(c != '0' && c != '1') ok = 0; if(s.size() <= (size_t)m) s += c; else ok = 0; }
	if((int)s.size() != m) ok = 0;
	if(ok) { int best = optimum(); ok = value(s) == best; }
	score << (ok ? atoi(argv[4]) : 0) << '\n'; message << (ok ? "Accepted" : "Invalid or nonoptimal construction") << '\n';
	return 0;
}