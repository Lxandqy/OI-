#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e4 + 10;
int n, p[maxn];
ll cnt[maxn << 1], ans;
int main() {
	freopen("book.in", "r", stdin);
	freopen("book.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> p[i];
	for(int i = 1; i <= n; i++) {
		fill(cnt, cnt + 2 * n + 1, 0);
		int sum = 0;
		for(int l = i; l >= 1; l--) {
			if(l < i) sum += (p[l] > p[i] ? 1 : -1);
			cnt[n + sum] += l;
		}
		sum = 0;
		for(int r = i; r <= n; r++) {
			if(r > i) sum += (p[r] > p[i] ? 1 : -1);
			ans += 1ll * p[i] * r * cnt[n - sum];
		}
	}
	cout << ans << '\n';
	return 0;
}
