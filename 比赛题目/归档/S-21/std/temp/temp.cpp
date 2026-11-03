#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m;
struct Node { int t, l, r; }a[maxn];
bool cmp(Node x, Node y) { return x.t < y.t; }
bool check() {
	int l = m, r = m, t = 0;
	for(int i = 1; i <= n; i++) {
		int d = a[i].t - t;
		l = max(l - d, a[i].l), r = min(r + d, a[i].r);
		if(l > r) return 0;
		t = a[i].t;
	}
	return 1;
}
int main() {
	freopen("temp.in", "r", stdin);
	freopen("temp.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i = 1; i <= n; i++) cin >> a[i].t >> a[i].l >> a[i].r;
		sort(a + 1, a + n + 1, cmp);
		cout << (check() ? "YES" : "NO") << '\n';
	}
	return 0;
}
