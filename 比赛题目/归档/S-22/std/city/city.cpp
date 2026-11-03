#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 10;
int n, m, x, q, fa[maxn], siz[maxn], id[maxn];
vector<int> G[maxn], roots;
vector<pair<int, int>> ans;
void init() {
	for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
}
int get(int u) { return u == fa[u] ? u : fa[u] = get(fa[u]); }
void merge(int u, int v) {
	u = get(u), v = get(v);
	if(u == v) return;
	if(siz[u] < siz[v]) swap(u, v);
	fa[v] = u, siz[u] += siz[v];
}
bool cmp(int u, int v) { return siz[u] < siz[v]; }
int main() {
	freopen("city.in", "r", stdin);
	freopen("city.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m >> x >> q;
	init();
	while(q--) {
		int u, v; cin >> u >> v;
		merge(u, v);
	}
	for(int i = 1; i <= n; i++) if(get(i) == i) roots.push_back(i);
	if((int)roots.size() < x) { cout << -1 << '\n'; return 0; }
	sort(roots.begin(), roots.end(), cmp);
	for(int i = 0; i < (int)roots.size(); i++) id[roots[i]] = min(i + 1, x);
	for(int i = 1; i <= n; i++) G[id[get(i)]].push_back(i);
	ll low = 0, high = 1ll * n * n;
	for(int i = 1; i <= x; i++) {
		int s = G[i].size();
		if(s > 1) low += s;
		high += 1ll * s * s;
	}
	high = high / 2 - n;
	if(m < low || m > high) { cout << -1 << '\n'; return 0; }
	for(int i = 1; i <= x; i++) {
		int s = G[i].size();
		if(s == 1) continue;
		for(int j = 0; j < s; j++) ans.push_back({G[i][j], G[i][(j + 1) % s]});
	}
	for(int i = 1; i <= x && (int)ans.size() < m; i++) {
		int s = G[i].size();
		for(int j = 0; j < s && (int)ans.size() < m; j++) {
			for(int k = 0; k < s && (int)ans.size() < m; k++) {
				if(j == k || (j + 1) % s == k) continue;
				ans.push_back({G[i][j], G[i][k]});
			}
		}
	}
	for(int i = 1; i <= x && (int)ans.size() < m; i++) {
		for(int j = i + 1; j <= x && (int)ans.size() < m; j++) {
			for(int u : G[i]) {
				if((int)ans.size() == m) break;
				for(int v : G[j]) {
					if((int)ans.size() == m) break;
					ans.push_back({u, v});
				}
			}
		}
	}
	for(auto e : ans) cout << e.first << ' ' << e.second << '\n';
	return 0;
}
