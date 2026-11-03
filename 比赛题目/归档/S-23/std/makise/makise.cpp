#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
	freopen("makise.in", "r", stdin);
	freopen("makise.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
int n, cnt = 0;
	ll sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		sum += x, cnt += x & 1;
		ll ans = sum - cnt / 3 - (cnt % 3 == 1);
		cout << (i == 1 ? sum : ans) << (i == n ? '\n' : ' ');
	}
	return 0;
}
