#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
int n, m, a[maxn], b[maxn], f[maxn];
ll k;
bool check(int d) {
	ll x = n, y = 0;
	for(int j = d; j <= m; j += d) {
		if(f[j - 1] > j - d) return 0;
		x += a[j + 1], y += b[j];
	}
	if(f[m] > m / d * d) return 0;
	return x <= k && k <= y;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		m = 0;
		for(int i = 1; i <= n; i++) {
			int l, r; cin >> l >> r;
			a[l]++, b[r]++, f[r] = max(f[r], l);
			m = max(m, r);
		}
		for(int i = m; i >= 1; i--) a[i] += a[i + 1], b[i] += b[i + 1];
		for(int i = 1; i <= m; i++) f[i] = max(f[i], f[i - 1]);
		int ans = -1;
		for(int i = m; i >= 1; i--) {
			if(check(i)) {
				ans = i;
				break;
			}
		}
		cout << ans << '\n';
		for(int i = 1; i <= m; i++) a[i] = b[i] = f[i] = 0;
	}
	return 0;
}
