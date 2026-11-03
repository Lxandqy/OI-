#include<bits/stdc++.h>
#define ll long long
#define PII pair<ll, int>
using namespace std;
const int maxn = 2e5 + 10;
const int maxm = 4e5 + 10;
const ll inf = 4000000000000000000ll;
struct Edge {
	int to, nxt;
	int w;
} e[maxm];
int n, m, tot, head[maxn];
// a、b 为画师和主题，c 为售价；id[u] 存点 u 保留的源点编号。
int a[maxn], b[maxn], c[maxn], id[maxn][5];
ll d1[maxn], dn[maxn], ans = inf;
struct Node {
	// 从车站到 s 买第一张，再走到 u 的费用；尚未买第二张。
	ll d;
	int u, s;
	bool operator<(const Node &x) const {
		return d > x.d;
	}
};
void add(int u, int v, int z) {
	e[++tot].to = v;
	e[tot].w = z;
	e[tot].nxt = head[u];
	head[u] = tot;
}
void dijkstra(int s, ll *d) {
	fill(d + 1, d + n + 1, inf);
	priority_queue<PII, vector<PII>, greater<PII>> q;
	d[s] = 0;
	q.push({0, s});
	while(!q.empty()) {
		PII t = q.top();
		q.pop();
		int u = t.second;
		if(t.first != d[u]) continue;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(d[v] > d[u] + e[i].w) {
				d[v] = d[u] + e[i].w;
				q.push({d[v], v});
			}
		}
	}
}
// 按费用从小到大出堆，每个点至多保留五个源点并继续扩展。
bool check(int u, int s) {
	if(!id[u][0]) {
		id[u][0] = s;
		return true;
	}
	// 第一个源点最便宜，以它的两种标签为基准。
	int x = id[u][0];
	bool ok = false;
	// 画师与基准不同：保留两个主题不同的源点。
	if(a[s] != a[x]) {
		if(!id[u][1]) id[u][1] = s, ok = true;
		else if(!id[u][2] && b[s] != b[id[u][1]]) id[u][2] = s, ok = true;
	}
	// 主题与基准不同：保留两个画师不同的源点。两组允许重合。
	if(b[s] != b[x]) {
		if(!id[u][3]) id[u][3] = s, ok = true;
		else if(!id[u][4] && a[s] != a[id[u][3]]) id[u][4] = s, ok = true;
	}
	return ok;
}
int main() {
	freopen("postcard.in", "r", stdin);
	freopen("postcard.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
	for(int i = 1; i <= m; i++) {
		int u, v, z;
		cin >> u >> v >> z;
		add(u, v, z);
		add(v, u, z);
	}
	dijkstra(1, d1);
	dijkstra(n, dn);
	if(d1[n] == inf) {
		cout << -1 << '\n';
		return 0;
	}
	priority_queue<Node> q;
	for(int i = 1; i <= n; i++) {
		if(d1[i] != inf) q.push({d1[i] + c[i], i, i});
	}
	while(!q.empty()) {
		Node t = q.top();
		q.pop();
		int u = t.u, s = t.s;
		// 被舍弃的源点若能配对，总有保留的源点能配对且费用不更大。
		if(!check(u, s)) continue;
		// 在 u 买第二张，补上售价和去码头的路费。
		if(a[s] != a[u] && b[s] != b[u]) ans = min(ans, t.d + c[u] + dn[u]);
		for(int i = head[u]; i; i = e[i].nxt) q.push({t.d + e[i].w, e[i].to, s});
	}
	cout << (ans == inf ? -1 : ans) << '\n';
	return 0;
}
