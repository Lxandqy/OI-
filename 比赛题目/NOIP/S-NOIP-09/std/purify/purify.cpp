#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m, a[maxn], fa[maxn], dep[maxn], siz[maxn], son[maxn], cnt[maxn], ans;
vector<int> G[maxn], V[maxn];
struct Node {
	int v, d;
	bool operator < (const Node &x) const {
		return d > x.d;
	}
};
priority_queue<Node> q[maxn];
void dfs1(int u) {
	dep[u] = dep[fa[u]] + 1, siz[u] = V[u].size();
	for(int v : G[u]) {
		dfs1(v);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
bool dfs2(int u) {
	for(int v : G[u]) {
		if(!dfs2(v)) return 0;
		cnt[u] += cnt[v];
	}
	if(son[u]) q[u].swap(q[son[u]]);
	for(int v : G[u]) {
		if(v == son[u]) continue;
		while(!q[v].empty()) {
			q[u].push(q[v].top());
			q[v].pop();
		}
		q[v] = priority_queue<Node>();
	}
	for(int v : V[u]) q[u].push({v, dep[v]});
	while(cnt[u] < a[u]) {
		if(q[u].empty() || q[u].top().d > dep[u]) return 0;
		int v = q[u].top().v;
		q[u].pop();
		cnt[u]++, cnt[fa[v]]--, ans++;
	}
	return 1;
}
int main() {
	freopen("purify.in", "r", stdin);
	freopen("purify.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 2; i <= n; i++) {
			cin >> fa[i];
			G[fa[i]].push_back(i);
		}
		for(int i = 1; i <= m; i++) {
			int s, v; cin >> s >> v;
			V[s].push_back(v);
		}
		ans = cnt[0] = 0;
		dfs1(1);
		if(dfs2(1)) cout << ans << '\n';
		else cout << -1 << '\n';
		for(int i = 1; i <= n; i++) {
			G[i].clear(), V[i].clear();
			son[i] = cnt[i] = 0;
			q[i] = priority_queue<Node>();
		}
	}
	return 0;
}
