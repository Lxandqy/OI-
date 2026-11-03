#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5010, mod = 1e9 + 7, inv2 = (mod + 1) / 2;
int n, b[maxn], vis[maxn];
ll p[maxn], a[maxn];
string s;
void solve() {
	cin >> n >> s;
	for(int i = 1; i <= n; i++) cin >> b[i];
	for(int i = 1; i <= n; i++) {
		vis[i] = 0;
		a[i] = s[i - 1] == 'C' ? 1 : s[i - 1] == '?' ? inv2 : 0;
	}
	int u = n;
	while(!vis[u]) { vis[u] = 1; u = b[u]; }
	int pos = u;
	for(int v = b[u]; v != u; v = b[v]) pos = min(pos, v);
	ll ans = 0;
	for(int x = 0; x <= 1; x++) for(int y = 0; y <= 1; y++) {
		for(int i = 1; i <= n; i++) p[i] = a[i];
		ll w = 1;
		for(int i = 1; i <= n; i++) {
			int v = b[i];
			if(i == pos) {
				w = (x ? p[i] : (1 - p[i] + mod) % mod) * (y ? p[v] : (1 - p[v] + mod) % mod) % mod;
				p[i] = x, p[v] = y;
			}
			ll z = p[i] * p[v] % mod;
			p[v] = (p[i] + p[v] - z + mod) % mod;
			p[i] = z;
		}
		ans = (ans + w * p[n]) % mod;
	}
	for(char c : s) if(c == '?') ans = ans * 2 % mod;
	cout << ans << '\n';
}
int main() {
	freopen("experiment.in", "r", stdin);
	freopen("experiment.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
int t; cin >> t;
	while(t--) solve();
	return 0;
}
