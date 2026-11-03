#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e4 + 10;
int n, p[maxn], pos[maxn], fa[maxn], siz[maxn];
struct Edge { int u, v; };
vector<Edge> G[maxn];
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
bool merge(int u, int v) {
	u = get(u), v = get(v);
	if(u == v) return 0;
	if(siz[u] < siz[v]) swap(u, v);
	fa[v] = u, siz[u] += siz[v];
	return 1;
}
int main() {
	freopen("pmst.in", "r", stdin);
	freopen("pmst.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) { cin >> p[i]; pos[p[i]] = i; fa[i] = i, siz[i] = 1; }
	int lim = sqrt(n) + 1;
	for(int i = 1; i <= n; i++) {
		for(int j = max(1, i - lim); j < i; j++) {
			int w = (i - j) * abs(p[i] - p[j]);
			if(w < n) G[w].push_back({i, j});
		}
		for(int x = max(1, p[i] - lim); x < p[i]; x++) {
			int j = pos[x];
			if(abs(i - j) <= lim) continue;
			int w = (p[i] - x) * abs(i - j);
			if(w < n) G[w].push_back({i, j});
		}
	}
	ll ans = 0;
	int cnt = 0;
	for(int w = 1; w < n && cnt < n - 1; w++) for(auto e : G[w]) if(merge(e.u, e.v)) {
		ans += w;
		if(++cnt == n - 1) break;
	}
	cout << ans << '\n';
	return 0;
}
