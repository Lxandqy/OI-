#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
const ll inf = 4000000000000000000ll;
int n, m;
ll x[maxn], l[maxn], r[maxn], c[maxn], a[maxn];
struct Node {
	int l, r;
	// f(t)：休息车停在 t 的最低费用；分别维护 f(t)、f(t)-t、f(t)+t 的最小值。
	ll mn, pre, suf, add;
}tree[maxn << 2];
void push_up(int i) {
	tree[i].mn = min(tree[i << 1].mn, tree[i << 1 | 1].mn);
	tree[i].pre = min(tree[i << 1].pre, tree[i << 1 | 1].pre);
	tree[i].suf = min(tree[i << 1].suf, tree[i << 1 | 1].suf);
}
void calc(int i, ll k) {
	tree[i].mn += k;
	tree[i].pre += k;
	tree[i].suf += k;
	tree[i].add += k;
}
void push_down(int i) {
	if(tree[i].add) {
		calc(i << 1, tree[i].add);
		calc(i << 1 | 1, tree[i].add);
		tree[i].add = 0;
	}
}
void build(int i, int L, int R) {
	tree[i].l = L, tree[i].r = R;
	if(L == R) {
		tree[i].mn = a[L] == 0 ? 0 : inf;
		tree[i].pre = tree[i].mn - a[L];
		tree[i].suf = tree[i].mn + a[L];
		return;
	}
	int mid = L + R >> 1;
	build(i << 1, L, mid), build(i << 1 | 1, mid + 1, R);
	push_up(i);
}
void modify1(int i, int L, int R, ll k) {
	if(L <= tree[i].l && tree[i].r <= R) {
		calc(i, k);
		return;
	}
	push_down(i);
	if(tree[i << 1].r >= L) modify1(i << 1, L, R, k);
	if(tree[i << 1 | 1].l <= R) modify1(i << 1 | 1, L, R, k);
	push_up(i);
}
// 新方案落在同一个休息位置，只保留较小费用。
void modify2(int i, int x, ll k) {
	if(tree[i].l == tree[i].r) {
		tree[i].mn = min(tree[i].mn, k);
		tree[i].pre = tree[i].mn - a[x];
		tree[i].suf = tree[i].mn + a[x];
		return;
	}
	push_down(i);
	if(tree[i << 1].r >= x) modify2(i << 1, x, k);
	else modify2(i << 1 | 1, x, k);
	push_up(i);
}
ll query(int i, int L, int R, int opt) {
	if(L <= tree[i].l && tree[i].r <= R) return opt ? tree[i].suf : tree[i].pre;
	push_down(i);
	ll ret = inf;
	if(tree[i << 1].r >= L) ret = min(ret, query(i << 1, L, R, opt));
	if(tree[i << 1 | 1].l <= R) ret = min(ret, query(i << 1 | 1, L, R, opt));
	return ret;
}
int main() {
	freopen("foodcart.in", "r", stdin);
	freopen("foodcart.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	// 车只会停在起点或某场活动的位置，停车区间端点不用加入离散化。
	a[++m] = 0;
	for(int i = 1; i <= n; i++) {
		cin >> x[i] >> l[i] >> r[i] >> c[i];
		a[++m] = x[i];
	}
	sort(a + 1, a + m + 1);
	m = unique(a + 1, a + m + 1) - a - 1;
	build(1, 1, m);
	for(int i = 1; i <= n; i++) {
		int p = lower_bound(a + 1, a + m + 1, x[i]) - a;
		// 换休息车出发：拆开绝对值，先从旧状态求 min(f(t)+|t-x[i]|)。
		ll val = min(query(1, 1, p, 0) + x[i], query(1, p, m, 1) - x[i]);
		// 原来的上场车留在 x[i-1]，它可能还要交停车费。
		if(l[i] <= x[i - 1] && x[i - 1] <= r[i]) val += c[i];
		// 继续派上场车：所有状态加路费，停车区间内的状态再加停车费。
		calc(1, abs(x[i] - x[i - 1]));
		int L = lower_bound(a + 1, a + m + 1, l[i]) - a;
		int R = upper_bound(a + 1, a + m + 1, r[i]) - a - 1;
		if(L <= R) modify1(1, L, R, c[i]);
		// 换车方案的休息位置变成 x[i-1]；val 必须在上面的区间加之前算好。
		p = lower_bound(a + 1, a + m + 1, x[i - 1]) - a;
		modify2(1, p, val);
	}
	cout << tree[1].mn << '\n';
	return 0;
}
