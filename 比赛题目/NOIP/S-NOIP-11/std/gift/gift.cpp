#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
const ll inf = 4e18;
int n, k;
ll m;
struct Node {
	int a;
	ll c;
}a[maxn];
bool cmp(Node x, Node y) {
	return x.a < y.a;
}
struct Trie {
	int tree[maxn * 20][2], tot;
	ll mn[maxn * 20];
	void clear() {
		for(int i = 0; i <= tot; i++) {
			tree[i][0] = tree[i][1] = 0;
			mn[i] = inf;
		}
		tot = 0;
	}
	void insert(int x, ll c, int b) {
		int u = 0;
		mn[u] = min(mn[u], c);
		for(int i = b; i >= 0; i--) {
			int val = (x >> i) & 1;
			if(!tree[u][val]) {
				tree[u][val] = ++tot;
				mn[tot] = inf;
			}
			u = tree[u][val];
			mn[u] = min(mn[u], c);
		}
	}
	ll query(int x, int lim, int b) {
		int u = 0;
		ll ans = inf;
		for(int i = b; i >= 0; i--) {
			int val = (x >> i) & 1;
			if((lim >> i) & 1) u = tree[u][val ^ 1];
			else {
				int v = tree[u][val ^ 1];
				if(v) ans = min(ans, mn[v]);
				u = tree[u][val];
			}
			if(!u) return ans;
		}
		return min(ans, mn[u]);
	}
}trie;
bool check(int x) {
	int b = 0;
	while((1 << (b + 1)) <= x) b++;
	vector<ll> v;
	for(int l = 1, r; l <= n; l = r) {
		r = l;
		ll c1 = inf, c2 = inf;
		trie.clear();
		while(r <= n && (a[r].a >> (b + 1)) == (a[l].a >> (b + 1))) {
			c1 = min(c1, a[r].c);
			if((a[r].a >> b) & 1)
				c2 = min(c2, a[r].c + trie.query(a[r].a, x - (1 << b), b - 1));
			else trie.insert(a[r].a, a[r].c, b - 1);
			r++;
		}
		v.push_back(c1);
		if(c2 < inf) v.push_back(c2 - c1);
	}
	if((int)v.size() < k) return 0;
	sort(v.begin(), v.end());
	ll sum = 0;
	for(int i = 0; i < k; i++) sum += v[i];
	return sum <= m;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k >> m;
		vector<ll> v;
		for(int i = 1; i <= n; i++) cin >> a[i].a >> a[i].c, v.push_back(a[i].c);
		sort(v.begin(), v.end());
		ll sum = 0;
		for(int i = 0; i < k; i++) sum += v[i];
		if(sum > m) {
			cout << -1 << '\n';
			continue;
		}
		sort(a + 1, a + n + 1, cmp);
		int l = 0, r = 1 << 20;
		while(l + 1 < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) l = mid;
			else r = mid;
		}
		cout << l << '\n';
	}
	return 0;
}
