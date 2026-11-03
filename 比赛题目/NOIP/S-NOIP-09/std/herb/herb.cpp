#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, r;
ll k;
struct Node {
	ll a, d;
}a[maxn];
bool cmp(Node x, Node y) {
	return x.a < y.a;
}
bool check(ll x) {
	ll cnt = 0;
	for(int i = 1; i <= n; i++) if(x >= a[i].a) {
		cnt += (x - a[i].a) / a[i].d + 1;
		if(cnt >= k) return 1;
	}
	return 0;
}
void solve() {
	cin >> n >> k >> r;
	for(int i = 1; i <= n; i++) cin >> a[i].a >> a[i].d;
	sort(a + 1, a + n + 1, cmp);
	ll ans = 0;
	for(int i = 1; i <= r; i++) ans += a[i].a, a[i].a += a[i].d;
	k -= r;
	if(!k) {
		cout << ans << '\n';
		return;
	}
	ll l = 0, h = a[1].a + a[1].d * (k - 1);
	while(l < h) {
		ll mid = l + h >> 1;
		if(check(mid)) h = mid;
		else l = mid + 1;
	}
	ll cnt = 0;
	for(int i = 1; i <= n; i++) if(l > a[i].a) {
		ll num = (l - 1 - a[i].a) / a[i].d + 1;
		cnt += num;
		ans += num * a[i].a + num * (num - 1) / 2 * a[i].d;
	}
	ans += (k - cnt) * l;
	cout << ans << '\n';
}
int main() {
	freopen("herb.in", "r", stdin);
	freopen("herb.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
