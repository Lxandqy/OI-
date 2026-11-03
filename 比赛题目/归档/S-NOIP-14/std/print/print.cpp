#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, top, ind, tot;
int t[maxn], d[maxn], w[maxn], s[maxn];
int dfn[maxn], low[maxn], col[maxn], vis[maxn];
vector<int> g[maxn], a[maxn], b[maxn];
void tarjan(int x) {
	s[++top] = x;
	dfn[x] = low[x] = ++ind;
	vis[x] = 1;
	for(int v : g[x]) {
		if(!dfn[v]) {
			tarjan(v);
			low[x] = min(low[x], low[v]);
		}
		else if(vis[v]) low[x] = min(low[x], dfn[v]);
	}
	if(dfn[x] == low[x]) {
		++tot;
		while(s[top] != x) {
			col[s[top]] = tot;
			vis[s[top--]] = 0;
		}
		col[s[top]] = tot;
		vis[s[top--]] = 0;
	}
}
bool cmp(int x, int y) {
	return d[x] > d[y];
}
void solve() {
	cin >> n >> m;
	top = ind = tot = 0;
	for(int i = 1; i <= n; i++) {
		g[i].clear(), a[i].clear(), b[i].clear();
		dfn[i] = low[i] = col[i] = vis[i] = 0;
		cin >> t[i] >> d[i] >> w[i];
	}
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; i++) a[col[i]].push_back(t[i]), b[col[i]].push_back(i);
	ll ans = 0;
	for(int i = 1; i <= tot; i++) {
		sort(a[i].begin(), a[i].end(), greater<int>());
		sort(b[i].begin(), b[i].end(), cmp);
		priority_queue<int> q;
		int pos = 0;
		for(int x : a[i]) {
			while(pos < (int)b[i].size() && d[b[i][pos]] >= x) q.push(w[b[i][pos++]]);
			if(!q.empty()) ans += q.top(), q.pop();
		}
	}
	cout << ans << '\n';
}
int main() {
	freopen("print.in", "r", stdin);
	freopen("print.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
