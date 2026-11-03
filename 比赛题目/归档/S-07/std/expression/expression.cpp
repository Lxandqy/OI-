#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10, mod = 998244353;
int n, p[maxn];
int main() {
	freopen("expression.in", "r", stdin);
	freopen("expression.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	p[0] = 1;
	for(int i = 1; i <= n; i++) p[i] = 3ll * p[i - 1] % mod;
	int sum = 0;
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x; sum ^= x;
		ans = (ans + (i == n ? sum : 2ll * sum * p[n - i - 1])) % mod;
	}
	cout << ans << '\n';
	return 0;
}
