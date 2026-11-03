#include<bits/stdc++.h>
using namespace std;
const int maxn = 105;
int n, m, sx, sy, tx, ty, a[maxn][maxn];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
long double s, dis[maxn][maxn];
bool vis[maxn][maxn];
struct Node {
	int x, y;
	long double dis;
	bool operator < (const Node &v) const { return dis > v.dis; }
};
long double dij(long double k) {
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) dis[i][j] = 1e30, vis[i][j] = 0;
	priority_queue<Node> q;
	dis[sx][sy] = 0; q.push({sx, sy, 0});
	while(!q.empty()) {
		Node u = q.top(); q.pop();
		int x = u.x, y = u.y;
		if(vis[x][y]) continue;
		vis[x][y] = 1;
		if(x == tx && y == ty) return dis[x][y];
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny]) continue;
			long double val = dis[x][y] + (i < 2 ? k : 1);
			if(dis[nx][ny] > val) dis[nx][ny] = val, q.push({nx, ny, val});
		}
	}
	return dis[tx][ty];
}
int main() {
	freopen("msg.in", "r", stdin);
	freopen("msg.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m >> sx >> sy >> tx >> ty;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];
	cin >> s;
	long double l = 0, r = s;
	for(int i = 1; i <= 75; i++) {
		long double mid = (l + r) / 2;
		if(dij(mid) >= s) r = mid;
		else l = mid;
	}
	cout << fixed << setprecision(3) << r << '\n';
	return 0;
}
