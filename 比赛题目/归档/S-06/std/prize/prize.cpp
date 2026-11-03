#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, a[maxn], num[maxn];
struct Node { int l, r, cnt, add; ll sum; }tree[maxn << 2];
void calc(int i, int k) { tree[i].sum += 1ll * tree[i].cnt * k, tree[i].add += k; }
void push_down(int i) {
	if(tree[i].add) {
		calc(i << 1, tree[i].add), calc(i << 1 | 1, tree[i].add);
		tree[i].add = 0;
	}
}
void push_up(int i) {
	tree[i].cnt = tree[i << 1].cnt + tree[i << 1 | 1].cnt;
	tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) return;
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
}
void insert(int i, int x) {
	if(tree[i].l == tree[i].r) { tree[i].cnt = 1; return; }
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(x <= mid) insert(i << 1, x);
	else insert(i << 1 | 1, x);
	push_up(i);
}
void modify(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) { calc(i, 1); return; }
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) modify(i << 1, l, r);
	if(r > mid) modify(i << 1 | 1, l, r);
	push_up(i);
}
ll query(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i].sum;
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1;
	ll res = 0;
	if(l <= mid) res += query(i << 1, l, r);
	if(r > mid) res += query(i << 1 | 1, l, r);
	return res;
}
int get(int x) {
	int l = 1, r = n;
	while(l < r) { int mid = l + r >> 1; if(num[mid] < x) l = mid + 1; else r = mid; }
	return l;
}
int main() {
	freopen("prize.in", "r", stdin);
	freopen("prize.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], num[i] = a[i];
	sort(num + 1, num + n + 1);
	build(1, 1, n);
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		int x = get(a[i]);
		if(x > 1) ans += query(1, 1, x - 1);
		if(x < n) modify(1, x + 1, n);
		insert(1, x);
	}
	cout << ans << '\n';
	return 0;
}
