#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 10;
int n, k, m, a[maxn];
struct Node {
	int l, r, cnt, ans;
	int pre[31], suf[31];
}tree[maxn << 2];
void push_up(int i) {
	Node &u = tree[i], &x = tree[i << 1], &y = tree[i << 1 | 1];
	u.ans = min(x.ans, y.ans);
	int pos[61], cnt[31] = {}, tot = 0, have = 0;
	for(int j = x.cnt; j >= 1; j--) pos[++tot] = x.suf[j];
	for(int j = 1; j <= y.cnt; j++) pos[++tot] = y.pre[j];
	for(int l = 1, r = 1; r <= tot; r++) {
		if(!cnt[a[pos[r]]]++) have++;
		while(have == k) {
			u.ans = min(u.ans, pos[r] - pos[l] + 1);
			if(!--cnt[a[pos[l++]]]) have--;
		}
	}
	int mask = 0;
	u.cnt = 0;
	for(int j = 1; j <= x.cnt; j++) {
		int p = x.pre[j];
		u.pre[++u.cnt] = p, mask |= 1 << (a[p] - 1);
	}
	for(int j = 1; j <= y.cnt; j++) {
		int p = y.pre[j];
		if(!(mask >> (a[p] - 1) & 1)) {
			u.pre[++u.cnt] = p, mask |= 1 << (a[p] - 1);
		}
	}
	mask = 0, tot = 0;
	for(int j = 1; j <= y.cnt; j++) {
		int p = y.suf[j];
		u.suf[++tot] = p, mask |= 1 << (a[p] - 1);
	}
	for(int j = 1; j <= x.cnt; j++) {
		int p = x.suf[j];
		if(!(mask >> (a[p] - 1) & 1)) {
			u.suf[++tot] = p, mask |= 1 << (a[p] - 1);
		}
	}
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) {
		tree[i].cnt = 1, tree[i].pre[1] = tree[i].suf[1] = l;
		tree[i].ans = (k == 1 ? 1 : maxn);
		return;
	}
	int mid = l + r >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void modify(int i, int p, int v) {
	if(tree[i].l == tree[i].r) {
		a[p] = v;
		return;
	}
	int mid = tree[i].l + tree[i].r >> 1;
	if(p <= mid) modify(i << 1, p, v);
	else modify(i << 1 | 1, p, v);
	push_up(i);
}
int main() {
	freopen("truth.in", "r", stdin);
	freopen("truth.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	while(m--) {
		int op; cin >> op;
		if(op == 1) {
			int p, v; cin >> p >> v;
			modify(1, p, v);
		}
		else cout << (tree[1].ans == maxn ? -1 : tree[1].ans) << '\n';
	}
	return 0;
}
