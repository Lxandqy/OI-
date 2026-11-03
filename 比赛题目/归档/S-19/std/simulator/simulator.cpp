#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
const ll inf = 1ll << 60;
int n, q, a[maxn];
struct Node {
	int l, r, cnt, dead, shield;
	ll mn, add;
}tree[maxn << 2];
void push_up(int i) {
	Node &u = tree[i], &l = tree[i << 1], &r = tree[i << 1 | 1];
	u.mn = min(l.mn, r.mn), u.cnt = 0;
	if(l.mn == u.mn) u.cnt += l.cnt;
	if(r.mn == u.mn) u.cnt += r.cnt;
	u.dead = l.dead + r.dead, u.shield = l.shield + r.shield;
}
void get(int i, ll x) {
	if(!tree[i].cnt) return;
	tree[i].mn += x, tree[i].add += x;
}
void push_down(int i) {
	if(!tree[i].add) return;
	get(i << 1, tree[i].add), get(i << 1 | 1, tree[i].add);
	tree[i].add = 0;
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) { tree[i].mn = a[l], tree[i].cnt = 1; return; }
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void attack(int i, int l, int r, ll x) {
	if(!tree[i].cnt) return;
	if(l <= tree[i].l && tree[i].r <= r && !tree[i].shield && tree[i].mn >= x) { get(i, -x); return; }
	if(tree[i].l == tree[i].r) {
		if(tree[i].shield) tree[i].shield--;
		else tree[i].mn = inf, tree[i].cnt = 0, tree[i].dead = 1, tree[i].add = 0;
		return;
	}
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) attack(i << 1, l, r, x);
	if(r > mid) attack(i << 1 | 1, l, r, x);
	push_up(i);
}
void modify(int i, int l, int r, ll x) {
	if(!tree[i].cnt) return;
	if(l <= tree[i].l && tree[i].r <= r) { get(i, x); return; }
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) modify(i << 1, l, r, x);
	if(r > mid) modify(i << 1 | 1, l, r, x);
	push_up(i);
}
void shield(int i, int p) {
	if(!tree[i].cnt) return;
	if(tree[i].l == tree[i].r) { tree[i].shield++; return; }
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(p <= mid) shield(i << 1, p);
	else shield(i << 1 | 1, p);
	push_up(i);
}
int query(int i, int l, int r, int op) {
	if(l <= tree[i].l && tree[i].r <= r) return op == 4 ? tree[i].dead : tree[i].mn == 0 ? tree[i].cnt : 0;
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1, ans = 0;
	if(l <= mid) ans += query(i << 1, l, r, op);
	if(r > mid) ans += query(i << 1 | 1, l, r, op);
	return ans;
}
int main() {
	freopen("simulator.in", "r", stdin);
	freopen("simulator.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n); cin >> q;
	while(q--) {
		int op, l, r, x; cin >> op >> l;
		if(op == 3) { shield(1, l); continue; }
		cin >> r;
		if(op <= 2) {
			cin >> x;
			if(op == 1) attack(1, l, r, x);
			else modify(1, l, r, x);
		}
		else cout << query(1, l, r, op) << '\n';
	}
	return 0;
}
