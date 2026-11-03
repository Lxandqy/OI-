#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, fa[maxn], dep[maxn], cnt[maxn];
vector<int> day[maxn];
priority_queue<pair<int, int>> q;
int main() {
	freopen("boss.in", "r", stdin);
	freopen("boss.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m;
	dep[1] = 1;
	for(int i = 2; i <= n; i++) cin >> fa[i], dep[i] = dep[fa[i]] + 1, cnt[fa[i]]++;
	for(int i = 1; i <= n; i++) if(!cnt[i]) q.push({dep[i], i});
	int ans = 0;
	while(!q.empty()) {
		ans++;
		for(int i = 1; i <= m && !q.empty(); i++) {
			int u = q.top().second; q.pop();
			day[ans].push_back(u);
		}
		for(int u : day[ans]) if(fa[u] && !--cnt[fa[u]]) q.push({dep[fa[u]], fa[u]});
	}
	cout << ans << '\n';
	for(int i = ans; i >= 1; i--) {
		cout << day[i].size();
		for(int u : day[i]) cout << ' ' << u;
		cout << '\n';
	}
	return 0;
}
