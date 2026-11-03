#include<bits/stdc++.h>
using namespace std;
const int maxn = 2000 + 10, maxm = 200000 + 10, mod = 998244353;
int n, k, m, f[maxm];
struct Node {
	int a, b, id;
}a[maxn];
bool cmp(Node x, Node y) {
	int p = x.b >= x.a, q = y.b >= y.a;
	if(p != q) return p > q;
	if(p && x.a != y.a) return x.a < y.a;
	if(!p && x.b != y.b) return x.b > y.b;
	return x.id < y.id;
}
int main() {
	freopen("stamp.in", "r", stdin);
	freopen("stamp.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k; m = k;
		for(int i = 1; i <= n; i++) {
			cin >> a[i].a >> a[i].b;
			a[i].id = i, m += a[i].b;
		}
		sort(a + 1, a + n + 1, cmp);
		for(int i = 0; i <= m; i++) f[i] = 0;
		f[k] = 1;
		for(int i = 1; i <= n; i++) {
			int x = a[i].a, d = a[i].b - x;
			if(d >= 0) {
				for(int j = m - d; j >= x; j--) {
					f[j + d] += f[j];
					if(f[j + d] >= mod) f[j + d] -= mod;
				}
			}
			else {
				for(int j = x; j <= m; j++) {
					f[j + d] += f[j];
					if(f[j + d] >= mod) f[j + d] -= mod;
				}
			}
		}
		int ans = mod - 1;
		for(int i = 0; i <= m; i++) {
			ans += f[i];
			if(ans >= mod) ans -= mod;
		}
		cout << ans << '\n';
	}
	return 0;
}
