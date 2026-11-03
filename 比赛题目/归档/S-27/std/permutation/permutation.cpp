#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10, mod = 998244353;
int n, p[maxn], a[maxn], b[maxn], cnt[maxn], pos[maxn], num[maxn];
void solve() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> p[i], cnt[i] = num[i] = 0;
	a[0] = a[n] = n;
	for(int i = 1; i < n; i++) {
		a[i] = max(p[i], p[i + 1]);
		cnt[a[i]]++, pos[a[i]] = i;
	}
	for(int i = 1; i <= n; i++) {
		b[i] = min(a[i - 1], a[i]);
		num[b[i]]++;
	}
	ll ans = 1;
	int sum = 0;
	for(int v = n; v >= 1; v--) {
		sum += num[v];
		if(!cnt[v]) ans = ans * sum % mod;
		else if(cnt[v] == 1) {
			int i = pos[v];
			ans = ans * ((b[i] == v) + (b[i + 1] == v)) % mod;
		}
		sum--;
	}
	cout << ans << '\n';
}
int main() {
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
