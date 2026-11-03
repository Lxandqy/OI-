#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll a[40], ans;
vector<ll> get(int l, int r, const vector<ll> &other) {
	vector<ll> v;
	for(int i = l; i <= r; i++) {
		int n = v.size(), p = 0;
		while(p < n && v[p] < a[i]) p++;
		if(p < n && v[p] == a[i]) return {0};
		vector<ll> b;
		b.reserve(3ll * n + 1);
		int x = 0, y = 0, z = p - 1, w = p;
		bool use = 0;
		while(x < n || y < n || z >= 0 || w < n || !use) {
			ll t = use ? LLONG_MAX : a[i];
			if(x < n) t = min(t, v[x]);
			if(y < n) t = min(t, v[y] + a[i]);
			if(z >= 0) t = min(t, a[i] - v[z]);
			if(w < n) t = min(t, v[w] - a[i]);
			if(b.empty() || b.back() != t) b.push_back(t);
			if(!use && t == a[i]) use = 1;
			if(x < n && t == v[x]) x++;
			if(y < n && t == v[y] + a[i]) y++;
			if(z >= 0 && t == a[i] - v[z]) z--;
			if(w < n && t == v[w] - a[i]) w++;
		}
		v.swap(b);
		if(!other.empty()) {
			if(v.size() <= 100000) {
				for(ll x : v) {
					int l = 0, r = (int)other.size() - 1;
					while(l <= r) {
						int mid = l + r >> 1;
						if(other[mid] == x) return {0};
						if(other[mid] < x) l = mid + 1;
						else r = mid - 1;
					}
				}
			}
			else {
				int j = 0;
				for(ll x : v) {
					while(j < (int)other.size() && other[j] < x) j++;
					if(j < (int)other.size() && other[j] == x) return {0};
				}
			}
		}
	}
	return v;
}
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	ans = LLONG_MAX;
	for(int i = 1; i <= n; i++) {
		ll x; cin >> x;
		ans = min(ans, x);
		if(i <= 33) a[i] = x;
	}
	if(n >= 34 || !ans) { cout << 0 << '\n'; return 0; }
	if(n >= 24) {
		vector<ll> sum(1, 0);
		for(int i = 1; i <= 20; i++) {
			int t = sum.size();
			for(int j = 0; j < t; j++) sum.push_back(sum[j] + a[i]);
		}
		sort(sum.begin(), sum.end());
		for(int i = 1; i < (int)sum.size(); i++) if(sum[i] == sum[i - 1]) {
			cout << 0 << '\n'; return 0;
		}
	}
	vector<ll> x = get(1, n / 2, {});
	if(!x.empty() && !x[0]) { cout << 0 << '\n'; return 0; }
	vector<ll> y = get(n / 2 + 1, n, x);
	if(!x.empty()) ans = min(ans, x[0]);
	if(!y.empty()) ans = min(ans, y[0]);
	for(int i = 0, j = 0; i < (int)x.size() && j < (int)y.size();) {
		ans = min(ans, abs(x[i] - y[j]));
		if(!ans) break;
		if(x[i] < y[j]) i++;
		else j++;
	}
	cout << ans << '\n';
	return 0;
}
