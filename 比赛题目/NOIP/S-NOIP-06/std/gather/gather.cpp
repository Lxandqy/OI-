#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 2e5 + 10;
const ll inf = 4e18;
int n, m, k, c[maxn], cnt[maxn];
ll dis[maxn * 2], sum[maxn];
bool vis[maxn * 2];
struct Node {
	int pos;
	ll dis;
	bool operator < (const Node &x) const {
		return dis > x.dis;
	}
};

void dij(int s, int d) {
	for(int i = 0; i < 2 * n * m; i++) dis[i] = inf, vis[i] = 0;
	priority_queue<Node> q;
	dis[s * 2 + d] = 0;
	q.push({s * 2 + d, 0});
	while(!q.empty()) {
		int u = q.top().pos;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		int p = u / 2, dir = u & 1;
		int x = p / m, y = p % m;
		if(dis[u ^ 1] > dis[u] + c[p]) {
			dis[u ^ 1] = dis[u] + c[p];
			q.push({u ^ 1, dis[u ^ 1]});
		}
		for(int i = -1; i <= 1; i += 2) {
			int nx = x + (dir == 1 ? i : 0);
			int ny = y + (dir == 0 ? i : 0);
			if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			int v = nx * m + ny;
			if(c[v] == -1) continue;
			v = v * 2 + dir;
			if(dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.push({v, dis[v]});
			}
		}
	}
	for(int i = 0; i < n * m; i++) {
		// 各车到达时的朝向可以不同，先取最小值再相加。
		ll val = min(dis[i * 2], dis[i * 2 + 1]);
		if(val != inf) sum[i] += val, cnt[i]++;
	}
}

int main() {
	freopen("gather.in", "r", stdin);
	freopen("gather.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 0; i < n * m; i++) cin >> c[i];
	for(int i = 1; i <= k; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		dij((x - 1) * m + y - 1, d);
	}
	ll ans = inf;
	int ways = 0;
	for(int i = 0; i < n * m; i++) {
		if(c[i] == -1 || cnt[i] != k) continue;
		if(sum[i] < ans) ans = sum[i], ways = 1;
		else if(sum[i] == ans) ways++;
	}
	if(!ways) cout << "-1 0\n";
	else cout << ans << ' ' << ways << '\n';
	return 0;
}
