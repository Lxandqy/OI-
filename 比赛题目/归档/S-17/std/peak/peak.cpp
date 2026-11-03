#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
int n, q;
ll a[maxn], b[maxn];
struct Node {
	int l, r, zero, up, down, first, last, bad;
}tree[maxn << 2];
Node merge(Node x, Node y) {
	Node z;
	z.l = x.l, z.r = y.r;
	z.zero = x.zero + y.zero;
	z.up = x.up + y.up, z.down = x.down + y.down;
	z.first = x.first, z.last = y.last;
	z.bad = x.bad + y.bad + (x.last < 0 && y.first > 0);
	return z;
}
void push_up(int i) {
	tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
}
void get(int i) {
	ll x = b[tree[i].l];
	tree[i].zero = (x == 0), tree[i].up = (x > 0), tree[i].down = (x < 0);
	tree[i].first = tree[i].last = (x > 0) - (x < 0);
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) { get(i); return; }
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void modify(int i, int pos) {
	if(tree[i].l == tree[i].r) { get(i); return; }
	if(pos <= tree[i << 1].r) modify(i << 1, pos);
	else modify(i << 1 | 1, pos);
	push_up(i);
}
Node query(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i];
	int mid = tree[i << 1].r;
	if(r <= mid) return query(i << 1, l, r);
	if(l > mid) return query(i << 1 | 1, l, r);
	return merge(query(i << 1, l, r), query(i << 1 | 1, l, r));
}
int main() {
	freopen("peak.in", "r", stdin);
	freopen("peak.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i] - a[i - 1];
	build(1, 1, n);
	cin >> q;
	while(q--) {
		int op, l, r; cin >> op >> l >> r;
		if(op == 1) {
			ll x; cin >> x;
			if(l > 1) b[l] += x, modify(1, l);
			if(r < n) b[r + 1] -= x, modify(1, r + 1);
		}
		else if(l == r) cout << 1 << '\n';
		else {
			Node ret = query(1, l + 1, r);
			if(op == 2) cout << (ret.zero == r - l) << '\n';
			if(op == 3) cout << (ret.up == r - l) << '\n';
			if(op == 4) cout << (ret.down == r - l) << '\n';
			if(op == 5) cout << (!ret.zero && ret.first > 0 && ret.last < 0 && !ret.bad) << '\n';
		}
	}
	return 0;
}
