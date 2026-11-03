#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn = 5e5 + 10, p = 131, inf = 1e9;
int n, m, q, pos[maxn], tim[maxn], ans[maxn];
char s[maxn * 2];
ull f[maxn * 2], h[maxn];
struct Item { int t, pos, val; }a[maxn];
struct Query { int k, l, r, id; }b[maxn];
struct Node { int l, r, mn; }tree[maxn << 2];
void init() {
	h[0] = 1;
	for(int i = 1; i <= n; i++) h[i] = h[i - 1] * p;
}
ull cal(int l, int r) { return f[r] - f[l - 1] * h[r - l + 1]; }
bool check(int k, int len) {
	int l = pos[len], r = l + len - 1;
	return cal(l, r - k) == cal(l + k, r);
}
int get(int k) {
	int l = k, r = n, ans = k;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(k, mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}
void push_up(int i) { tree[i].mn = min(tree[i << 1].mn, tree[i << 1 | 1].mn); }
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r, tree[i].mn = inf;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
}
void modify(int i, int x, int v) {
	if(tree[i].l == tree[i].r) { tree[i].mn = v; return; }
	if(x <= tree[i << 1].r) modify(i << 1, x, v);
	else modify(i << 1 | 1, x, v);
	push_up(i);
}
int query(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i].mn;
	int ans = inf;
	if(l <= tree[i << 1].r) ans = min(ans, query(i << 1, l, r));
	if(r >= tree[i << 1 | 1].l) ans = min(ans, query(i << 1 | 1, l, r));
	return ans;
}
bool cmp1(Item x, Item y) { return x.t > y.t; }
bool cmp2(Query x, Query y) { return x.k > y.k; }
int main() {
	freopen("period.in", "r", stdin);
	freopen("period.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string d;
	cin >> n >> d;
	int l = n + 1, r = n;
	for(int i = 1; i <= n; i++) {
		if(d[i - 1] >= 'a' && d[i - 1] <= 'z') s[--l] = d[i - 1];
		else s[++r] = d[i - 1] - 'A' + 'a';
		pos[i] = l;
	}
	init();
	for(int i = l; i <= r; i++) f[i] = f[i - 1] * p + s[i];
	for(int i = 1; i <= n; i++) tim[i] = get(i);
	cin >> m;
	for(int i = 1; i <= m; i++) { int x; cin >> x; a[i] = {tim[x], i, x}; }
	cin >> q;
	for(int i = 1; i <= q; i++) { cin >> b[i].k >> b[i].l >> b[i].r; b[i].id = i; }
	sort(a + 1, a + m + 1, cmp1), sort(b + 1, b + q + 1, cmp2);
	build(1, 1, m);
	int j = 1;
	for(int i = 1; i <= q; i++) {
		while(j <= m && a[j].t >= b[i].k) { modify(1, a[j].pos, a[j].val); j++; }
		int res = query(1, b[i].l, b[i].r);
		ans[b[i].id] = res <= b[i].k ? res : -1;
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
