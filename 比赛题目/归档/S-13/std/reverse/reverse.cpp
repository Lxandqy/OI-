#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int n, a[maxn];
int main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = n; i >= 1; i -= 2) cout << a[i] << ' ';
	for(int i = n % 2 ? 2 : 1; i <= n; i += 2) cout << a[i] << ' ';
	cout << '\n';
	return 0;
}
