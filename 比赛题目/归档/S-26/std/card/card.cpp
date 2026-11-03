#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int n, a[maxn], b[maxn];
bool check(int x) {
	int sum = 0, cur = 0, ans = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i] >= x;
		cur = max(0, cur + (b[i] >= x) - (a[i] >= x));
		ans = max(ans, cur);
	}
	return sum + ans >= (n + 1) / 2;
}
int main() {
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
	int l = 1, r = 1e9;
	while(l < r) {
		int mid = l + (r - l + 1) / 2;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l << '\n';
	return 0;
}
