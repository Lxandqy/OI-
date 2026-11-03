#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, L, R, f[maxn], len;
int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> L >> R;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		if(x < L || x > R) continue;
		int l = 1, r = len;
		while(l <= r) {
			int mid = l + r >> 1;
			if(f[mid] < x) l = mid + 1;
			else r = mid - 1;
		}
		f[l] = x, len = max(len, l);
	}
	cout << n - len << '\n';
	return 0;
}
