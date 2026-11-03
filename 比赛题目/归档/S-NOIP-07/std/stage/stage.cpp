#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
const int maxm = 4e5 + 10;
struct Edge {
	int u, v, w;
	bool operator < (const Edge &x) const {
		return w < x.w;
	}
}e[maxm], h[500];
struct Node {
	int v, w;
};
struct Query {
	int id, u, w;
	bool operator < (const Query &x) const {
		return w < x.w;
	}
};
int n, m, q, fa[maxn], siz[maxn];
int f[maxn][20], mx[maxn][20], dep[maxn];
int pos[35], ans[maxn], cnt[maxn];
ll sum[35], b;
vector<Node> G[maxn];
vector<Edge> tree;
vector<Query> ask;
void init(int len) {
	for(int i = 1; i <= len; i++) fa[i] = i, siz[i] = 1;
}
int get(int x) {
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}
bool merge(int x, int y) {
	x = get(x), y = get(y);
	if(x == y) return 0;
	if(siz[x] > siz[y]) swap(x, y);
	fa[x] = y, siz[y] += siz[x];
	return 1;
}
void kruskal() {
	init(n);
	sort(e + 1, e + m + 1);
	for(int i = 1; i <= m; i++)
		if(merge(e[i].u, e[i].v)) {
			int u = e[i].u, v = e[i].v, w = e[i].w;
			G[u].push_back({v, w}), G[v].push_back({u, w});
			tree.push_back(e[i]);
		}
}
void dfs(int u, int pa) {
	f[u][0] = pa, dep[u] = dep[pa] + 1;
	for(Node x : G[u]) {
		if(x.v == pa) continue;
		mx[x.v][0] = x.w;
		dfs(x.v, u);
	}
}
int query(int x, int y) {
	int res = 0;
	if(dep[x] > dep[y]) swap(x, y);
	for(int i = 19; i >= 0; i--)
		if(dep[y] - (1 << i) >= dep[x]) res = max(res, mx[y][i]), y = f[y][i];
	if(x == y) return res;
	for(int i = 19; i >= 0; i--)
		if(f[x][i] != f[y][i]) {
			res = max(res, max(mx[x][i], mx[y][i]));
			x = f[x][i], y = f[y][i];
		}
	return max(res, max(mx[x][0], mx[y][0]));
}
void solve(int id) {
	int k, len = 0, cur = 0;
	cin >> k >> b;
	init(k);
	for(int i = 1; i <= k; i++) {
		cin >> pos[i] >> sum[i];
		cur += sum[i] >= b;
	}
	if(cur) { ans[id] = 0, cnt[id] = cur; return; }
	ans[id] = -1;
	for(int i = 1; i <= k; i++)
		for(int j = i + 1; j <= k; j++) h[++len] = {i, j, query(pos[i], pos[j])};
	sort(h + 1, h + len + 1);
	for(int l = 1, r; l <= len; l = r) {
		for(r = l; r <= len && h[r].w == h[l].w; r++) {
			int u = get(h[r].u), v = get(h[r].v);
			if(u == v) continue;
			cur -= (sum[u] >= b) + (sum[v] >= b);
			fa[u] = v, sum[v] += sum[u];
			cur += sum[v] >= b;
		}
		// 同权边全部加入后，才判断这一音量是否可行。
		if(!cur) continue;
		ans[id] = h[l].w;
		for(int i = 1; i <= k; i++)
			if(get(i) == i && sum[i] >= b) ask.push_back({id, pos[i], ans[id]});
		break;
	}
}
int main() {
	freopen("stage.in", "r", stdin);
	freopen("stage.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	kruskal();
	dfs(1, 0);
	for(int j = 1; j < 20; j++)
		for(int i = 1; i <= n; i++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
			mx[i][j] = max(mx[i][j - 1], mx[f[i][j - 1]][j - 1]);
		}
	for(int i = 1; i <= q; i++) solve(i);
	init(n);
	sort(ask.begin(), ask.end());
	int p = 0;
	for(Query x : ask) {
		while(p < (int)tree.size() && tree[p].w <= x.w) merge(tree[p].u, tree[p].v), p++;
		// 这里统计完整连通块，未标记的房间也要计入。
		cnt[x.id] += siz[get(x.u)];
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << ' ' << cnt[i] << '\n';
	return 0;
}
