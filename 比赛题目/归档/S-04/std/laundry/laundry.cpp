#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
int q, n, m;
ll f[maxn], g[maxn];
struct Node {
	ll t; int w;
	bool operator < (const Node &x) const { return t > x.t; }
};
void get(int n, ll *a) {
	priority_queue<Node> h;
	for(int i = 1; i <= n; i++) { int x; cin >> x; h.push({x, x}); }
	for(int i = 1; i <= q; i++) {
		Node x = h.top(); h.pop();
		a[i] = x.t;
		h.push({x.t + x.w, x.w});
	}
}
int main() {
	freopen("laundry.in", "r", stdin);
	freopen("laundry.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> q >> n >> m;
	get(n, f), get(m, g);
	ll ans = 0;
	for(int i = 1; i <= q; i++) ans = max(ans, f[i] + g[q - i + 1]);
	cout << ans << '\n';
	return 0;
}
