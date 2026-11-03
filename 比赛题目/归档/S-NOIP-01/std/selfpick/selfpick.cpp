#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
struct Edge {
	int to, nxt;
	int w;
} e[maxn * 2];
int n, q, cnt, tot, head[maxn];
int dep[maxn], fa[maxn][20], dfn[maxn], id[maxn];
ll dis[maxn], sum;
bool vis[maxn];
// s 按 DFS 序存邮局和收件点，sum 是首尾相连后的环长。
set<int> s;
// 每个收件点自取能省下的路程，允许多个点的贡献相同。
multiset<ll> val;
void add(int u, int v, int z) {
	e[++cnt].to = v;
	e[cnt].w = z;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
void dfs(int u, int f) {
	dfn[u] = ++tot;
	id[tot] = u;
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
	for(int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == f) continue;
		dis[v] = dis[u] + e[i].w;
		dfs(v, u);
	}
}
int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	for(int i = 19; i >= 0; i--)
		if(dep[y] - (1 << i) >= dep[x]) y = fa[y][i];
	if(x == y) return x;
	for(int i = 19; i >= 0; i--)
		if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
ll getdis(int u, int v) {
	return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}
int pre(set<int>::iterator it) {
	if(it == s.begin()) it = s.end();
	return *prev(it);
}
int nxtpos(set<int>::iterator it) {
	it++;
	if(it == s.end()) it = s.begin();
	return *it;
}
// 把 l-r 换成 l-x-r 增加的环长，也就是删去 x 时省下的路程。
ll calc(int x, int l, int r) {
	return getdis(id[l], id[x]) + getdis(id[x], id[r]) - getdis(id[l], id[r]);
}
void change(int x, int type) {
	// 邮局始终留在环中，但不能作为自取候选。
	if(x == dfn[1]) return;
	auto it = s.find(x);
	ll z = calc(x, pre(it), nxtpos(it));
	if(type == 1) val.insert(z);
	else val.erase(val.find(z));
}
int main() {
	freopen("selfpick.in", "r", stdin);
	freopen("selfpick.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i < n; i++) {
		int u, v, z;
		cin >> u >> v >> z;
		add(u, v, z);
		add(v, u, z);
	}
	dfs(1, 0);
	s.insert(dfn[1]);
	while(q--) {
		int u;
		cin >> u;
		int x = dfn[u], l, r;
		if(!vis[u]) {
			auto it = s.lower_bound(x);
			if(it == s.end()) it = s.begin();
			r = *it;
			l = pre(it);
			// 插入只影响左右邻居的贡献；邻居相同时只删一次。
			change(l, -1);
			if(r != l) change(r, -1);
			sum += calc(x, l, r);
			s.insert(x);
			change(x, 1);
			change(l, 1);
			if(r != l) change(r, 1);
		}
		else {
			auto it = s.find(x);
			l = pre(it);
			r = nxtpos(it);
			// 先删旧贡献，再改变环，最后重算留下的邻居。
			change(x, -1);
			change(l, -1);
			if(r != l) change(r, -1);
			sum -= calc(x, l, r);
			s.erase(it);
			change(l, 1);
			if(r != l) change(r, 1);
		}
		vis[u] = !vis[u];
		// 环长等于全部送达的往返路程，再减去最大的自取贡献。
		cout << sum - (val.empty() ? 0 : *val.rbegin()) << '\n';
	}
	return 0;
}
