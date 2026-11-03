#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 200005, maxm = 400005;
int n, m, head[maxn], tot, lim;
int dfn[maxn], low[maxn], stk[maxn], top, cnt;
int col[maxn], num, out[maxn], ans;
bool vis[maxn];
struct Edge {
	int to, nxt, w;
}e[maxm];

void add(int x, int y, int w) {
	e[++tot] = {y, head[x], w};
	head[x] = tot;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++cnt;
	stk[++top] = x;
	vis[x] = 1;
	for(int i = head[x]; i; i = e[i].nxt) {
		if(e[i].w > lim) continue;
		int y = e[i].to;
		if(!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if(vis[y]) low[x] = min(low[x], dfn[y]);
	}
	if(low[x] == dfn[x]) {
		++num;
		int y;
		do {
			y = stk[top--];
			vis[y] = 0;
			col[y] = num;
		}while(x != y);
	}
}

bool check(int x) {
	lim = x;
	cnt = num = top = ans = 0;
	for(int i = 1; i <= n; i++) dfn[i] = out[i] = 0;
	for(int i = 1; i <= n; i++) {
		if(!dfn[i]) tarjan(i);
	}
	for(int x = 1; x <= n; x++) {
		for(int i = head[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if(e[i].w <= lim && col[x] != col[y]) out[col[x]] = 1;
		}
	}
	// 只有一个出度为零的分量时，其中的点才都能作为起点。
	for(int i = 1; i <= num; i++) {
		if(out[i]) continue;
		if(ans) return false;
		ans = i;
	}
	return true;
}

int main() {
	freopen("cruise.in", "r", stdin);
	freopen("cruise.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	int l = 0, r = 0;
	for(int i = 1; i <= n; i++) {
		int d, x;
		cin >> d;
		r = max(r, d - 1);
		for(int j = 1; j <= d; j++) {
			cin >> x;
			// 原列表最后一条航线无需调整，其余第 j 条需要左移 j 次。
			add(i, x, j == d ? 0 : j);
		}
	}
	while(l < r) {
		int mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	check(l);
	int sum = 0;
	for(int i = 1; i <= n; i++) sum += col[i] == ans;
	cout << l << '\n' << sum << '\n';
	for(int i = 1; i <= n; i++) {
		if(col[i] == ans) cout << i << ' ';
	}
	cout << '\n';
	return 0;
}
