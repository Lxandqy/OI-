#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
struct Node { int p, q; };
int n, k, q, type, Log[maxn];
ll a[maxn], b[maxn];
vector<Node> f[40], st[21];
Node maxx(Node x, Node y) {
	return 1ll * x.p * y.q >= 1ll * y.p * x.q ? x : y;
}
Node query(int l, int r) {
	int t = min(n, 2 * k - 1), len = r - l + 1;
	if(len < k) return {0, 1};
	if(len < t) return f[len][r];
	l += t - 1;
	int z = Log[r - l + 1];
	return maxx(st[z][l], st[z][r - (1 << z) + 1]);
}
int main() {
	freopen("subarray.in", "r", stdin);
	freopen("subarray.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k >> q >> type;
	for(int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	for(int i = 1; i <= n; i++) cin >> b[i], b[i] += b[i - 1];
	int t = min(n, 2 * k - 1);
	for(int len = k; len <= t; len++) {
		f[len].assign(n + 1, {0, 1});
		for(int r = len; r <= n; r++) {
			Node cur = {(int)(a[r] - a[r - len]), (int)(b[r] - b[r - len])};
			if(len > k) cur = maxx(cur, maxx(f[len - 1][r], f[len - 1][r - 1]));
			f[len][r] = cur;
		}
	}
	for(int i = 2; i <= n; i++) Log[i] = Log[i / 2] + 1;
	if(k <= n) {
		st[0] = f[t];
		for(int j = 1; (1 << j) <= n; j++) {
			st[j].assign(n + 1, {0, 1});
			for(int i = t; i + (1 << j) - 1 <= n; i++)
				st[j][i] = maxx(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
		}
	}
	ll last = 0;
	while(q--) {
		ll x, y; cin >> x >> y;
		int l = (x ^ (last * type)) % n + 1, r = (y ^ (last * type)) % n + 1;
		if(l > r) swap(l, r);
		Node v = query(l, r);
		int d = __gcd(v.p, v.q);
		last = v.p / d;
		cout << last << '/' << v.q / d << '\n';
	}
	return 0;
}
