#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 600 + 10;
const ll inf = 1e18;
int n, k, a[maxn];
ll g[maxn][maxn], f[maxn][maxn];
int main() {
	freopen("erase.in", "r", stdin);
	freopen("erase.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i < n; i++) g[i][i + 1] = 0;
		for(int len = 3; len <= n; len++) {
			for(int l = 1; l + len - 1 <= n; l++) {
				int r = l + len - 1;
				g[l][r] = inf;
				for(int j = l + 1; j < r; j++)
					g[l][r] = min(g[l][r], g[l][j] + g[j][r]);
				g[l][r] += abs(a[l] - a[r]);
			}
		}
		for(int c = 1; c <= k; c++)
			for(int i = 1; i <= n; i++) f[c][i] = inf;
		f[1][1] = 0;
		// 相邻两个保留位置之间的删除互不影响。
		for(int c = 2; c <= k; c++)
			for(int r = c; r <= n; r++)
				for(int l = c - 1; l < r; l++)
					f[c][r] = min(f[c][r], f[c - 1][l] + g[l][r]);
		cout << f[k][n] << '\n';
	}
	return 0;
}
