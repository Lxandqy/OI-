#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 110, maxh = 510;
const ll inf = 1ll << 60;
int n, h;
ll f[maxh][maxh];
struct Node {
	int t, b, l, r;
}a[maxn];
bool cmp(Node x, Node y) {
	return 1ll * x.t * y.b < 1ll * y.t * x.b;
}
void solve() {
	cin >> n >> h;
	for(int i = 1; i <= n; i++) cin >> a[i].t >> a[i].b >> a[i].l >> a[i].r;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 0; i <= h; i++)
		for(int j = 0; i + j <= h; j++) f[i][j] = -inf;
	f[0][0] = 0;
	ll ans = 0;
	for(int k = 1; k <= n; k++) {
		int t = a[k].t, b = a[k].b;
		for(int i = h; i >= 0; i--)
			for(int j = h - i; j >= 0; j--) {
				if(i >= t && f[i - t][j] != -inf)
					f[i][j] = max(f[i][j], f[i - t][j] + a[k].l - 1ll * b * i);
				if(j >= t && f[i][j - t] != -inf)
					f[i][j] = max(f[i][j], f[i][j - t] + a[k].r - 1ll * b * j);
				ans = max(ans, f[i][j]);
			}
	}
	cout << ans << '\n';
}
int main() {
	freopen("tea.in", "r", stdin);
	freopen("tea.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
