#include<bits/stdc++.h>
using namespace std;
int n, m, k, a[20], b[20], cnt[205][20], val[205][20];
bool ac[205][20];
string name[205];
map<string, int> id;
int main() {
	freopen("score.in", "r", stdin);
	freopen("score.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> name[i], id[name[i]] = i;
	for(int i = 1; i <= k; i++) cin >> a[i] >> b[i];
	while(m--) {
		int h, mm, p; char c; string s, status;
		cin >> h >> c >> mm >> p >> s >> status;
		int u = id[s];
		if(ac[u][p]) val[u][p] = max(0, val[u][p] - 50);
		else if(status == "WA") cnt[u][p]++;
		else {
			ac[u][p] = 1;
			val[u][p] = max(0, a[p] - b[p] * (h * 60 + mm) - 50 * cnt[u][p]);
		}
	}
	for(int i = 1; i <= n; i++) {
		int ans = 0;
		for(int j = 1; j <= k; j++) ans += val[i][j];
		cout << name[i] << ' ' << ans << '\n';
	}
	return 0;
}
