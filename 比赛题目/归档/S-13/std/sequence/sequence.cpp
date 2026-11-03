#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 3e5 + 10, mod = 998244353;
int n, t, p[maxn];
bool vis[maxn];
pair<int, int> a[maxn], b[maxn];
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> t;
	for(int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
	for(int i = 1; i <= n; i++) cin >> b[i].first, b[i].second = i;
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		ll x = a[i].first - b[i].first;
		ans = (ans + x * x) % mod;
		p[a[i].second] = b[i].second;
	}
	cout << ans;
	if(t) {
		int cnt = 0;
		for(int i = 1; i <= n; i++) if(!vis[i]) {
			cnt++;
			for(int u = i; !vis[u]; u = p[u]) vis[u] = 1;
		}
		cout << ' ' << n - cnt;
	}
	cout << '\n';
	return 0;
}
