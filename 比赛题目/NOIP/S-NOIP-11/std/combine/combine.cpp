#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, k, d[maxn];
vector<ll> a[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m >> k;
		for(int i = 1; i <= m; i++) cin >> d[i];
		for(int i = 1; i <= n; i++) {
			int x, y; cin >> x >> y;
			a[x].push_back(y);
		}
		ll ans = 0;
		for(int i = 1; i <= m; i++) {
			sort(a[i].begin(), a[i].end());
			if(a[i].size() < d[i]) { ans = -1; break; }
			for(int j = 0; j < d[i]; j++) ans += a[i][j];
			if(i == m) continue;
			for(int j = d[i]; j + k <= (int)a[i].size(); j += k) {
				ll sum = 0;
				for(int p = j; p < j + k; p++) sum += a[i][p];
				a[i + 1].push_back(sum);
			}
		}
		cout << ans << '\n';
		for(int i = 1; i <= m; i++) a[i].clear();
	}
	return 0;
}
