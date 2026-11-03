#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 6e5 + 10, mod = 998244353;
int n, m, k, x[maxn], y[maxn], c[maxn], num[maxn], fa[maxn], siz[maxn], val[maxn];
int get(int x) {
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = get(p), val[x] ^= val[p];
	return fa[x];
}
int id(int x, int len) {
	int l = 1, r = len;
	while(l < r) { int mid = l + r >> 1; if(num[mid] < x) l = mid + 1; else r = mid; }
	return l;
}
ll qpow(ll a, int b) {
	ll ans = 1;
	while(b) { if(b & 1) ans = ans * a % mod; a = a * a % mod, b >>= 1; }
	return ans;
}
int main() {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= k; i++) {
		cin >> x[i] >> y[i] >> c[i];
		y[i] += n;
		num[2 * i - 1] = x[i], num[2 * i] = y[i];
	}
	sort(num + 1, num + 2 * k + 1);
	int len = unique(num + 1, num + 2 * k + 1) - num - 1;
	for(int i = 1; i <= len; i++) fa[i] = i, siz[i] = 1;
	int cnt = n + m;
	for(int i = 1; i <= k; i++) {
		int u = id(x[i], len), v = id(y[i], len), a = get(u), b = get(v);
		int w = val[u] ^ val[v] ^ c[i];
		if(a == b) { if(w) { cout << 0 << '\n'; return 0; } }
		else {
			if(siz[a] > siz[b]) swap(a, b);
			fa[a] = b, siz[b] += siz[a], val[a] = w, cnt--;
		}
	}
	cout << qpow(2, cnt - 1) << '\n';
	return 0;
}
