#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, d, m, a[maxn], b[maxn], L[maxn], R[maxn];
struct Node {
	int l, r, mx, add;
}tree[maxn << 2];
void push_up(int i) {
	tree[i].mx = max(tree[i << 1].mx, tree[i << 1 | 1].mx);
}
void build(int i, int l, int r) {
	tree[i] = {l, r, 0, 0};
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
}
void push_down(int i) {
	int v = tree[i].add;
	if(!v) return;
	tree[i << 1].mx += v, tree[i << 1].add += v;
	tree[i << 1 | 1].mx += v, tree[i << 1 | 1].add += v;
	tree[i].add = 0;
}
void modify(int i, int l, int r, int v) {
	if(l <= tree[i].l && tree[i].r <= r) {
		tree[i].mx += v, tree[i].add += v;
		return;
	}
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) modify(i << 1, l, r, v);
	if(r > mid) modify(i << 1 | 1, l, r, v);
	push_up(i);
}
int get(int x) {
	int l = 1, r = m;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(b[mid] >= x) r = mid;
		else l = mid + 1;
	}
	return l;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k >> d;
		for(int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
		sort(b + 1, b + n + 1);
		m = unique(b + 1, b + n + 1) - b - 1;
		for(int i = 1; i <= n; i++) L[i] = get(a[i] - d), R[i] = get(a[i]);
		build(1, 1, m);
		ll ans = 0;
		for(int l = 1, r = 1; r <= n; r++) {
			modify(1, L[r], R[r], 1);
			while(r - l + 1 - tree[1].mx > k) {
				modify(1, L[l], R[l], -1);
				l++;
			}
			ans += r - l + 1;
		}
		cout << ans << '\n';
	}
	return 0;
}
