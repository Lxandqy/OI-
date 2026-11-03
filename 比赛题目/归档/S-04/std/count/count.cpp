#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10, mod = 998244353;
int n, len, a[maxn], num[maxn];
struct Node { int l, r, sum, mul, add; }tree[maxn << 2];
void push_up(int i) { tree[i].sum = (tree[i << 1].sum + tree[i << 1 | 1].sum) % mod; }
void calc(int i, int mul, int add) {
	tree[i].sum = (1ll * tree[i].sum * mul + 1ll * (num[tree[i].r] - num[tree[i].l - 1]) * add) % mod;
	tree[i].mul = 1ll * tree[i].mul * mul % mod;
	tree[i].add = (1ll * tree[i].add * mul + add) % mod;
}
void push_down(int i) {
	if(tree[i].mul != 1 || tree[i].add) {
		calc(i << 1, tree[i].mul, tree[i].add), calc(i << 1 | 1, tree[i].mul, tree[i].add);
		tree[i].mul = 1, tree[i].add = 0;
	}
}
void build(int i, int l, int r) {
	tree[i] = {l, r, 0, 1, 0};
	if(l == r) return;
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
}
void modify(int i, int l, int r, int mul, int add) {
	if(l <= tree[i].l && tree[i].r <= r) { calc(i, mul, add); return; }
	push_down(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) modify(i << 1, l, r, mul, add);
	if(r > mid) modify(i << 1 | 1, l, r, mul, add);
	push_up(i);
}
int get(int x) {
	int l = 1, r = len;
	while(l < r) {
		int mid = l + r >> 1;
		if(num[mid] < x) l = mid + 1;
		else r = mid;
	}
	return l;
}
int main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], num[i] = a[i];
	sort(num + 1, num + n + 1);
	len = unique(num + 1, num + n + 1) - num - 1;
	build(1, 1, len);
	for(int i = 1; i <= n; i++) {
		int sum = i == 1 ? 1 : tree[1].sum, p = get(a[i]);
		modify(1, 1, p, mod - 1, sum);
		if(p < len) modify(1, p + 1, len, 0, 0);
	}
	cout << tree[1].sum << '\n';
	return 0;
}
