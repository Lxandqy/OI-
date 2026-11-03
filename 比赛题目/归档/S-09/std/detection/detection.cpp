#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
int n, m, P, C, a[maxn], d[maxn];
ll sum[maxn];
int main() {
	freopen("detection.in", "r", stdin);
	freopen("detection.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> P >> C;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++) d[i] = a[i + 1] - a[i];
	sort(d + 1, d + n);
	for(int i = 1; i < n; i++) sum[i] = sum[i - 1] + d[i];
	while(m--) {
		int R; cin >> R;
		int l = 1, r = n - 1;
		while(l <= r) { int mid = l + r >> 1; if(d[mid] <= 2 * R) l = mid + 1; else r = mid - 1; }
		ll cnt = n - l, len = sum[l - 1] + (cnt + 1) * (2ll * R);
		cout << len * P + (cnt + 1) * C << '\n';
	}
	return 0;
}
