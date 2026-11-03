#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 410, maxm = 1e6 + 10;
int n, m, a[maxn][maxn], cnt[maxm];
int main() {
	freopen("colorful.in", "r", stdin);
	freopen("colorful.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];
	ll ans = 1ll * n * (n + 1) * m * (m + 1) / 4;
	for(int l = 1; l <= n; l++) for(int r = l; r <= n; r++) {
		for(int j = 1; j <= m; j++) if(a[l][j] == a[r][j]) ans -= ++cnt[a[l][j]];
		for(int j = 1; j <= m; j++) cnt[a[l][j]] = 0;
	}
	cout << ans << '\n';
	return 0;
}
