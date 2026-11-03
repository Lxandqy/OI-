#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 998244353;
int n, k, m, f[2][1024][11], cnt[1024], g[11][11];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void add(int &x, int y) { x += y; if(x >= mod) x -= mod; }
int main() {
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k; m = n / k;
	int all = (1 << m) - 1;
	for(int s = 1; s <= all; s++) cnt[s] = cnt[s >> 1] + (s & 1);
	for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) g[i][j] = gcd(i, j) == 1;
	f[0][0][0] = 1;
	for(int i = 0; i < n; i++) {
		int u = i & 1, v = u ^ 1;
		memset(f[v], 0, sizeof f[v]);
		for(int s = 0; s <= all; s++) {
			int num = n - m - (i - cnt[s]);
			for(int j = 0; j <= m; j++) if(f[u][s][j]) {
				ll val = f[u][s][j];
				if(num > 0) add(f[v][s][0], 1ll * val * num % mod);
				for(int x = 1; x <= m; x++) if(!(s >> (x - 1) & 1) && (!j || !g[j][x]))
					add(f[v][s | (1 << (x - 1))][x], val);
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= m; i++) add(ans, f[n & 1][all][i]);
	cout << ans << '\n';
	return 0;
}
