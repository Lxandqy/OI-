#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct Node { int l, x, y, r; }a[maxn];
int n, m, k;
bool vis[maxn];
int main() {
	freopen("shoot.in", "r", stdin);
	freopen("shoot.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> a[i].l >> a[i].x >> a[i].y >> a[i].r;
	sort(a + 1, a + n + 1, [](Node x, Node y) { return x.r < y.r; });
	while(k--) {
		int x; cin >> x;
		int l = 1, r = n;
		while(l <= r) {
			int mid = l + r >> 1;
			if(a[mid].r >= x) r = mid - 1;
			else l = mid + 1;
		}
		if(l > n || x < a[l].l) cout << "Failed\n";
		else if(vis[l]) cout << "Again\n";
		else {
			vis[l] = 1;
			cout << (a[l].x <= x && x <= a[l].y ? "Perfect\n" : "Normal\n");
		}
	}
	return 0;
}
