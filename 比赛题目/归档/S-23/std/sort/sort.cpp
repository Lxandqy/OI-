#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int n, a[maxn], b[maxn];
vector<pair<int, int>> ans;
bool solve() {
	ans.clear();
	for(int i = 1; i <= n; i++) {
		int j = i;
		while(j <= n && a[j] != b[i]) j++;
		if(j > n) return 0;
		while(j > i) {
			if(a[j - 1] <= a[j]) return 0;
			swap(a[j - 1], a[j]);
			ans.push_back({j - 1, j});
			j--;
		}
	}
	return 1;
}
int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
int t; cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++) cin >> b[i];
		if(!solve()) cout << -1 << '\n';
		else {
			cout << 0 << '\n' << ans.size() << '\n';
			for(auto x : ans) cout << x.first << ' ' << x.second << '\n';
		}
	}
	return 0;
}
