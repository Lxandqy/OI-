#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 100 + 5;
const ll inf = 4e18;
int n, a[maxn];
ll g[maxn][maxn][maxn], h[maxn][maxn][maxn];
vector<ll> f[maxn][maxn];
vector<int> ans;
ll &get(int l, int r, int s, int t) {
	return f[l][r][(s - l) * (r - l + 1) + t - l];
}
int get_end(int l, int r, int s) {
	for(int t = l; t <= r; t++)
		if(get(l, r, s, t) + abs(a[t] - a[l - 1]) == g[l][r][s]) return t;
	return 0;
}
void dfs(int l, int r, int s, int p) {
	if(l == r) {
		ans.push_back(l);
		return;
	}
	if(p == l) dfs(l + 1, r, s, get_end(l + 1, r, s));
	else {
		for(int t = l; t < p; t++) {
			ll val = p == r ? abs(a[t] - a[p]) : h[p + 1][r][t];
			if(get(l, p - 1, s, t) + val != get(l, r, s, p)) continue;
			dfs(l, p - 1, s, t);
			if(p < r) {
				for(int u = p + 1; u <= r; u++) {
					if(g[p + 1][r][u] + abs(a[t] - a[u]) != val) continue;
					dfs(p + 1, r, u, get_end(p + 1, r, u));
					break;
				}
			}
			break;
		}
	}
	ans.push_back(p);
}
void solve() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int len = 1; len <= n; len++) {
		for(int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			f[l][r].assign(len * len, inf);
			if(l == r) get(l, r, l, l) = 0;
			else {
				for(int s = l + 1; s <= r; s++)
					get(l, r, s, l) = g[l + 1][r][s];
				for(int p = l + 1; p <= r; p++) {
					for(int s = l; s < p; s++) {
						ll res = inf;
						for(int t = l; t < p; t++) {
							ll val = p == r ? abs(a[t] - a[p]) : h[p + 1][r][t];
							res = min(res, get(l, p - 1, s, t) + val);
						}
						get(l, r, s, p) = res;
					}
				}
			}
			if(l == 1) continue;
			for(int s = l; s <= r; s++) {
				g[l][r][s] = inf;
				for(int t = l; t <= r; t++)
					g[l][r][s] = min(g[l][r][s], get(l, r, s, t) + abs(a[t] - a[l - 1]));
			}
			for(int t = 1; t < l - 1; t++) {
				h[l][r][t] = inf;
				for(int s = l; s <= r; s++)
					h[l][r][t] = min(h[l][r][t], g[l][r][s] + abs(a[t] - a[s]));
			}
		}
	}
	ll res = inf;
	int x = 0, y = 0;
	for(int s = 1; s <= n; s++)
		for(int t = 1; t <= n; t++)
			if(get(1, n, s, t) < res) res = get(1, n, s, t), x = s, y = t;
	ans.clear();
	dfs(1, n, x, y);
	cout << res << '\n';
	for(int i = 0; i < n; i++) cout << ans[i] << ' ';
	cout << '\n';
}
int main() {
	freopen("frame.in", "r", stdin);
	freopen("frame.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
