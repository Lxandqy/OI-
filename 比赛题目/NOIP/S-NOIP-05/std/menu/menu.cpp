#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10, inf = 1e9;
int n, b[maxn], cnt[maxn], h[maxn], ans[maxn], val[maxn << 2];
int pos, choice;
struct Order {
	int l, r, c;
} a[maxn];
struct Node {
	int l, r, mn, add;
} tree[maxn << 2];
priority_queue<int, vector<int>, greater<int>> q[maxn];
bool cmp(Order x, Order y) {
	return x.l < y.l;
}
void push_up(int i) {
	tree[i].mn = min(tree[i << 1].mn, tree[i << 1 | 1].mn);
}
void push_down(int i) {
	if(!tree[i].add) return;
	for(int j = i << 1; j <= (i << 1 | 1); j++)
		tree[j].mn += tree[i].add, tree[j].add += tree[i].add;
	tree[i].add = 0;
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r, tree[i].add = 0;
	if(l == r) {
		tree[i].mn = h[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void modify(int i, int l, int r, int v) {
	if(l <= tree[i].l && tree[i].r <= r) {
		tree[i].mn += v, tree[i].add += v;
		return;
	}
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) modify(i << 1, l, r, v);
	if(r > mid) modify(i << 1 | 1, l, r, v);
	push_up(i);
}
int get(int i) {
	if(tree[i].l == tree[i].r) return tree[i].l;
	push_down(i);
	if(!tree[i << 1].mn) return get(i << 1);
	return get(i << 1 | 1);
}
void update(int i, int l, int r, int x) {
	if(l == r) {
		val[i] = q[x].empty() ? inf : q[x].top();
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) update(i << 1, l, mid, x);
	else update(i << 1 | 1, mid + 1, r, x);
	val[i] = min(val[i << 1], val[i << 1 | 1]);
}
int query(int i, int l, int r, int x, int t) {
	if(r < x || val[i] > t) return 0;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int res = query(i << 1, l, mid, x, t);
	if(res) return res;
	return query(i << 1 | 1, mid + 1, r, x, t);
}
void work(int flag) {
	for(int i = 1; i <= n; i++) while(!q[i].empty()) q[i].pop();
	fill(val, val + (n << 2) + 5, inf);
	build(1, 1, n);
	int j = 1;
	for(int i = 1; i <= n; i++) {
		while(j <= n && a[j].l <= i) {
			int c = a[j].c;
			q[c].push(a[j].r), update(1, 1, n, c);
			j++;
		}
		int t = get(1), c;
		if(!flag) {
			int x = query(1, 1, n, b[i] + 1, t);
			if(x) pos = i, choice = x;
			c = b[i];
		}
		else {
			if(i < pos) c = b[i];
			else if(i == pos) c = choice;
			else c = query(1, 1, n, 1, t);
			ans[i] = c;
		}
		// 同一口味先做最早截止的订单，保留后面安排的余地。
		int r = q[c].top();
		q[c].pop(), update(1, 1, n, c);
		modify(1, i, i, inf);
		if(i + 1 < r) modify(1, i + 1, r - 1, -1);
	}
}
void solve() {
	cin >> n;
	fill(cnt, cnt + n + 1, 0);
	for(int i = 1; i <= n; i++) {
		cin >> a[i].l >> a[i].r >> a[i].c;
		cnt[a[i].r]++;
	}
	for(int i = 1; i <= n; i++) cin >> b[i];
	for(int i = 1, sum = 0; i <= n; i++) sum += cnt[i], h[i] = i - sum;
	sort(a + 1, a + n + 1, cmp);
	pos = choice = 0;
	work(0);
	if(!pos) {
		cout << -1 << '\n';
		return;
	}
	work(1);
	for(int i = 1; i <= n; i++) cout << ans[i] << (i == n ? '\n' : ' ');
}
int main() {
	freopen("menu.in", "r", stdin);
	freopen("menu.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
