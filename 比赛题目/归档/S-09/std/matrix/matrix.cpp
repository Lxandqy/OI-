#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int n, k;
bitset<maxn> a[maxn];
bool check(bitset<maxn> s) {
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int cnt = (s ^ a[i]).count();
		ans += min(cnt, n - cnt);
		if(ans > k) return 0;
	}
	return 1;
}
void solve() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s; a[i].reset();
		for(int j = 0; j < n; j++) a[i][j] = s[j] == '1';
	}
	for(int i = 1; i <= n; i++) if(check(a[i])) { cout << "YES\n"; return; }
	if(k == n) for(int j = 0; j < n; j++) {
		bitset<maxn> s = a[1]; s.flip(j);
		if(check(s)) { cout << "YES\n"; return; }
	}
	cout << "NO\n";
}
int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
