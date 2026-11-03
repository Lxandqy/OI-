#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, k, fa[maxn], siz[maxn];
struct Edge { int u, v, w; }e[maxn];
bool cmp(Edge x, Edge y) { return x.w < y.w; }
void init() { for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1; }
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
bool merge(int x, int y) {
	x = get(x), y = get(y);
	if(x == y) return 0;
	if(siz[x] < siz[y]) swap(x, y);
	fa[y] = x, siz[x] += siz[y];
	return 1;
}
int main() {
	freopen("speed.in", "r", stdin);
	freopen("speed.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	int best = 1e9;
	for(int i = 1; i <= m; i++) {
		cin >> e[i].u >> e[i].v >> e[i].w;
		best = min(best, abs(e[i].w - k));
	}
	init();
	sort(e + 1, e + m + 1, cmp);
	ll ans = 0;
	for(int i = 1; i <= m; i++) if(merge(e[i].u, e[i].v)) ans += max(0, e[i].w - k);
	cout << (ans ? ans : best) << '\n';
	return 0;
}
