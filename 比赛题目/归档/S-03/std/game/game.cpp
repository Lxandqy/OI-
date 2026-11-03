#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
int n, a[maxn];
ll f[maxn];
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, greater<int>());
	for(int i = n; i >= 1; i--) f[i] = f[i + 2] + a[i];
	ll sum = 0, ans = LLONG_MIN;
	for(int i = 1; i <= n; i++) sum += a[i], ans = max(ans, sum + f[i + 2]);
	cout << ans << '\n';
	return 0;
}
