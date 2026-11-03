#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6 + 10;
int n, q, cnt, tot, head[maxn], h1[maxn], h2[maxn], last[maxn], ans[maxn];
struct Edge { int v, nxt; }e[maxn];
struct Node { int v, nxt, pre; }a[maxn];
struct Query { int y, nxt; }b[maxn];
void add(int u, int v) {
	e[++cnt] = {v, head[u]}, head[u] = cnt;
}
void dfs(int u) {
	for(int i = h1[u]; i; i = a[i].nxt) a[i].pre = last[a[i].v], last[a[i].v] = u;
	for(int i = h2[u]; i; i = b[i].nxt) ans[i] = last[b[i].y] ? last[b[i].y] : -1;
	for(int i = head[u]; i; i = e[i].nxt) dfs(e[i].v);
	for(int i = h1[u]; i; i = a[i].nxt) last[a[i].v] = a[i].pre;
}
int main() {
	freopen("slay.in", "r", stdin);
	freopen("slay.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n;
	for(int i = 2; i <= n; i++) {
		int p; cin >> p;
		add(p, i);
	}
	for(int i = 1; i <= n; i++) {
		int k; cin >> k;
		while(k--) {
			int x; cin >> x;
			a[++tot] = {x, h1[i], 0}, h1[i] = tot;
		}
	}
	cin >> q;
	for(int i = 1; i <= q; i++) {
		int x, y; cin >> x >> y;
		b[i] = {y, h2[x]}, h2[x] = i;
	}
	dfs(1);
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
