#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int N = 500005;
int n, m, x, q, fa[N], siz[N], dfn[N], low[N], col[N], stk[N], top, cnt, tot;
bool vis[N];
vector<int> G[N];
vector<pair<int, int>> req;
int get(int u) { return u == fa[u] ? u : fa[u] = get(fa[u]); }
void merge(int u, int v) {
	u = get(u), v = get(v); if(u == v) return;
	if(siz[u] < siz[v]) swap(u, v);
	fa[v] = u, siz[u] += siz[v];
}
void tarjan(int u) {
	dfn[u] = low[u] = ++cnt; stk[++top] = u; vis[u] = 1;
	for(int v : G[u]) {
		if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if(vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		++tot; int v;
		do { v = stk[top--]; vis[v] = 0; col[v] = tot; } while(v != u);
	}
}
bool check(istream &in, istream &out, string &message) {
	in >> n >> m >> x >> q;
	for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
	for(int i = 0; i < q; i++) { int u, v; in >> u >> v; req.push_back({u, v}); merge(u, v); }
	vector<int> a;
	for(int i = 1; i <= n; i++) if(get(i) == i) a.push_back(siz[i]);
	bool possible = (int)a.size() >= x;
	if(possible) {
		sort(a.begin(), a.end());
		long long low = 0, high = 1ll * n * n, big = 0;
		for(int i = 0; i < x - 1; i++) { if(a[i] > 1) low += a[i]; high += 1ll * a[i] * a[i]; }
		for(int i = x - 1; i < (int)a.size(); i++) big += a[i];
		if(big > 1) low += big; high = (high + big * big) / 2 - n;
		possible = low <= m && m <= high;
	}
	long long u, v;
	if(!(out >> u)) { message = "Missing output"; return 0; }
	if(u == -1) {
		string extra;
		if(out >> extra) { message = "Extra output"; return 0; }
		if(possible) { message = "A valid graph exists"; return 0; }
		message = "Correct impossibility"; return 1;
	}
	if(!possible) { message = "Requested graph is impossible"; return 0; }
	vector<long long> edges;
	for(int i = 0; i < m; i++) {
		if(i && !(out >> u)) { message = "Missing edge"; return 0; }
		if(!(out >> v) || u < 1 || u > n || v < 1 || v > n || u == v) { message = "Invalid edge"; return 0; }
		G[u].push_back(v); edges.push_back(u * (n + 1ll) + v);
	}
	string extra;
	if(out >> extra) { message = "Extra output"; return 0; }
	sort(edges.begin(), edges.end());
	for(int i = 1; i < m; i++) if(edges[i] == edges[i - 1]) { message = "Repeated edge"; return 0; }
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
	if(tot != x) { message = "Wrong SCC count"; return 0; }
	for(auto e : req) if(col[e.first] != col[e.second]) { message = "Required vertices are separated"; return 0; }
	message = "Valid graph"; return 1;
}
int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv); ifstream in(argv[1]), out(argv[2]); string message;
	if(!check(in, out, message)) quitf(_wa, "%s", message.c_str());
	while(!ouf.eof()) ouf.skipChar();
	quitf(_ok, "%s", message.c_str());
}