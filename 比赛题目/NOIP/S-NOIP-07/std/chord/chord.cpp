#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct Node {
	int g;
	ll cnt[2], sum[2];
};
vector<Node> f, h;
void add(Node x) {
	if(h.empty() || h.back().g != x.g) h.push_back(x);
	else for(int i = 0; i < 2; i++) {
		h.back().cnt[i] += x.cnt[i];
		h.back().sum[i] += x.sum[i];
	}
}
int main() {
	freopen("chord.in", "r", stdin);
	freopen("chord.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		f.clear();
		ll ans = 0;
		for(int i = 1; i <= n; i++) {
			int x;
			cin >> x;
			h.clear();
			add({x, {0, 1}, {0, 1}});
			for(Node u : f) {
				int g = __gcd(u.g, x);
				Node v = {g, {0, 0}, {0, 0}};
				for(int j = 0; j < 2; j++) {
					// gcd 变小后，原来的元素都不等于新的 gcd。
					int k = (g == u.g ? j : 0) ^ (g == x);
					v.cnt[k] += u.cnt[j];
					v.sum[k] += u.sum[j] + u.cnt[j];
				}
				add(v);
			}
			f.swap(h);
			for(Node u : f) ans += u.sum[1];
		}
		cout << ans << '\n';
	}
	return 0;
}
