#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
int n, r[maxn], t[maxn], d[maxn];
int main() {
	freopen("poker.in", "r", stdin);
	freopen("poker.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s; cin >> n >> s;
	for(int i = 1; i <= n; i++) cin >> r[i];
	for(int i = 1; i <= n; i++) cin >> t[i];
	ll ans = 0;
	int cur = 0;
	for(int i = 1; i <= n; i++) {
		cur ^= d[i];
		if((s[i - 1] - '0') ^ cur) {
			ans += t[i];
			cur ^= 1, d[r[i] + 1] ^= 1;
		}
	}
	cout << ans << '\n';
	return 0;
}
