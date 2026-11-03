#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, h[maxn], c[maxn], s[maxn], stk[maxn], top;
ll dis[maxn];
bool vis[maxn];
vector<int> G[maxn];
struct Node {
	int pos;
	ll dis;
	bool operator < (const Node &x) const {
		return x.dis < dis;
	}
};
void add(int u, int v) {
	G[u].push_back(v), G[v].push_back(u);
}
void dij() {
	priority_queue<Node> q;
	for(int i = 1; i <= n; i++) dis[i] = 4e18, vis[i] = 0;
	for(int i = 1; i <= k; i++) dis[s[i]] = 0, q.push({s[i], 0});
	while(!q.empty()) {
		int u = q.top().pos;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int v : G[u]) {
			if(dis[v] > dis[u] + c[u]) {
				dis[v] = dis[u] + c[u];
				q.push({v, dis[v]});
			}
		}
	}
}
int main() {
	freopen("message.in", "r", stdin);
	freopen("message.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> h[i];
		for(int i = 1; i <= n; i++) cin >> c[i];
		for(int i = 1; i <= k; i++) cin >> s[i];
		for(int i = 1; i <= n; i++) G[i].clear();
		top = 0;
		for(int i = 1; i <= n; i++) {
			while(top && h[stk[top]] < h[i]) top--;
			if(top) add(i, stk[top]);
			stk[++top] = i;
		}
		top = 0;
		for(int i = n; i >= 1; i--) {
			while(top && h[stk[top]] < h[i]) top--;
			if(top) add(i, stk[top]);
			stk[++top] = i;
		}
		dij();
		ll ans = 0;
		for(int i = 1; i <= n; i++) ans = max(ans, dis[i]);
		cout << ans << '\n';
	}
	return 0;
}
