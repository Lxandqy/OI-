#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) ((x) & (-x))
using namespace std;
const int maxn = 2e5 + 10;
struct Node {
	int mx, mn;
	ll sum;
}L[maxn], R[maxn];
int n, a[maxn], c[maxn], pos[maxn], tot;
ll k, h[maxn];
ll f(int x) {
	return 1ll * x * (x + 1) / 2;
}
void modify(int x, int v) {
	for(int i = x; i <= tot; i += lowbit(i)) c[i] += v;
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= lowbit(i)) res += c[i];
	return res;
}
int get(ll x) {
	int l = 1, r = tot, res = tot + 1;
	while(l <= r) {
		int mid = l + r >> 1;
		if(h[mid] >= x) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}
ll cal(Node *x, Node *y, int n, int m) {
	for(int i = 1; i <= m; i++) h[i] = f(y[i].mn - 1) + y[i].sum;
	sort(h + 1, h + m + 1);
	tot = unique(h + 1, h + m + 1) - h - 1;
	for(int i = 1; i <= tot; i++) c[i] = 0;
	for(int i = 1; i <= m; i++) pos[i] = get(f(y[i].mn - 1) + y[i].sum);
	ll ans = 0;
	int l = 1, r = 0;
	for(int i = 1; i <= n; i++) {
		while(r < m && y[r + 1].mx < x[i].mx) {
			r++;
			if(r >= l) modify(pos[r], 1);
		}
		while(l <= m && y[l].mn > x[i].mn) {
			if(l <= r) modify(pos[l], -1);
			l++;
		}
		if(l <= r) {
			ll val = f(x[i].mx) - x[i].sum - k;
			ans += r - l + 1 - query(get(val) - 1);
		}
		int len = min(r, l - 1);
		ll val = f(x[i].mx) - f(x[i].mn - 1) - x[i].sum - k;
		int ql = 1, qr = len, res = len + 1;
		while(ql <= qr) {
			int mid = ql + qr >> 1;
			if(y[mid].sum >= val) res = mid, qr = mid - 1;
			else ql = mid + 1;
		}
		ans += len - res + 1;
	}
	return ans;
}
ll solve(int l, int r) {
	if(l == r) return 1;
	int mid = l + r >> 1;
	ll ans = solve(l, mid) + solve(mid + 1, r);
	int n = 0, m = 0;
	L[0] = R[0] = {0, 1000000001, 0};
	for(int i = mid; i >= l; i--) {
		n++;
		L[n].mx = max(L[n - 1].mx, a[i]);
		L[n].mn = min(L[n - 1].mn, a[i]);
		L[n].sum = L[n - 1].sum + a[i];
	}
	for(int i = mid + 1; i <= r; i++) {
		m++;
		R[m].mx = max(R[m - 1].mx, a[i]);
		R[m].mn = min(R[m - 1].mn, a[i]);
		R[m].sum = R[m - 1].sum + a[i];
	}
	ans += cal(L, R, n, m);
	ans += cal(R, L, m, n);
	return ans;
}
int main() {
	freopen("album.in", "r", stdin);
	freopen("album.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		cout << solve(1, n) << '\n';
	}
	return 0;
}
