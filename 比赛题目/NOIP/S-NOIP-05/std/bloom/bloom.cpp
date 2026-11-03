#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll h, d;
vector<pair<ll, ll>> a;
void add(ll l, ll r, ll w) {
	l = max(l, 0ll), r = min(r, h - d);
	if(l > r) return;
	a.push_back({l, w}), a.push_back({r + 1, -w});
}
void solve() {
	cin >> n >> h >> d;
	a.clear();
	a.push_back({0, 0}), a.push_back({h - d + 1, 0});
	for(int i = 1; i <= n; i++) {
		ll l, r, w; cin >> l >> r >> w;
		if(r - d + 1 >= l) add(l - d, r, w);
		else add(l - d, r - d, w), add(l, r, w);
	}
	sort(a.begin(), a.end());
	ll sum = 0, ans = -1, cnt = 0;
	for(int i = 0; i < (int)a.size();) {
		int j = i;
		while(j < (int)a.size() && a[j].first == a[i].first) sum += a[j++].second;
		if(j == (int)a.size()) break;
		ll len = a[j].first - a[i].first;
		if(sum > ans) ans = sum, cnt = len;
		else if(sum == ans) cnt += len;
		i = j;
	}
	cout << ans << ' ' << cnt << '\n';
}
int main() {
	freopen("bloom.in", "r", stdin);
	freopen("bloom.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
