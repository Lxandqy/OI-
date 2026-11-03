#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int n, w, a[maxn], cnt[maxn];
int main() {
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> w;
	for(int i = 1; i <= n; i++) cin >> a[i];
	if(n == 1) { cout << 0 << '\n'; return 0; }
	int ans = n;
	for(int v = 0; v <= (w - 1) / (n - 1); v++) {
		int lim = w - (n - 1) * v;
		for(int i = 1; i <= n; i++) {
			int x = a[i] - (i - 1) * v;
			if(x >= 1 && x <= lim) ans = min(ans, n - ++cnt[x]);
		}
		for(int i = 1; i <= n; i++) {
			int x = a[i] - (i - 1) * v;
			if(x >= 1 && x <= lim) cnt[x] = 0;
		}
	}
	cout << ans << '\n';
	return 0;
}
