#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
int n, a[maxn];
ll r1, r2, r3, d, f[maxn], b[maxn];
int main() {
	freopen("shot.in", "r", stdin);
	freopen("shot.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> r1 >> r2 >> r3 >> d;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = min((a[i] + 1) * r1, r2);
	}
	fill(f, f + n + 3, 4e18);
	f[1] = 0;
	for(int i = 1; i <= n; i++) {
		f[i + 1] = min(f[i + 1], f[i] + a[i] * r1 + r3 + d);
		f[i + 1] = min(f[i + 1], f[i] + b[i] + r1 + 3 * d);
		if(i < n) f[i + 2] = min(f[i + 2], f[i] + b[i] + b[i + 1] + 2 * r1 + 4 * d);
	}
	ll ans = f[n + 1] - d;
	ans = min(ans, f[n - 1] + b[n - 1] + a[n] * r1 + r3 + r1 + 2 * d);
	cout << ans << '\n';
	return 0;
}
