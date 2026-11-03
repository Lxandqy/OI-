#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, a[maxn], id[maxn], fa[maxn], siz[maxn];
int head[maxn], tail[maxn], nxt[maxn];
ll sum[maxn], ans[maxn];
bool vis[maxn];
vector<int> G[maxn];
int get(int x) {
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}
void merge(int x, int y) {
	x = get(x), y = get(y);
	if(x == y) return;
	if(siz[x] < siz[y]) swap(x, y);
	fa[y] = x, siz[x] += siz[y], sum[x] += sum[y];
	nxt[tail[x]] = head[y], tail[x] = tail[y];
}
bool cmp(int x, int y) {
	return a[x] < a[y];
}
void solve() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		id[i] = fa[i] = head[i] = tail[i] = i;
		siz[i] = 1, sum[i] = a[i], ans[i] = nxt[i] = vis[i] = 0;
		G[i].clear();
	}
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	sort(id + 1, id + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		int u = id[i];
		vis[u] = 1;
		for(int v : G[u]) {
			if(!vis[v]) continue;
			int x = get(u), y = get(v);
			if(x == y) continue;
			if(sum[y] < a[u])
				for(int j = head[y]; j; j = nxt[j])
					ans[j] = max(ans[j], a[u] - sum[y]);
			merge(x, y);
		}
	}
	for(int i = 1; i <= n; i++) cout << ans[i] << (i == n ? '\n' : ' ');
}
int main() {
	freopen("explore.in", "r", stdin);
	freopen("explore.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
