#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7, inv2 = 500000004;
ll sum(ll l, ll r) {
	if(l > r) return 0;
	return (l + r) % mod * ((r - l + 1) % mod) % mod * inv2 % mod;
}
ll query(ll x) {
	if(!x) return 0;
	ll l = 1, r = 1e9;
	while(l < r) {
		ll mid = l + r + 1 >> 1;
		if(mid * mid <= x) l = mid;
		else r = mid - 1;
	}
	ll p = l * l, mid = p + l;
	ll ans = (sum(p, min(x, mid)) - sum(mid + 1, x) + mod) % mod;
	if(!(l & 1)) ans = (mod - ans) % mod;
	return ans;
}
int main() {
	freopen("alice.in", "r", stdin);
	freopen("alice.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll l, r; cin >> l >> r;
	cout << (query(r) - query(l - 1) + mod) % mod << '\n';
	return 0;
}
