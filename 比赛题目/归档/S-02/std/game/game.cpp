#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 10;
int n, m, a[maxn], id[maxn], L[maxn], R[maxn], pre[maxn], nxt[maxn];
int f[maxn][20];
ll sum[maxn][20];
struct Node { int l, r, val; }tree[maxn << 2];
int mode;
int best(int x, int y) {
	if(!x) return y;
	if(!y) return x;
	return (a[x] < a[y]) == (mode == 1) ? x : y;
}
void build(int i, int l, int r) {
	tree[i] = {l, r, 0};
	if(l == r) return;
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
}
void modify(int i, int x) {
	if(tree[i].l == tree[i].r) { tree[i].val = x; return; }
	int mid = tree[i].l + tree[i].r >> 1;
	if(x <= mid) modify(i << 1, x);
	else modify(i << 1 | 1, x);
	tree[i].val = best(tree[i << 1].val, tree[i << 1 | 1].val);
}
int query(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i].val;
	int mid = tree[i].l + tree[i].r >> 1, res = 0;
	if(l <= mid) res = best(res, query(i << 1, l, r));
	if(r > mid) res = best(res, query(i << 1 | 1, l, r));
	return res;
}
ll get(int u, int k) {
	ll ans = 0;
	for(int j = 0; k; j++, k >>= 1) if(k & 1) ans += sum[u][j], u = f[u][j];
	return ans;
}
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], id[i] = i;
	for(int i = 1; i <= n; i++) cin >> L[i] >> R[i];
	sort(id + 1, id + n + 1, [](int x, int y) { return a[x] < a[y]; });
	mode = 0, build(1, 1, n);
	for(int i = 1; i <= n; i++) {
		int u = id[i]; pre[u] = query(1, L[u], R[u]); modify(1, u);
	}
	mode = 1, build(1, 1, n);
	for(int i = n; i >= 1; i--) {
		int u = id[i]; nxt[u] = query(1, L[u], R[u]); modify(1, u);
	}
	for(int i = 1; i <= n; i++) {
		int x = pre[i], y = nxt[i];
		if(!x || (y && a[i] - a[x] > a[y] - a[i])) x = y;
		f[i][0] = x, sum[i][0] = abs(a[i] - a[x]);
	}
	for(int j = 1; j <= 19; j++) for(int i = 1; i <= n; i++) {
		int u = f[i][j - 1];
		f[i][j] = f[u][j - 1], sum[i][j] = sum[i][j - 1] + sum[u][j - 1];
	}
	cin >> m;
	while(m--) {
		int u, v, k; cin >> u >> v >> k;
		ll x = get(u, k), y = get(v, k);
		cout << (x > y ? "win" : x == y ? "draw" : "lose") << '\n';
	}
	return 0;
}
