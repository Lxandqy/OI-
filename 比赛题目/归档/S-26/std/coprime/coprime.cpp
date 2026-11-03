#include<bits/stdc++.h>
using namespace std;
const int maxn = 2005;
int n, a[maxn];
bool edge[maxn][maxn], vis[maxn];
vector<int> G[maxn];
priority_queue<int> q;
int gcd(int x, int y) {
	return y ? gcd(y, x % y) : x;
}
void dfs(int u) {
	vis[u] = 1;
	for(int v = 1; v <= n; v++)
		if(!vis[v] && edge[u][v]) {
			G[u].push_back(v);
			dfs(v);
		}
}
int main() {
	freopen("coprime.in", "r", stdin);
	freopen("coprime.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < i; j++)
			if(gcd(a[i], a[j]) > 1) edge[i][j] = edge[j][i] = 1;
	for(int i = 1; i <= n; i++)
		if(!vis[i]) q.push(i), dfs(i);
	int cnt = 0;
	while(!q.empty()) {
		int u = q.top(); q.pop();
		cout << a[u] << (++cnt == n ? '\n' : ' ');
		for(int v : G[u]) q.push(v);
	}
	return 0;
}
