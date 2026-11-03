#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 100005;
int n, m, k, u[maxn], v[maxn], d[maxn], pos[maxn], now[maxn];
int g[maxn << 1], q[maxn], a[maxn], cnt, l, r;
bool vis[maxn];

bool check() {
	for(int i = 1; i <= cnt; i++) {
		for(int j = i + 1; j <= cnt; j++) {
			int x = a[i], y = a[j];
			if(pos[x + 1] - pos[x] > pos[y + 1] - pos[y]) swap(x, y);
			int l = pos[x] + 1, r = pos[x + 1];
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(g[mid] == y) break;
				if(g[mid] < y) l = mid + 1;
				else r = mid - 1;
			}
			if(l > r) return 0;
		}
	}
	return 1;
}

int main() {
	freopen("rally.in", "r", stdin);
	freopen("rally.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i];
		d[u[i]]++;
		d[v[i]]++;
	}
	// 邻接点连续存放，排序后可以二分查边。
	for(int i = 1; i <= n; i++) {
		pos[i + 1] = pos[i] + d[i];
		now[i] = pos[i];
	}
	for(int i = 1; i <= m; i++) {
		g[++now[u[i]]] = v[i];
		g[++now[v[i]]] = u[i];
	}
	for(int i = 1; i <= n; i++) {
		sort(g + pos[i] + 1, g + pos[i + 1] + 1);
		if(d[i] < k) q[++r] = i;
	}
	l = 1;
	while(l <= r) {
		int x = q[l++];
		// 只在还剩 k-1 个邻居时，才可能找到包含 x 的 k 团。
		if(d[x] == k - 1 && 1ll * k * (k - 1) <= 2 * m) {
			cnt = 0;
			for(int i = pos[x] + 1; i <= pos[x + 1]; i++) {
				if(!vis[g[i]]) a[++cnt] = g[i];
			}
			if(check()) {
				cout << 2 << '\n' << x;
				for(int i = 1; i <= cnt; i++) cout << ' ' << a[i];
				cout << '\n';
				return 0;
			}
		}
		vis[x] = true;
		for(int i = pos[x] + 1; i <= pos[x + 1]; i++) {
			int y = g[i];
			if(vis[y]) continue;
			if(--d[y] == k - 1) q[++r] = y;
		}
	}
	// 队列清空后，留下的每个点都有至少 k 个现存邻居。
	cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) a[++cnt] = i;
	}
	if(!cnt) cout << -1 << '\n';
	else {
		cout << 1 << ' ' << cnt << '\n';
		for(int i = 1; i <= cnt; i++) cout << a[i] << " \n"[i == cnt];
	}
	return 0;
}
