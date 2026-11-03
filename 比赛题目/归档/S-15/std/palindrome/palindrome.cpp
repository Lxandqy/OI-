#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, num[25], sum[25], len[2], a[2][25];
ll ans;
bool modify(int t, int p, int v) {
	if(v < 0 || v > 9) return 0;
	if((p == 1 || p == len[t]) && v == 0) return 0;
	if(a[t][p] != -1) return a[t][p] == v;
	a[t][p] = v;
	if(!modify(t, len[t] + 1 - p, v)) return 0;
	if(p <= len[t ^ 1]) return modify(t ^ 1, p, sum[p] - v);
	return sum[p] == v;
}
void cal() {
	int m = n;
	while(m > 1 && sum[m] == 0) m--;
	ll res = 1;
	for(int i = 1; i <= (m + 1) / 2; i++) {
		if(sum[i] != sum[m + 1 - i]) { res = 0; break; }
		int l = max(i == 1 ? 1 : 0, sum[i] - 9);
		int r = min(9, sum[i] - (i == 1 ? 1 : 0));
		if(l > r) { res = 0; break; }
		res *= r - l + 1;
	}
	ans += res;
	len[0] = m;
	for(int k = 1; k < m; k++) {
		len[1] = k;
		memset(a, -1, sizeof(a));
		bool ok = 1;
		// 较短的数没有这些高位，较长的数由此确定。
		for(int i = m; i > k && ok; i--) ok = modify(0, i, sum[i]);
		for(int i = 1; i <= m && ok; i++) {
			if(a[0][i] < 0 || (i <= k && a[1][i] < 0)) ok = 0;
			else if(a[0][i] + (i <= k ? a[1][i] : 0) != sum[i]) ok = 0;
		}
		if(ok) ans += 2;
	}
}
void dfs(int p, int carry) {
	if(p > n) { cal(); return; }
	for(int i = 0; i <= (p < n); i++) {
		sum[p] = num[p] + i * 10 - carry;
		if(sum[p] >= 0 && sum[p] <= 18) dfs(p + 1, i);
	}
}
int main() {
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	ll x; cin >> x;
	while(x) num[++n] = x % 10, x /= 10;
	dfs(1, 0);
	cout << ans << '\n';
	return 0;
}
