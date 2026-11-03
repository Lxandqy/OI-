#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n;
ll a[maxn];
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		a[++n] = 0;
		sort(a + 1, a + n + 1);
		n = unique(a + 1, a + n + 1) - a - 1;
		ll ans = a[n] - a[1] + min(-a[1], a[n]);
		for(int i = 1; i < n; i++) {
			ll res = a[i] - a[1] + a[n] - a[i + 1];
			if(a[i] >= 0) res += min(-a[1], a[i]);
			else res += min(-a[i + 1], a[n]);
			ans = min(ans, res);
		}
		cout << ans << '\n';
	}
	return 0;
}
