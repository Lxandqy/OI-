#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
typedef __int128 int128;
const int128 inf = (int128)1 << 120;
const ll base = 100000;
int n, k, lmt[maxn], rmt[maxn];
ll a[maxn], b[maxn], sa[maxn], sb[maxn];
int128 f[2][maxn], g[maxn], c[maxn];
struct Node {
	int l, r;
	int128 mx;
}tree[maxn << 2];
void push_up(int i) {
	tree[i].mx = max(tree[i << 1].mx, tree[i << 1 | 1].mx);
}
void build(int i, int L, int R) {
	tree[i].l = L, tree[i].r = R;
	if(L == R) {
		tree[i].mx = g[L];
		return;
	}
	int mid = L + R >> 1;
	build(i << 1, L, mid);
	build(i << 1 | 1, mid + 1, R);
	push_up(i);
}
int128 query(int i, int L, int R) {
	if(L <= tree[i].l && tree[i].r <= R) return tree[i].mx;
	int128 res = -inf;
	if(tree[i << 1].r >= L) res = max(res, query(i << 1, L, R));
	if(tree[i << 1 | 1].l <= R) res = max(res, query(i << 1 | 1, L, R));
	return res;
}
bool check(ll x) {
	for(int i = 0; i <= n; i++) {
		c[i] = (int128)sa[i] * base - (int128)x * sb[i];
		f[0][i] = 0;
	}
	for(int j = 1; j <= k; j++) {
		int now = j & 1, pre = now ^ 1;
		for(int i = 0; i < n; i++) g[i] = f[pre][i] - c[i];
		build(1, 0, n - 1);
		f[now][0] = -inf;
		for(int i = 1; i <= n; i++) {
			f[now][i] = f[now][i - 1];
			int128 v = query(1, i - rmt[i], i - lmt[i]);
			if(v > -inf / 2) f[now][i] = max(f[now][i], v + c[i]);
		}
	}
	return f[k & 1][n] >= 0;
}
int main() {
	freopen("fraction.in", "r", stdin);
	freopen("fraction.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	ll l = 0, r = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> lmt[i] >> rmt[i];
		sa[i] = sa[i - 1] + a[i], sb[i] = sb[i - 1] + b[i];
		r = max(r, a[i] * base / b[i]);
	}
	while(l < r) {
		ll mid = (l + r + 1) >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l / base << '.' << setw(5) << setfill('0') << l % base << '\n';
	return 0;
}
