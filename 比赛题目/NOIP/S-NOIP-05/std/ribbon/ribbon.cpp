#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, q, a[maxn];
ll tree[3][maxn];
struct Node {
	int l, r, c;
	bool operator < (const Node &x) const {return l < x.l;}
};
set<Node> s;
void add(int x, int v) {
	ll val[3] = {v, 1ll * v * x, 1ll * v * x * x};
	for(int i = x; i <= n; i += i & -i)
		for(int j = 0; j < 3; j++) tree[j][i] += val[j];
}
ll query(int id, int x) {
	ll ans = 0;
	for(int i = x; i; i -= i & -i) ans += tree[id][i];
	return ans;
}
set<Node>::iterator split(int x) {
	if(x > n) return s.end();
	auto it = --s.upper_bound({x, 0, 0});
	if(it->l == x) return it;
	int l = it->l, r = it->r, c = it->c;
	add(r - l + 1, -1), s.erase(it);
	s.insert({l, x - 1, c}); add(x - l, 1);
	add(r - x + 1, 1);
	return s.insert({x, r, c}).first;
}
void modify(int l, int r, int c) {
	auto right = split(r + 1), left = split(l);
	for(auto it = left; it != right;) {
		add(it->r - it->l + 1, -1);
		it = s.erase(it);
	}
	auto it = s.insert({l, r, c}).first;
	add(r - l + 1, 1);
	if(it != s.begin()) {
		auto pre = prev(it);
		if(pre->c == c) {
			l = pre->l;
			add(pre->r - pre->l + 1, -1), add(it->r - it->l + 1, -1);
			s.erase(pre), s.erase(it);
			it = s.insert({l, r, c}).first; add(r - l + 1, 1);
		}
	}
	auto nxt = next(it);
	if(nxt != s.end() && nxt->c == c) {
		add(nxt->r - nxt->l + 1, -1), add(it->r - it->l + 1, -1);
		r = nxt->r;
		s.erase(nxt), s.erase(it);
		s.insert({l, r, c}); add(r - l + 1, 1);
	}
}
int main() {
	freopen("ribbon.in", "r", stdin);
	freopen("ribbon.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int l = 1, r; l <= n; l = r + 1) {
		r = l;
		while(r < n && a[r + 1] == a[l]) r++;
		s.insert({l, r, a[l]}), add(r - l + 1, 1);
	}
	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int l, r, c; cin >> l >> r >> c;
			modify(l, r, c);
		}
		else {
			int k; cin >> k;
			ll val[3];
			for(int i = 0; i < 3; i++) val[i] = query(i, n) - query(i, k - 1);
			cout << (val[2] + (3ll - 2 * k) * val[1] + 1ll * (k - 1) * (k - 2) * val[0]) / 2 << '\n';
		}
	}
	return 0;
}
