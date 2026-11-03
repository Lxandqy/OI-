#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10, mod = 998244353;
int n, m, s, t, tp, tail;
int a[maxn], dis[maxn], f[maxn], q[maxn];
int fa[2][maxn], l[2][maxn], r[2][maxn];
vector<pair<int, int>> e;
int pos(int u, int opt) {
	return opt ? u % m * n + u / m : u;
}
int get(int opt, int x) {
	return fa[opt][x] == x ? x : fa[opt][x] = get(opt, fa[opt][x]);
}
bool cmp(int x, int y) {
	return pos(x, tp) < pos(y, tp);
}
void add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}
void visit(int u, int d) {
	dis[u] = d, q[tail++] = u;
	for(int opt = 0; opt < 2; opt++) {
		int v = pos(u, opt);
		fa[opt][v] = get(opt, v + 1);
	}
}
void bfs() {
	fill(dis, dis + n * m, -1);
	tail = 0, visit(s, 0);
	for(int head = 0; head < tail; head++) {
		int u = q[head];
		for(int opt = 0; opt < 2; opt++) {
			int v = get(opt, l[opt][u]);
			while(v <= r[opt][u]) {
				int w = opt ? v % n * m + v / n : v;
				visit(w, dis[u] + 1);
				v = get(opt, v);
			}
		}
	}
}
void cal(int l1, int r1, int l2, int r2, int opt) {
	e.clear();
	for(int i = l1; i < r1; i++) {
		int u = q[i];
		e.push_back({l[opt][u], f[u]});
		e.push_back({r[opt][u] + 1, mod - f[u]});
	}
	sort(e.begin(), e.end());
	tp = opt, sort(q + l2, q + r2, cmp);
	int j = 0, sum = 0;
	for(int i = l2; i < r2; i++) {
		int u = q[i];
		while(j < (int)e.size() && e[j].first <= pos(u, opt)) add(sum, e[j++].second);
		add(f[u], sum);
	}
}
void solve() {
	cin >> n >> m;
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	s = (x1 - 1) * m + y1 - 1, t = (x2 - 1) * m + y2 - 1;
	for(int i = 0; i < n * m; i++) cin >> a[i];
	for(int opt = 0; opt < 2; opt++) {
		fa[opt][n * m] = n * m;
		for(int i = n * m - 1; i >= 0; i--) {
			int u = opt ? i % n * m + i / n : i;
			fa[opt][i] = a[u] ? i : fa[opt][i + 1];
		}
	}
	for(int i = 0; i < n; i++) {
		int last = 0;
		for(int j = 0; j < m; j++) {
			int u = i * m + j;
			if(!a[u]) last = j + 1;
			else l[0][u] = i * m + max(last, j - a[u]);
		}
		last = m - 1;
		for(int j = m - 1; j >= 0; j--) {
			int u = i * m + j;
			if(!a[u]) last = j - 1;
			else r[0][u] = i * m + min(last, j + a[u]);
		}
	}
	for(int j = 0; j < m; j++) {
		int last = 0;
		for(int i = 0; i < n; i++) {
			int u = i * m + j;
			if(!a[u]) last = i + 1;
			else l[1][u] = j * n + max(last, i - a[u]);
		}
		last = n - 1;
		for(int i = n - 1; i >= 0; i--) {
			int u = i * m + j;
			if(!a[u]) last = i - 1;
			else r[1][u] = j * n + min(last, i + a[u]);
		}
	}
	bfs();
	if(dis[t] == -1) {
		cout << "-1 0\n";
		return;
	}
	vector<int> st(1, 0);
	for(int i = 1; i < tail; i++) if(dis[q[i]] != dis[q[i - 1]]) st.push_back(i);
	st.push_back(tail);
	fill(f, f + n * m, 0), f[s] = 1;
	for(int i = 1; i <= dis[t]; i++) {
		cal(st[i - 1], st[i], st[i], st[i + 1], 0);
		cal(st[i - 1], st[i], st[i], st[i + 1], 1);
	}
	cout << dis[t] << ' ' << f[t] << '\n';
}
int main() {
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
