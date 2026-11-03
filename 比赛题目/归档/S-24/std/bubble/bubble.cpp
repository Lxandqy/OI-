#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
int n, q, a[maxn], pos[maxn], rev[maxn], c[maxn], t[maxn << 1], ans[maxn];
vector<int> G[maxn];
struct Node { int k, x, id; }querys[maxn];
int lowbit(int x) { return x & -x; }
void modify(int *c, int n, int x, int val) {
	for(int i = x; i <= n; i += lowbit(i)) c[i] += val;
}
int query(int *c, int x) {
	int ans = 0;
	for(int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}
int get(int k) {
	int x = 0;
	for(int i = 20; i >= 0; i--)
		if(x + (1 << i) <= 2 * n && t[x + (1 << i)] < k) {
			x += 1 << i; k -= t[x];
		}
	return x + 1;
}
bool cmp(Node x, Node y) { return x.k < y.k; }
int main() {
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; pos[a[i]] = i;
		rev[a[i]] = i - 1 - query(c, a[i]);
		G[rev[a[i]]].push_back(i);
		modify(c, n, a[i], 1);
	}
	fill(c, c + n + 1, 0);
	cin >> q;
	for(int i = 1; i <= q; i++) cin >> querys[i].k >> querys[i].x, querys[i].id = i;
	sort(querys + 1, querys + q + 1, cmp);
	int now = 0;
	for(int i = 1; i <= q; i++) {
		int k = querys[i].k, x = querys[i].x, id = querys[i].id;
		while(now < k) {
			for(int j : G[now]) modify(c, n, a[j], 1), modify(t, 2 * n, j, 1);
			now++;
			modify(t, 2 * n, now, -1);
			modify(t, 2 * n, n + now, 1);
		}
		if(rev[x] >= k) ans[id] = pos[x] - k;
		else ans[id] = get(query(c, x)) - k;
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
