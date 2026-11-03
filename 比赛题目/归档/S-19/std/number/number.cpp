#include<bits/stdc++.h>
using namespace std;
const int maxn = 5010, base = 200000;
int n, a[maxn], ans;
bool f[400010];
int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < i; j++) if(f[a[i] - a[j] + base]) { ans++; break; }
		// 查询完成后，才能把当前数加入两个数的和中。
		for(int j = 1; j <= i; j++) f[a[i] + a[j] + base] = 1;
	}
	cout << ans << '\n';
	return 0;
}
