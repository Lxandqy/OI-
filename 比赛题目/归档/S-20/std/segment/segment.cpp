#include<bits/stdc++.h>
using namespace std;
const int maxn = 510, inf = 1e9;
int n, q, w[maxn], cnt[maxn][maxn], f[maxn][maxn];
int main() {
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> q;
	for(int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r;
		cnt[l][r]++, w[l]++, w[r]--;
	}
	for(int i = 1; i <= n; i++) w[i] += w[i - 1];
	for(int l = 1; l <= n; l++) for(int r = n; r >= l; r--)
		cnt[l][r] += cnt[l - 1][r] + cnt[l][r + 1] - cnt[l - 1][r + 1];
	for(int len = 2; len <= n; len++) for(int l = 1; l + len - 1 <= n; l++) {
		int r = l + len - 1;
		f[l][r] = inf;
		for(int k = l; k < r; k++) f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + w[k] - cnt[l][r]);
	}
	cout << f[1][n] + q << '\n';
	return 0;
}
