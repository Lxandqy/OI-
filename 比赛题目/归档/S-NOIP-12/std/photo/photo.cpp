#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 50000 + 10;
int n, m, q, tot, b, cnt[maxn], id[maxn], vis[maxn], mark[maxn];
ll sum[maxn];
int f[maxn][320];
vector<int> G[maxn], h;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m >> q;
		for(int i = 1; i <= n; i++) G[i].clear(), id[i] = -1, vis[i] = 0;
		for(int i = 1; i <= m; i++) cnt[i] = mark[i] = 0;
		tot = 0, h.clear();
		for(int i = 1; i <= m; i++) {
			int k; cin >> k;
			tot += k;
			while(k--) {
				int u; cin >> u;
				G[u].push_back(i);
			}
		}
		b = max(1, (int)sqrt(tot));
		for(int i = 1; i <= n; i++)
			if((int)G[i].size() > b) id[i] = h.size(), h.push_back(i);
		int k = h.size();
		for(int i = 1; i <= n; i++)
			for(int j = 0; j < k; j++) f[i][j] = 0;
		for(int j = 0; j < k; j++) {
			sum[j] = 0;
			for(int v : G[h[j]]) mark[v] = j + 1;
			for(int u = 1; u <= n; u++)
				for(int v : G[u])
					if(mark[v] == j + 1) f[u][j]++;
		}
		ll ans = 0;
		while(q--) {
			int u; cin >> u;
			ll res = 0;
			if(id[u] == -1) {
				for(int v : G[u]) res += cnt[v];
			}
			else res = sum[id[u]];
			for(int j = 0; j < k; j++)
				if(vis[h[j]]) res += f[u][j];
			int val = vis[u] ? -1 : 1;
			if(val == 1) ans += res;
			else ans -= res - (int)G[u].size();
			if(id[u] == -1) {
				for(int v : G[u]) cnt[v] += val;
				for(int j = 0; j < k; j++) sum[j] += val * f[u][j];
			}
			vis[u] ^= 1;
			cout << ans << '\n';
		}
	}
	return 0;
}
