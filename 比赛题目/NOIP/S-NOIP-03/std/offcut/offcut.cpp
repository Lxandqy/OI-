#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1000010;
int n, a[maxn], s[maxn], mx;
ll m, k;

bool check(int x) {
	ll cnt = 0, rem = m, save = 0;
	for(int j = x, t = 1; j <= mx; j += x, t++) {
		cnt += 1ll * t * (s[min(mx, j + x - 1)] - s[j - 1]);
		ll num = min(1ll * a[j], rem / t);
		rem -= num * t;
		save += num;
	}
	return cnt >= m && m - save <= k;
}

int main() {
	freopen("offcut.in", "r", stdin);
	freopen("offcut.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1, x; i <= n; i++) {
		cin >> x;
		a[x]++;
		mx = max(mx, x);
	}
	for(int i = 1; i <= mx; i++) s[i] = s[i - 1] + a[i];
	int ans = 0;
	for(int i = mx; i; i--) {
		if(check(i)) {
			ans = i;
			break;
		}
	}
	cout << ans << '\n';
	return 0;
}
