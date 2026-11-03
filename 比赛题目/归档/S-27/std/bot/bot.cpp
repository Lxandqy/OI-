#include<bits/stdc++.h>
using namespace std;
const int maxn = 55;
int n, m, len, sx, sy, ex, ey;
char a[maxn][maxn], s[maxn];
int dis[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
string dir = "UDLR";
struct Node { int x, y, k; };
deque<Node> q;
bool check(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m || a[x][y] == '#') return 0;
	return 1;
}
void update(int x, int y, int k, int val, int w) {
	if(val >= dis[x][y][k]) return;
	dis[x][y][k] = val;
	if(w) q.push_back({x, y, k});
	else q.push_front({x, y, k});
}
int bfs() {
	memset(dis, 0x3f, sizeof(dis));
	update(sx, sy, 0, 0, 0);
	while(!q.empty()) {
		Node u = q.front(); q.pop_front();
		int x = u.x, y = u.y, k = u.k, d = dis[x][y][k];
		if(vis[x][y][k]) continue;
		vis[x][y][k] = 1;
		if(x == ex && y == ey) return d;
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if(check(nx, ny)) update(nx, ny, k, d + 1, 1);
		}
		if(k == len) continue;
		update(x, y, k + 1, d + 1, 1);
		int t = dir.find(s[k + 1]);
		int nx = x + dx[t], ny = y + dy[t];
		if(!check(nx, ny)) nx = x, ny = y;
		update(nx, ny, k + 1, d, 0);
	}
	return -1;
}
int main() {
	freopen("bot.in", "r", stdin);
	freopen("bot.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> (a[i] + 1);
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 'R') sx = i, sy = j;
			if(a[i][j] == 'E') ex = i, ey = j;
		}
	}
	cin >> (s + 1); len = strlen(s + 1);
	cout << bfs() << '\n';
	return 0;
}
