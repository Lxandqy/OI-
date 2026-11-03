#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 3e5 + 10, mod = 998244353;
int n, rt, c[maxn];
ll fac[maxn], tot = 1, pairs, inv;
vector<int> G[maxn];
int lowbit(int x) { return x & -x; }
void modify(int x, int v) { for(int i = x; i <= n; i += lowbit(i)) c[i] += v; }
int query(int x) {
	int ans = 0;
	for(int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}
void dfs(int u, int fa, int dep) {
	pairs += dep, inv += dep - query(u);
	modify(u, 1);
	int cnt = 0;
	for(int v : G[u]) if(v != fa) dfs(v, u, dep + 1), cnt++;
	tot = tot * fac[cnt] % mod;
	modify(u, -1);
}
int main() {
	freopen("wander.in", "r", stdin);
	freopen("wander.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> rt;
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	dfs(rt, 0, 0);
	ll other = 1ll * n * (n - 1) / 2 - pairs;
	cout << tot * ((inv + other % mod * ((mod + 1) / 2)) % mod) % mod << '\n';
	return 0;
}
