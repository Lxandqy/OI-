#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, a[maxn];
ll d[maxn];
int main() {
	freopen("star.in", "r", stdin);
	freopen("star.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		ll sum = 0, mx = 0;
		for(int i = 1; i <= n; i++) {
			ll b; cin >> b;
			d[i] = b - a[i];
			sum += d[i], mx = max(mx, abs(d[i]));
		}
		ll ans = mx;
		if(2 * k != n) {
			if(sum % (2 * k - n)) {
				cout << -1 << '\n';
				continue;
			}
			ans = sum / (2 * k - n);
		}
		else if(sum) ans = -1;
		if(ans < mx) ans = -1;
		for(int i = 1; i <= n && ans != -1; i++)
			if((d[i] + ans) % 2) ans = -1;
		cout << ans << '\n';
	}
	return 0;
}
