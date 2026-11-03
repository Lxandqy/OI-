#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, a[maxn], b[maxn];
ll k, s[maxn];
void solve() {
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= m; i++) s[i] = s[i - 1] + b[i];
	ll sum = 0, ans = 4e18;
	for(int i = 0; i <= n; i++) {
		ll j = (k + i) / (i + 1) - 1;
		if(j <= m) ans = min(ans, sum + s[j]);
		if(i < n) sum += a[i + 1];
	}
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
