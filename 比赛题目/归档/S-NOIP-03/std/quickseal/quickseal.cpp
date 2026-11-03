#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 200010;
int n, q;
ll a[maxn], b[maxn], c[maxn];
int main() {
	freopen("quickseal.in", "r", stdin);
	freopen("quickseal.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
	ll sum = 0, mx = 0;
	for(int i = n; i >= 1; i--) {
		sum += b[i];
		if(i < n) sum += c[i];
		mx = max(mx, a[i] + sum);
	}
	while(q--) {
		ll t;
		cin >> t;
		if(t < sum) cout << -1 << '\n';
		else cout << max(0LL, mx - t) << '\n';
	}
	return 0;
}
