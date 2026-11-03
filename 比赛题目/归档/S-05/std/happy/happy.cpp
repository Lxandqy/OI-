#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, a[maxn];
int main() {
	freopen("happy.in", "r", stdin);
	freopen("happy.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) cin >> a[i], a[i] = max(a[i], a[i - 1]);
		int cnt = n, ans = 0;
		while(m--) {
			int x; cin >> x;
			if(!cnt) continue;
			ans++;
			int l = 1, r = cnt;
			while(l <= r) {
				int mid = l + r >> 1;
				if(a[mid] >= x) r = mid - 1;
				else l = mid + 1;
			}
			cnt = min(cnt - 1, l - 1);
		}
		cout << ans << '\n';
	}
	return 0;
}
