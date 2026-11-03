#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

const int maxn = 2e5 + 10;
int n, p[maxn << 1];
char s[maxn];
const int base = 131;
ull f1[maxn], f2[maxn], h[maxn];
vector<int> G[maxn];
struct Node {
	int l, r, cnt[2];
	ll sum[2];
}tree[maxn << 2];

ull cal(ull *f, int l, int r) {
	return f[r] - f[l - 1] * h[r - l + 1];
}
bool check(int l, int r) {
	if(l >= r) return 1;
	return cal(f1, l, r) == cal(f2, n - r + 1, n - l + 1);
}
void init() {
	h[0] = 1, f1[0] = f2[0] = 0;
	for(int i = 1; i <= n; i++) {
		h[i] = h[i - 1] * base;
		f1[i] = f1[i - 1] * base + s[i];
		f2[i] = f2[i - 1] * base + s[n - i + 1];
	}
	p[0] = p[n * 2] = 0;
	for(int i = 1; i < n * 2; i++) {
		int x = (i + 1) / 2, op = i & 1;
		int l = 0, r = min(x - op, n - x);
		while(l < r) {
			int mid = (l + r + 1) >> 1;
			if(check(x - mid + 1 - op, x + mid)) l = mid;
			else r = mid - 1;
		}
		p[i] = l * 2 + op;
	}
}
void push_up(int i) {
	for(int j = 0; j < 2; j++) {
		tree[i].cnt[j] = tree[i << 1].cnt[j] + tree[i << 1 | 1].cnt[j];
		tree[i].sum[j] = tree[i << 1].sum[j] + tree[i << 1 | 1].sum[j];
	}
}
void build(int i, int L, int R) {
	tree[i].l = L, tree[i].r = R;
	for(int j = 0; j < 2; j++) tree[i].cnt[j] = tree[i].sum[j] = 0;
	if(L == R) return;
	int mid = (L + R) >> 1;
	build(i << 1, L, mid), build(i << 1 | 1, mid + 1, R);
}
void modify(int i, int x) {
	if(tree[i].l == tree[i].r) {
		tree[i].cnt[x & 1]++;
		tree[i].sum[x & 1] += x;
		return;
	}
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(x <= mid) modify(i << 1, x);
	else modify(i << 1 | 1, x);
	push_up(i);
}
pair<int, ll> query(int i, int L, int R, int op) {
	if(L <= tree[i].l && tree[i].r <= R) return {tree[i].cnt[op], tree[i].sum[op]};
	int mid = (tree[i].l + tree[i].r) >> 1;
	pair<int, ll> res = {0, 0};
	if(L <= mid) res = query(i << 1, L, R, op);
	if(R > mid) {
		auto ret = query(i << 1 | 1, L, R, op);
		res.first += ret.first, res.second += ret.second;
	}
	return res;
}
ll solve() {
	if(n == 1) return 0;
	init();
	int k = 0;
	while(k < n / 2 && s[k + 1] == s[n - k]) k++;
	for(int i = 0; i <= n; i++) G[i].clear();
	for(int d = 1; d < n; d++) G[p[n + d]].push_back(d);
	build(1, 1, n - 1);
	ll ans = 0;
	for(int a = n - 1; a >= 1; a--) {
		for(int d : G[a]) modify(1, d);
		int L = max(1, n - k * 2 - a);
		int R = min(n - a, p[n - a]);
		if(L > R) continue;
		auto ret = query(1, L, R, (n - a) & 1);
		// 同一分法可以裁下左段或右段，两种裁法共贡献 a+d。
		ans += 1ll * a * ret.first + ret.second;
	}
	if(k == n / 2) {
		ll m = (n - 1) / 2;
		ans += m * n - m * (m + 1);
	}
	return ans;
}
int main() {
	freopen("bookmark.in", "r", stdin);
	freopen("bookmark.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> s + 1;
		cout << solve() << '\n';
	}
	return 0;
}
