#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
int n, m, a[maxn], num[maxn], cnt[maxn], seen[maxn], len;
ll ans[maxn], val[maxn];
vector<int> pos[maxn];
struct Query { int x, y, id; }q[maxn];
vector<Query> ask[maxn];
int get(int x) {
	int l = 1, r = len;
	while(l <= r) {
		int mid = l + r >> 1;
		if(num[mid] == x) return mid;
		if(num[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	return 0;
}
ll query(int x, int y) {
	ll res = 0;
	int j = 0;
	for(int i = 0; i < (int)pos[x].size(); i++) {
		while(j < (int)pos[y].size() && pos[y][j] <= pos[x][i]) j++;
		res = max(res, 1ll * (i + 1) * (cnt[y] - j));
	}
	return res;
}
int main() {
	freopen("occurrences.in", "r", stdin);
	freopen("occurrences.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i], num[i] = a[i];
	sort(num + 1, num + n + 1);
	len = unique(num + 1, num + n + 1) - num - 1;
	for(int i = 1; i <= n; i++) a[i] = get(a[i]), cnt[a[i]]++, pos[a[i]].push_back(i);
	int block = sqrt(n) + 1;
	for(int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		x = get(x), y = get(y);
		q[i] = {x, y, i};
		if(!x || !y) continue;
		if(cnt[x] >= block) ask[x].push_back(q[i]);
		else if(cnt[y] >= block) ask[y].push_back(q[i]);
		else ans[i] = query(x, y);
	}
	for(int h = 1; h <= len; h++) if(!ask[h].empty()) {
		fill(seen, seen + len + 1, 0);
		fill(val, val + len + 1, 0);
		for(int i = 1; i <= n; i++) {
			int x = a[i];
			val[x] = max(val[x], 1ll * seen[h] * (cnt[x] - seen[x]));
			seen[x]++;
		}
		for(Query v : ask[h]) if(v.x == h) ans[v.id] = val[v.y];
		fill(seen, seen + len + 1, 0);
		fill(val, val + len + 1, 0);
		for(int i = n; i >= 1; i--) {
			int x = a[i];
			val[x] = max(val[x], 1ll * seen[h] * (cnt[x] - seen[x]));
			seen[x]++;
		}
		for(Query v : ask[h]) if(v.x != h) ans[v.id] = val[v.x];
	}
	for(int i = 1; i <= m; i++) cout << ans[i] << '\n';
	return 0;
}
