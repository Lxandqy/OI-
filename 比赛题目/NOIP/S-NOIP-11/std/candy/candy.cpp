#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
const ll inf = 1e18;
int n, m, col[maxn];
ll a[maxn], val;
bool flag;
struct Edge {
	int v, w;
};
vector<Edge> G[maxn];
vector<int> p;
void dfs(int u) {
	p.push_back(u);
	for(Edge e : G[u]) {
		int v = e.v;
		if(!col[v]) {
			col[v] = -col[u], a[v] = e.w - a[u];
			dfs(v);
		}
		else {
			ll x = e.w - a[u] - a[v];
			if(col[u] != col[v]) {
				if(x) flag = 0;
			}
			else {
				if(x % 2) flag = 0;
				x /= col[u] + col[v];
				if(val == inf) val = x;
				else if(val != x) flag = 0;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) G[i].clear(), col[i] = 0;
		for(int i = 1; i <= m; i++) {
			int u, v, w; cin >> u >> v >> w;
			G[u].push_back({v, w}), G[v].push_back({u, w});
		}
		ll l = inf, r = 0, ans = 0;
		flag = 1;
		for(int i = 1; i <= n; i++) {
			if(col[i]) continue;
			p.clear(), val = inf, col[i] = 1, a[i] = 0;
			dfs(i);
			if(val != inf) {
				for(int u : p) {
					ll x = col[u] * val + a[u];
					if(x < 0) flag = 0;
					l = min(l, x), r = max(r, x);
				}
			}
			else if(p.size() > 1) {
				ll mn[2] = {inf, inf}, mx[2] = {-inf, -inf};
				for(int u : p) {
					int k = col[u] == 1;
					mn[k] = min(mn[k], a[u]), mx[k] = max(mx[k], a[u]);
				}
				if(mn[0] + mn[1] < 0) flag = 0;
				l = min(l, (mn[0] + mn[1]) / 2);
				r = max(r, (mx[0] + mx[1] + 1) / 2);
				ans = max({ans, mx[0] - mn[0], mx[1] - mn[1]});
			}
		}
		if(!flag) cout << -1 << '\n';
		else cout << (l == inf ? 0 : max(ans, r - l)) << '\n';
	}
	return 0;
}
