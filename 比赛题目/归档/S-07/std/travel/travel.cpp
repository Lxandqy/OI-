#include<bits/stdc++.h>
using namespace std;
int main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	int n, a, b; cin >> n >> a >> b;
	int x = a ^ b, ans = 0;
	while(x) ans += x & 1, x >>= 1;
	cout << ans << '\n';
	return 0;
}
