#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m, fa[maxn], siz[maxn], tag[maxn], val[maxn];
void init() {
	for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
}
int get(int x) {
	if(fa[x] == x) return x;
	int p = fa[x];
	fa[x] = get(p), val[x] += val[p];
	return fa[x];
}
void merge(int x, int y) {
	x = get(x), y = get(y);
	if(x == y) return;
	if(siz[x] > siz[y]) swap(x, y);
	fa[x] = y, siz[y] += siz[x], val[x] = tag[x] - tag[y];
}
int main() {
	freopen("gossip.in", "r", stdin);
	freopen("gossip.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	init();
	while(m--) {
		int opt, x, y; cin >> opt >> x >> y;
		if(opt == 1) merge(x, y);
		else tag[get(x)] += y;
	}
	for(int i = 1; i <= n; i++) {
		int rt = get(i);
		cout << val[i] + tag[rt] << (i == n ? '\n' : ' ');
	}
	return 0;
}
