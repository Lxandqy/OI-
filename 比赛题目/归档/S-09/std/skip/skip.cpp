#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, q, cnt[maxn], mx;
bool ans[maxn];
int main() {
	freopen("skip.in", "r", stdin);
	freopen("skip.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++) { int x; cin >> x; cnt[x]++, mx = max(mx, x); }
	for(int x = 1; x <= mx; x++) if(cnt[x]) {
		if(cnt[x] > 1) ans[1] = 1;
		for(int y = x + x; y <= mx; y += x) if(cnt[y]) ans[y / x] = 1;
	}
	while(q--) { int x; cin >> x; cout << (ans[x] ? "YES\n" : "NO\n"); }
	return 0;
}
