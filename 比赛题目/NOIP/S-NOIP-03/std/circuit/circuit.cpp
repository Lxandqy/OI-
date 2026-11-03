#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 200010;
const int lg = 19;
int n, q, s[maxn], f[2][lg][maxn];
ll a[2][maxn], g[2][lg][maxn], sum[maxn];

void init(int k) {
	int top = 0;
	for(int i = n; i >= 1; i--) {
		while(top && a[k][s[top]] >= a[k][i]) top--;
		f[k][0][i] = top ? s[top] : n + 1;
		g[k][0][i] = a[k][i] * (f[k][0][i] - i);
		s[++top] = i;
	}
	for(int j = 0; j < lg; j++) f[k][j][n + 1] = n + 1;
	// g[k][j][i] 记录这次倍增跳过的各段贡献之和。
	for(int j = 1; j < lg; j++) {
		for(int i = 1; i <= n; i++) {
			int u = f[k][j - 1][i];
			f[k][j][i] = f[k][j - 1][u];
			g[k][j][i] = g[k][j - 1][i] + g[k][j - 1][u];
		}
	}
}

ll getmin(int l, int r) {
	for(int i = lg - 1; i >= 0; i--) {
		if(f[0][i][l] <= r) l = f[0][i][l];
	}
	return a[0][l];
}

ll query(int k, int l, int r, ll h) {
	int u = l;
	ll ans = 0;
	// 前缀最小值不小于 h 的这些位置，每个位置的贡献都是 h。
	if(a[k][u] >= h) {
		for(int i = lg - 1; i >= 0; i--) {
			int v = f[k][i][u];
			if(v <= r && a[k][v] >= h) u = v;
		}
		int v = f[k][0][u];
		if(v > r) return h * (r - l + 1);
		ans = h * (v - l);
		u = v;
	}
	for(int i = lg - 1; i >= 0; i--) {
		if(f[k][i][u] <= r) {
			ans += g[k][i][u];
			u = f[k][i][u];
		}
	}
	return ans + a[k][u] * (r - u + 1);
}

int main() {
	freopen("circuit.in", "r", stdin);
	freopen("circuit.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		ll x;
		cin >> x;
		a[0][i + 1] = a[0][i] + x;
	}
	n++;
	for(int i = 1; i <= n; i++) {
		a[1][i] = a[0][n - i + 1];
		sum[i] = sum[i - 1] + a[0][i];
	}
	init(0), init(1);
	while(q--) {
		int l, r;
		cin >> l >> r;
		r++;
		ll v = a[0][r] - a[0][l], mn = getmin(l, r);
		ll ans = sum[r - 1] - sum[l - 1];
		if(v >= 0) {
			ll h = mn + v;
			// 在反向数组上统计后缀最小值，减去右端点多算的一项。
			ans -= query(1, n - r + 1, n - l + 1, h) - min(a[0][r], h);
		}
		else ans -= v * (r - l) + query(0, l, r - 1, mn - v);
		cout << ans << '\n';
	}
	return 0;
}
