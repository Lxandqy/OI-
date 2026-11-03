#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 200010;
int n, fa[maxn], sz[maxn], mx[maxn], cnt;
ll sum[maxn], ans;
struct Node {
	int l, r, w;
}a[maxn];
set<pair<int, int> > s;

bool cmp(Node x, Node y) {
	return x.l < y.l;
}

int get(int x) {
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}

void merge(int x, int y) {
	x = get(x), y = get(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
	sum[x] += sum[y];
	mx[x] = max(mx[x], mx[y]);
	cnt--;
}

int main() {
	freopen("crossweave.in", "r", stdin);
	freopen("crossweave.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].w;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		fa[i] = i, sz[i] = 1, mx[i] = a[i].r, sum[i] = a[i].w;
		cnt++;
		while(!s.empty() && s.begin()->first < a[i].l) s.erase(s.begin());
		auto it = s.begin();
		while(it != s.end() && it->first < a[i].r) {
			int u = get(it->second);
			it = s.upper_bound(make_pair(mx[u], n + 1));
			merge(i, u);
		}
		s.insert(make_pair(a[i].r, i));
		ans = max(ans, sum[get(i)]);
		cout << cnt << ' ' << ans << '\n';
	}
	return 0;
}
