#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 40000 + 10;
const ll inf = 4e18;
int n, q, k, pre[maxn], nxt[maxn], stk[maxn], cnt, top;
ll a[maxn];
pair<int, ll> bak[maxn];
struct Node {
	int l, r, pos;
	ll mx, add;
}tree[maxn << 2];
void push_up(int i) {
	int x = i << 1, y = i << 1 | 1;
	if(tree[x].mx < tree[y].mx) x = y;
	tree[i].mx = tree[x].mx, tree[i].pos = tree[x].pos;
}
void push_down(int i) {
	if(tree[i].add) {
		ll x = tree[i].add;
		tree[i << 1].mx += x, tree[i << 1].add += x;
		tree[i << 1 | 1].mx += x, tree[i << 1 | 1].add += x;
		tree[i].add = 0;
	}
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r, tree[i].add = 0;
	if(l == r) {
		tree[i].mx = a[l], tree[i].pos = l;
		return;
	}
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void modify(int i, int l, int r, ll x) {
	if(l <= tree[i].l && tree[i].r <= r) {
		tree[i].mx += x, tree[i].add += x;
		return;
	}
	push_down(i);
	if(tree[i << 1].r >= l) modify(i << 1, l, r, x);
	if(tree[i << 1 | 1].l <= r) modify(i << 1 | 1, l, r, x);
	push_up(i);
}
ll change(int i, int p, ll x) {
	if(tree[i].l == tree[i].r) {
		ll ret = tree[i].mx;
		tree[i].mx = x, tree[i].add = 0;
		return ret;
	}
	push_down(i);
	ll ret;
	if(p <= tree[i << 1].r) ret = change(i << 1, p, x);
	else ret = change(i << 1 | 1, p, x);
	push_up(i);
	return ret;
}
ll query(int i, int p) {
	if(tree[i].l == tree[i].r) return tree[i].mx;
	push_down(i);
	if(p <= tree[i << 1].r) return query(i << 1, p);
	return query(i << 1 | 1, p);
}
void save(int p, ll x) {
	bak[++top] = {p, change(1, p, x)};
}
void del(int p) {
	int l = pre[p], r = nxt[p];
	if(l) nxt[l] = r, stk[++cnt] = l;
	if(r <= n) pre[r] = l, stk[++cnt] = r;
	save(p, -inf);
}
ll get() {
	ll ans = 0;
	for(int i = 1; i <= k; i++) {
		int p = tree[1].pos, l = pre[p], r = nxt[p];
		ll x = tree[1].mx;
		ans += x;
		if(i == k) break;
		if(l && r <= n) {
			save(p, query(1, l) + query(1, r) - x);
			del(l), del(r);
		}
		else {
			del(p);
			if(l) del(l);
			if(r <= n) del(r);
		}
	}
	while(top) {
		change(1, bak[top].first, bak[top].second);
		top--;
	}
	while(cnt) {
		int p = stk[cnt--];
		pre[p] = p - 1, nxt[p] = p + 1;
	}
	return ans;
}
int main() {
	freopen("decorate.in", "r", stdin);
	freopen("decorate.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> q >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++) pre[i] = i - 1, nxt[i] = i + 1;
		build(1, 1, n);
		while(q--) {
			int l, r; ll x; cin >> l >> r >> x;
			modify(1, l, r, x);
			cout << get() << '\n';
		}
	}
	return 0;
}
