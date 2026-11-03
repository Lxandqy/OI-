#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, a[maxn];
int main() {
	freopen("juice.in", "r", stdin);
	freopen("juice.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		sort(a + 1, a + n + 1);
		int m = a[(n + 1) / 2];
		int l = max(a[1], m - k + 1), r = min(a[n], m + k - 1);
		ll ans = LLONG_MAX;
		for(int x = l; x <= r; x++) {
			ll sum = 0;
			for(int i = 1; i <= n; i++) sum += (abs(a[i] - x) + k - 1) / k;
			ans = min(ans, sum);
		}
		cout << ans << '\n';
	}
	return 0;
}
