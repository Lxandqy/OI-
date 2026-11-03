#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, b[maxn];
struct Node {
	int a, w;
}a[maxn];
bool cmp(Node x, Node y) {
	if(x.a != y.a) return x.a < y.a;
	return x.w > y.w;
}
int main() {
	freopen("board.in", "r", stdin);
	freopen("board.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i].a >> a[i].w;
		sort(a + 1, a + n + 1, cmp);
		int cnt = 0, tot = 0;
		for(int i = 1; i <= n; i++) {
			if(i == 1 || a[i].a != a[i - 1].a) cnt = 0;
			if(++cnt <= k / 2) b[++tot] = a[i].w;
		}
		if(tot < k) {
			cout << -1 << '\n';
			continue;
		}
		sort(b + 1, b + tot + 1, greater<int>());
		ll ans = 0;
		for(int i = 1; i <= k; i++) ans += b[i];
		cout << ans << '\n';
	}
	return 0;
}
