#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 10;
int n, k, L, R, f[maxn][20], Log[maxn];
ll sum[maxn];
int get(int x, int y) {
	return sum[x] >= sum[y] ? x : y;
}
void init() {
	for(int i = 2; i <= n; i++) Log[i] = Log[i / 2] + 1;
	for(int i = 1; i <= n; i++) f[i][0] = i;
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			f[i][j] = get(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}
int query(int l, int r) {
	int t = Log[r - l + 1];
	return get(f[l][t], f[r - (1 << t) + 1][t]);
}
struct Node {
	int o, l, r, pos;
	ll val;
	bool operator < (const Node &x) const { return val < x.val; }
};
priority_queue<Node> q;
void add(int o, int l, int r) {
	if(l > r) return;
	int pos = query(l, r);
	q.push({o, l, r, pos, sum[pos] - sum[o - 1]});
}
int main() {
	freopen("feast.in", "r", stdin);
	freopen("feast.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k >> L >> R;
	for(int i = 1; i <= n; i++) cin >> sum[i], sum[i] += sum[i - 1];
	init();
	for(int i = 1; i + L - 1 <= n; i++) add(i, i + L - 1, min(n, i + R - 1));
	ll ans = 0;
	while(k--) {
		Node u = q.top(); q.pop();
		ans += u.val;
		add(u.o, u.l, u.pos - 1);
		add(u.o, u.pos + 1, u.r);
	}
	cout << ans << '\n';
	return 0;
}
