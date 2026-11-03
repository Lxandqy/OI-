#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, a[maxn];
ll m, sum;
int main() {
	freopen("vote.in", "r", stdin);
	freopen("vote.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		sum = m;
		int mx = 0;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			sum += a[i], mx = max(mx, a[i]);
		}
		ll x = max(1ll * mx, (sum + n - 1) / n);
		sort(a + 1, a + n + 1);
		int ans = 0;
		for(int i = n; i >= 1; i--) {
			if(m < x - a[i]) break;
			m -= x - a[i], ans++;
		}
		cout << ans << '\n';
	}
	return 0;
}
