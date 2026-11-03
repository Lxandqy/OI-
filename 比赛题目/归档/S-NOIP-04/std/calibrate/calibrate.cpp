#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n;
// mn、mx 维护前缀和数组的后缀最小值、最大值。
ll s[maxn], mn[maxn], mx[maxn];
int main() {
	freopen("calibrate.in", "r", stdin);
	freopen("calibrate.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		ll x; cin >> x;
		s[i] = s[i - 1] + x;
	}
	mn[n] = mx[n] = s[n];
	for(int i = n - 1; i >= 0; i--)
		mn[i] = min(mn[i + 1], s[i]), mx[i] = max(mx[i + 1], s[i]);
	ll l = 0, r = 0, ans = 4e18;
	for(int i = 1; i <= n; i++) {
		// 改第 i 步后，s[i..n] 都减去总和 s[n]。
		ll L = min(l, mn[i] - s[n]), R = max(r, mx[i] - s[n]);
		ans = min(ans, R - L);
		// 算完本次答案，才把 s[i] 加入左边。
		l = min(l, s[i]), r = max(r, s[i]);
	}
	cout << ans << '\n';
	return 0;
}
