#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
int n, m, a[maxn], b[maxn];
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];
	sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
	ll ans = 0;
	int l = 1, r = m;
	for(int i = 1; i <= n && a[i] < 0; i++) ans += 1ll * a[i] * b[l++];
	for(int i = n; i >= 1 && a[i] > 0; i--) ans += 1ll * a[i] * b[r--];
	cout << ans << '\n';
	return 0;
}
