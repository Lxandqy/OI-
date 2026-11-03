#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll k;
map<int, pair<int, int>> mp;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		mp.clear();
		for(int i = 1; i <= n; i++) {
			int l, r, s = 0, last = 0;
			cin >> l; r = l;
			while(1) {
				for(int x : {r, l})
					if(x && x != last) {
						auto &v = mp[x];
						v.first++, v.second += s;
						last = x;
					}
				if(r == 1) break;
				l /= 2, r = (r + 1) / 2, s++;
			}
		}
		int ans = -1;
		for(auto x : mp)
			if(x.second.first == n && x.second.second <= k) ans = max(ans, x.first);
		cout << ans << '\n';
	}
	return 0;
}
