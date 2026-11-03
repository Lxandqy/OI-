#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e6 + 10, mod = 1e9 + 7;
int n, m, s, t, tot;
struct Node { int x, v; }a[maxn];
bool cmp(Node x, Node y) { return x.x < y.x; }
ll ksm(ll x, int y) {
	ll ans = 1;
	while(y) {
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod; y >>= 1;
	}
	return ans;
}
int main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m >> s >> t;
	for(int i = 1; i <= m; i++) {
		int x, l, r; cin >> x >> l >> r;
		a[++tot] = {l, -1}, a[++tot] = {r + 1, 1};
	}
	a[++tot] = {t + 1, 0};
	sort(a + 1, a + tot + 1, cmp);
	int last = s, cnt = n;
	ll ans = 1;
	for(int i = 1; i <= tot;) {
		int x = a[i].x;
		ans = ans * ksm(cnt, x - last) % mod;
		while(i <= tot && a[i].x == x) cnt += a[i++].v;
		last = x;
	}
	cout << ans << '\n';
	return 0;
}
