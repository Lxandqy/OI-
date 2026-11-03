#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5000 + 10;
int n, a[maxn], cnt[1 << 20];
ll ans;
int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int k = 1; k <= n; k++) {
		for(int l = k + 1; l <= n; l++) ans += cnt[a[k] ^ a[l]];
		// 查询后再加入第二个位置为 k 的数对。
		for(int i = 1; i < k; i++) cnt[a[i] ^ a[k]]++;
	}
	cout << ans << '\n';
	return 0;
}
