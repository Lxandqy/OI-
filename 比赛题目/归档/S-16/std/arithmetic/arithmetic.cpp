#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, q, op[maxn];
ll L, R, a[maxn], x[maxn], s[maxn], t[maxn];
__int128 cal(ll v) {
	__int128 res = v;
	for(int i = 1; i <= q; i++) {
		if(op[i] == 1 && res >= x[i]) res = (res + s[i]) * t[i];
		if(op[i] == 2 && res <= x[i]) res = (res - s[i]) / t[i];
	}
	return res;
}
int get(__int128 val) {
	int l = 1, r = n + 1;
	while(l < r) {
		int mid = l + r >> 1;
		if(cal(a[mid]) >= val) r = mid;
		else l = mid + 1;
	}
	return l;
}
int main() {
	freopen("arithmetic.in", "r", stdin);
	freopen("arithmetic.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q >> L >> R;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= q; i++) cin >> op[i] >> x[i] >> s[i] >> t[i];
	sort(a + 1, a + n + 1);
	cout << get((__int128)R + 1) - get(L) << '\n';
	return 0;
}
