#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10, mod = 998244353;
ll fac[maxn], inv[maxn];
ll qpow(ll a, int b) {
	ll ans = 1;
	while(b) { if(b & 1) ans = ans * a % mod; a = a * a % mod, b >>= 1; }
	return ans;
}
ll C(int n, int m) {
	if(n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void init() {
	fac[0] = 1;
	for(int i = 1; i <= 200000; i++) fac[i] = fac[i - 1] * i % mod;
	inv[200000] = qpow(fac[200000], mod - 2);
	for(int i = 200000; i; i--) inv[i - 1] = inv[i] * i % mod;
}
int main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	init();
	int t; cin >> t;
	while(t--) {
		int n, m; cin >> n >> m;
		ll ans = 0;
		for(int k = 1; k * m <= n; k++) {
			int s = n - k * m;
			ans = (ans + C(s + 2 * k, 2 * k) - C(s + k, 2 * k) + mod) % mod;
		}
		cout << ans << '\n';
	}
	return 0;
}
