#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 505;
int n, q, c[maxn][maxn], row[maxn][maxn], col[maxn][maxn];
ll dis[maxn][maxn], sum[maxn][maxn], cnt[maxn][maxn], ans[maxn][maxn];
void init() {
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) row[i][j] = col[i][j] = j;
		sort(row[i] + 1, row[i] + n + 1, [i](int x, int y) { return dis[i][x] < dis[i][y]; });
		sort(col[i] + 1, col[i] + n + 1, [i](int x, int y) { return dis[x][i] < dis[y][i]; });
	}
}
void solve(int s) {
	memset(sum, 0, sizeof(sum));
	memset(cnt, 0, sizeof(cnt));
	for(int t = 1; t <= n; t++) {
		if(!c[s][t]) continue;
		int pos = n;
		for(int i = 1; i <= n; i++) {
			int y = col[t][i];
			ll val = dis[s][t] - dis[y][t];
			while(pos && dis[s][row[s][pos]] >= val) pos--;
			if(!pos) break;
			sum[y][pos] += val * c[s][t];
			cnt[y][pos] += c[s][t];
		}
	}
	for(int y = 1; y <= n; y++)
		for(int i = n; i >= 1; i--) {
			sum[y][i] += sum[y][i + 1], cnt[y][i] += cnt[y][i + 1];
			int x = row[s][i];
			ans[x][y] += sum[y][i] - cnt[y][i] * dis[s][x];
		}
}
int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) cin >> dis[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) cin >> c[i][j];
	init();
	ll tot = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) tot += c[i][j] * dis[i][j];
		solve(i);
	}
	while(q--) {
		int x, y; cin >> x >> y;
		cout << tot - ans[x][y] - ans[y][x] << '\n';
	}
	return 0;
}
