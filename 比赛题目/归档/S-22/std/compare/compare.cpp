#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, q, ans, cnt[maxn];
void modify(int u, int v, int x) {
	if(u > v) swap(u, v);
	if(!cnt[u]) ans--;
	cnt[u] += x;
	if(!cnt[u]) ans++;
}
int main() {
	freopen("compare.in", "r", stdin);
	freopen("compare.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m; ans = n;
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		modify(u, v, 1);
	}
	cin >> q;
	while(q--) {
		int op; cin >> op;
		if(op == 3) cout << ans << '\n';
		else {
			int u, v; cin >> u >> v;
			modify(u, v, op == 1 ? 1 : -1);
		}
	}
	return 0;
}
