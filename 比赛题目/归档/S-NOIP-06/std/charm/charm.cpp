#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 2e5 + 10;
int n, a[maxn];
ll k;
struct Trie {
	int tree[maxn * 30][2], cnt[maxn * 30], tot;
	ll c[30][2], sum;
	void clear() {
		for(int i = 0; i <= tot; i++) {
			cnt[i] = 0;
			for(int j = 0; j < 2; j++) tree[i][j] = 0;
		}
		tot = 0, sum = 0;
		memset(c, 0, sizeof(c));
	}
	void insert(int x) {
		int u = 0;
		for(int i = 29; i >= 0; i--) {
			int val = (x >> i) & 1;
			sum -= min(c[i][0], c[i][1]);
			c[i][val] += cnt[tree[u][val ^ 1]];
			sum += min(c[i][0], c[i][1]);
			if(!tree[u][val]) tree[u][val] = ++tot;
			u = tree[u][val];
			cnt[u]++;
		}
	}
	void del(int x) {
		int u = 0;
		for(int i = 29; i >= 0; i--) {
			int val = (x >> i) & 1;
			sum -= min(c[i][0], c[i][1]);
			// 删除左端时，x 是数对中靠前的数。
			c[i][val ^ 1] -= cnt[tree[u][val ^ 1]];
			sum += min(c[i][0], c[i][1]);
			u = tree[u][val];
			cnt[u]--;
		}
	}
}trie;

int main() {
	freopen("charm.in", "r", stdin);
	freopen("charm.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		trie.clear();
		ll ans = 0;
		int l = 1;
		for(int r = 1; r <= n; r++) {
			trie.insert(a[r]);
			while(trie.sum > k) trie.del(a[l++]);
			ans += r - l + 1;
		}
		cout << ans << '\n';
	}
	return 0;
}
