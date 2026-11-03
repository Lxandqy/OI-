#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e3 + 10;
int n, m;
ll f[maxn], g[maxn];
int main() {
	freopen("bottle.in", "r", stdin);
	freopen("bottle.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		int a, b, c; cin >> a >> b >> c;
		fill(g, g + m + 1, -(1ll << 60));
		for(int j = a; j <= m; j++)
			g[j] = max(f[j - a], g[j - a + b]) + 1ll * b * c;
		for(int j = 0; j <= m; j++) f[j] = max(f[j], g[j]);
	}
	for(int i = 1; i <= m; i++) cout << f[i] << '\n';
	return 0;
}
