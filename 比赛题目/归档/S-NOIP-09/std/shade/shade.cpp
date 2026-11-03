#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n;
ll k, a[maxn];
void solve() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	ll ans = -1, cut = -1;
	for(int i = 3; i <= n; i++) {
		ll d = max(0ll, a[i] - a[i - 1] - a[i - 2] + 1);
		if(d > k) continue;
		ll res = a[i] + a[i - 1] + a[i - 2] - d;
		if(res > ans) ans = res, cut = d;
		else if(res == ans) cut = min(cut, d);
	}
	cout << ans << ' ' << cut << '\n';
}
int main() {
	freopen("shade.in", "r", stdin);
	freopen("shade.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
