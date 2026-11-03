#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, Log[maxn];
ll f[maxn][19], g[maxn][19];
int main() {
	freopen("max.in", "r", stdin);
	freopen("max.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		f[i][0] = g[i][0] = f[i - 1][0] + x;
	}
	for(int i = 2; i <= n + 1; i++) Log[i] = Log[i / 2] + 1;
	for(int j = 1; (1 << j) <= n + 1; j++)
		for(int i = 0; i + (1 << j) - 1 <= n; i++) {
			int k = i + (1 << j - 1);
			f[i][j] = max(f[i][j - 1], f[k][j - 1]);
			g[i][j] = min(g[i][j - 1], g[k][j - 1]);
		}
	while(m--) {
		int l, r; cin >> l >> r; l--;
		int k = Log[r - l + 1], p = r - (1 << k) + 1;
		cout << max(f[l][k], f[p][k]) - min(g[l][k], g[p][k]) << '\n';
	}
	return 0;
}
