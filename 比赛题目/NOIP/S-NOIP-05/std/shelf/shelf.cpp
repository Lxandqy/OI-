#include<bits/stdc++.h>
using namespace std;
const int maxn = (1 << 20) + 10, mod = 1e9 + 7;
int n, k, cnt[20], l[20], r[20], len[maxn], f[maxn], g[maxn];
void solve() {
	cin >> n >> k;
	for(int i = 0; i < k; i++) cnt[i] = r[i] = 0, l[i] = n + 1;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x; x--;
		cnt[x]++, l[x] = min(l[x], i), r[x] = i;
	}
	int all = (1 << k) - 1;
	f[0] = len[0] = 0;
	for(int s = 1; s <= all; s++) {
		int x = __builtin_ctz(s);
		len[s] = len[s ^ (1 << x)] + cnt[x], f[s] = n;
	}
	for(int s = 0; s < all; s++)
		for(int t = all ^ s; t; t &= t - 1) {
			int x = __builtin_ctz(t), nxt = s | (1 << x);
			int cost = max(len[s] + 1 - l[x], r[x] - len[s] - cnt[x]);
			f[nxt] = min(f[nxt], max(f[s], cost));
		}
	int ans = f[all];
	// 固定最终的最小距离，再统计所有满足限制的前缀。
	for(int s = 0; s <= all; s++) g[s] = 0;
	g[0] = 1;
	for(int s = 0; s < all; s++) if(g[s])
		for(int t = all ^ s; t; t &= t - 1) {
			int x = __builtin_ctz(t), nxt = s | (1 << x);
			int cost = max(len[s] + 1 - l[x], r[x] - len[s] - cnt[x]);
			if(cost <= ans) g[nxt] = (g[nxt] + g[s]) % mod;
		}
	cout << ans << ' ' << g[all] << '\n';
}
int main() {
	freopen("shelf.in", "r", stdin);
	freopen("shelf.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
