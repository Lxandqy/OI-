#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m, a[maxn], num[maxn], cnt[maxn], f[maxn][18];
int get(int x) {
	int l = 1, r = n;
	while(l < r) { int mid = l + r >> 1; if(num[mid] < x) l = mid + 1; else r = mid; }
	return l;
}
int main() {
	freopen("luck.in", "r", stdin);
	freopen("luck.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i], num[i] = a[i];
	sort(num + 1, num + n + 1);
	for(int i = 1; i <= n; i++) a[i] = get(a[i]);
	int r = 0, sum = 0;
	for(int l = 1; l <= n; l++) {
		while(r < n && sum < 8) if(!cnt[a[++r]]++) sum++;
		f[l][0] = sum == 8 ? r + 1 : n + 2;
		if(!--cnt[a[l]]) sum--;
	}
	for(int j = 0; j <= 17; j++) f[n + 1][j] = f[n + 2][j] = n + 2;
	for(int j = 1; j <= 17; j++) for(int i = 1; i <= n; i++) f[i][j] = f[f[i][j - 1]][j - 1];
	while(m--) {
		int l, r; cin >> l >> r;
		int ans = 0;
		for(int j = 17; j >= 0; j--) if(f[l][j] <= r + 1) ans += 1 << j, l = f[l][j];
		cout << ans << '\n';
	}
	return 0;
}
