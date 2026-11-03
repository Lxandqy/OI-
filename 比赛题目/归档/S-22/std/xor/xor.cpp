#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, a[maxn], s[maxn];
int solve() {
	if(n > 60) return 1;
	for(int len = 3; len <= n; len++) {
		for(int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			for(int i = l; i < r; i++) if((s[i] ^ s[l - 1]) > (s[r] ^ s[i])) return len - 2;
		}
	}
	return -1;
}
int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
int t; cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i], s[i] = s[i - 1] ^ a[i];
		cout << solve() << '\n';
	}
	return 0;
}
