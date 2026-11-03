#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
int n, pos[maxn], pre[maxn], nxt[maxn];
set<int> s;
int main() {
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x; pos[x] = i;
		pre[i] = i - 1, nxt[i] = i + 1;
	}
	ll ans = 1ll * n * (n - 1) * (n + 1) / 6;
	s.insert(n + 1);
	for(int v = 1; v <= n; v++) {
		int x = pos[v], l = pre[x], r = nxt[x];
		if(r <= n) {
			int d = *s.upper_bound(r);
			ans -= 1ll * (x - l) * (d - r);
		}
		nxt[l] = r, pre[r] = l;
		s.insert(x);
	}
	cout << ans << '\n';
	return 0;
}
