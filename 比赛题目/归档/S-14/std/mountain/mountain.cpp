#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e6 + 10;
int n, a[maxn];
int main() {
	freopen("mountain.in", "r", stdin);
	freopen("mountain.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int l = 0, r = n + 1, mn1 = 0, mx1 = 0, mn2 = 0, mx2 = 0;
	while(l + 2 < r) {
		mn1 = min(mn1, a[l + 1]), mx1 = max(mx1, a[l + 1]);
		mn2 = min(mn2, a[r - 1]), mx2 = max(mx2, a[r - 1]);
		if(mn1 <= a[r - 1] && a[r - 1] <= mx1) r--;
		else if(mn2 <= a[l + 1] && a[l + 1] <= mx2) l++;
		else break;
	}
	cout << (l + 2 == r ? "Yes" : "No") << '\n';
	return 0;
}
