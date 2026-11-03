#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10, mod = 1e9 + 7, inf = 2e9;
int n, m, a[maxn];
struct Node {
	int l, r, mn, mx, sum, sum2, tag;
	bool rev;
}tree[maxn << 2];
void push_up(int i) {
	tree[i].mn = min(tree[i << 1].mn, tree[i << 1 | 1].mn);
	tree[i].mx = max(tree[i << 1].mx, tree[i << 1 | 1].mx);
	tree[i].sum = (tree[i << 1].sum + tree[i << 1 | 1].sum) % mod;
	tree[i].sum2 = (tree[i << 1].sum2 + tree[i << 1 | 1].sum2) % mod;
}
void cover(int i, int x) {
	ll val = (x + mod) % mod, len = tree[i].r - tree[i].l + 1;
	tree[i].mn = tree[i].mx = tree[i].tag = x, tree[i].rev = 0;
	tree[i].sum = val * len % mod, tree[i].sum2 = val * val % mod * len % mod;
}
void reverse(int i) {
	swap(tree[i].mn, tree[i].mx);
	tree[i].mn = -tree[i].mn, tree[i].mx = -tree[i].mx;
	tree[i].sum = (mod - tree[i].sum) % mod;
	if(tree[i].tag != inf) tree[i].tag = -tree[i].tag;
	else tree[i].rev ^= 1;
}
void push_down(int i) {
	if(tree[i].tag != inf) {
		cover(i << 1, tree[i].tag), cover(i << 1 | 1, tree[i].tag);
		tree[i].tag = inf;
	}
	if(tree[i].rev) {
		reverse(i << 1), reverse(i << 1 | 1);
		tree[i].rev = 0;
	}
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r, tree[i].tag = inf;
	if(l == r) { cover(i, a[l]); return; }
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
int calc(int x, int p) {
	int ans = x / p;
	if(x % p && (x < 0) != (p < 0)) ans--;
	return ans;
}
void divide(int i, int l, int r, int p) {
	if(p == 1) return;
	if(l <= tree[i].l && tree[i].r <= r) {
		if(p == -1) { reverse(i); return; }
		if(tree[i].mn == tree[i].mx) { cover(i, calc(tree[i].mn, p)); return; }
		if(tree[i].mn >= -1 && tree[i].mx <= 1) {
			if(tree[i].mx <= 0) {
				if(p < 0) cover(i, 0);
				return;
			}
			if(tree[i].mn >= 0) {
				if(p < 0) reverse(i);
				else cover(i, 0);
				return;
			}
		}
	}
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) divide(i << 1, l, r, p);
	if(r > mid) divide(i << 1 | 1, l, r, p);
	push_up(i);
}
void modify(int i, int pos, int val) {
	if(tree[i].l == tree[i].r) { cover(i, val); return; }
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(pos <= mid) modify(i << 1, pos, val);
	else modify(i << 1 | 1, pos, val);
	push_up(i);
}
int query(int i, int l, int r, int opt) {
	if(l <= tree[i].l && tree[i].r <= r) return opt == 1 ? tree[i].sum : tree[i].sum2;
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1, ans = 0;
	if(l <= mid) ans = query(i << 1, l, r, opt);
	if(r > mid) ans = (ans + query(i << 1 | 1, l, r, opt)) % mod;
	return ans;
}
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	while(m--) {
		int opt, l, r; cin >> opt >> l >> r;
		if(opt <= 2) cout << query(1, l, r, opt) << '\n';
		else if(opt == 3) { int p; cin >> p; divide(1, l, r, p); }
		else modify(1, l, r);
	}
	return 0;
}
