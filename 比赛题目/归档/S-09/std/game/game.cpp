#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 10;
int n, k, pre[maxn], nxt[maxn];
ll a[maxn];
bool vis[maxn];
struct Node {
	int pos; ll val;
	bool operator < (const Node &x) const { return val == x.val ? pos > x.pos : val > x.val; }
};
priority_queue<Node> q;
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; pre[i] = i - 1, nxt[i] = i + 1;
		q.push({i, a[i]});
	}
	nxt[0] = 1;
	while(k--) {
		while(vis[q.top().pos] || q.top().val != a[q.top().pos]) q.pop();
		int u = q.top().pos; q.pop();
		vis[u] = 1;
		int l = pre[u], r = nxt[u];
		if(l) a[l] += a[u], q.push({l, a[l]});
		if(r <= n) a[r] += a[u], q.push({r, a[r]});
		nxt[l] = r, pre[r] = l;
	}
	for(int i = nxt[0]; i <= n; i = nxt[i]) cout << a[i] << (nxt[i] > n ? '\n' : ' ');
	return 0;
}
