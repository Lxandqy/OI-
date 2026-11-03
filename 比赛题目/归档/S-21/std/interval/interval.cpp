#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 3e5 + 10;
int n, q, a[maxn], b[maxn], stk[maxn], top;
ll ans[maxn];
vector<pair<int, int>> G[maxn];
struct Node {
	int l, r, cnt, add;
	ll sum;
}tree[maxn << 2];
void push_up(int i) {
	tree[i].cnt = tree[i << 1].cnt + tree[i << 1 | 1].cnt;
	tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;
}
void get(int i, int x) { tree[i].sum += 1ll * x * tree[i].cnt; tree[i].add += x; }
void push_down(int i) {
	if(!tree[i].add) return;
	get(i << 1, tree[i].add), get(i << 1 | 1, tree[i].add);
	tree[i].add = 0;
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
}
void modify(int i, int p, int x) {
	if(tree[i].l == tree[i].r) { tree[i].cnt = x; return; }
	// 先结清之前的贡献，再改变哪些位置还可作为左端点。
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(p <= mid) modify(i << 1, p, x);
	else modify(i << 1 | 1, p, x);
	push_up(i);
}
void update(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) { get(i, 1); return; }
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) update(i << 1, l, r);
	if(r > mid) update(i << 1 | 1, l, r);
	push_up(i);
}
ll query(int i, int l, int r) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i].sum;
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	ll ans = 0;
	if(l <= mid) ans += query(i << 1, l, r);
	if(r > mid) ans += query(i << 1 | 1, l, r);
	return ans;
}
int main() {
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 2; i <= n; i++) cin >> b[i];
	cin >> q;
	for(int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r;
		G[r].push_back({l, i});
	}
	build(1, 1, n);
	for(int i = 1; i < n; i++) {
		while(top && a[stk[top]] <= a[i]) modify(1, stk[top--], 0);
		stk[++top] = i; modify(1, i, 1);
		int l = 1, r = top, pos = top + 1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(a[stk[mid]] < b[i + 1]) pos = mid, r = mid - 1;
			else l = mid + 1;
		}
		if(pos <= top) update(1, stk[pos], i);
		for(auto x : G[i + 1]) ans[x.second] = query(1, x.first, i);
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
