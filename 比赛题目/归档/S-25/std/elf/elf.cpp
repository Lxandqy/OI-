#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e4 + 10;
int n, cnt, a[maxn];
int get(int pos, int k) {
	if(pos <= cnt) return a[pos];
	if(pos <= cnt + k) return 0;
	return a[pos - k];
}
int main() {
	freopen("elf.in", "r", stdin);
	freopen("elf.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	while(cnt < n && a[cnt + 1] < 0) cnt++;
	ll ans = 2e9;
	for(int k = n & 1; k <= n; k += 2) {
		ll mx = -4e9, mn = 4e9;
		for(int i = 1; i <= (n + k) / 2; i++) {
			ll val = 1ll * get(i, k) + get(n + k - i + 1, k);
			mx = max(mx, val), mn = min(mn, val);
			if(mx - mn >= ans) break;
		}
		ans = min(ans, mx - mn);
		if(!ans) break;
	}
	cout << ans << '\n';
	return 0;
}
