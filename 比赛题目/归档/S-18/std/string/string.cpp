#include<bits/stdc++.h>
using namespace std;
const int maxn = 410, inf = 1e9;
int n, cnt[3], pos[3][maxn], pre[maxn][3];
int f[2][205][205][3];
string s;
int cal(int x, int i, int j, int k) {
	int p = pos[x][(x == 0 ? i : x == 1 ? j : k) + 1];
	return p - 1 - min(i, pre[p - 1][0]) - min(j, pre[p - 1][1]) - min(k, pre[p - 1][2]);
}
int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> s;
	n = s.size();
	for(int i = 1; i <= n; i++) {
		int x = s[i - 1] - '0';
		pos[x][++cnt[x]] = i;
		for(int j = 0; j < 3; j++) pre[i][j] = pre[i - 1][j] + (x == j);
	}
	for(int x = 0; x < 3; x++) if(cnt[x] > (n + 1) / 2) { cout << -1 << '\n'; return 0; }
	for(int i = 0; i <= cnt[0]; i++) {
		int cur = i & 1;
		memset(f[cur], 0x3f, sizeof(f[cur]));
		if(!i) f[cur][0][0][0] = f[cur][0][0][1] = f[cur][0][0][2] = 0;
		for(int j = 0; j <= cnt[1]; j++) for(int k = 0; k <= cnt[2]; k++) {
			if(i) f[cur][j][k][0] = min(f[cur ^ 1][j][k][1], f[cur ^ 1][j][k][2]) + cal(0, i - 1, j, k);
			if(j) f[cur][j][k][1] = min(f[cur][j - 1][k][0], f[cur][j - 1][k][2]) + cal(1, i, j - 1, k);
			if(k) f[cur][j][k][2] = min(f[cur][j][k - 1][0], f[cur][j][k - 1][1]) + cal(2, i, j, k - 1);
		}
	}
	int ans = inf;
	for(int x = 0; x < 3; x++) ans = min(ans, f[cnt[0] & 1][cnt[1]][cnt[2]][x]);
	cout << ans << '\n';
	return 0;
}
