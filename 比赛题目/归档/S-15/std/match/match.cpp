#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, q, pos[maxn][4], d[maxn];
struct Node {
	int l, r, mn, add;
}tree[maxn << 2];
void push_up(int i) {
	tree[i].mn = min(tree[i << 1].mn, tree[i << 1 | 1].mn);
}
void push_down(int i) {
	int k = tree[i].add;
	if(!k) return;
	tree[i << 1].mn += k, tree[i << 1].add += k;
	tree[i << 1 | 1].mn += k, tree[i << 1 | 1].add += k;
	tree[i].add = 0;
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) { tree[i].mn = d[l]; return; }
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void modify(int i, int l, int r, int k) {
	if(l <= tree[i].l && tree[i].r <= r) {
		tree[i].mn += k, tree[i].add += k;
		return;
	}
	push_down(i);
	if(tree[i << 1].r >= l) modify(i << 1, l, r, k);
	if(tree[i << 1 | 1].l <= r) modify(i << 1 | 1, l, r, k);
	push_up(i);
}
void change(int x, int k) {
	int l = min(pos[x][1], min(pos[x][2], pos[x][3]));
	int r = max(pos[x][1], max(pos[x][2], pos[x][3]));
	if(l < r) modify(1, l, r - 1, k);
}
int query(int i) {
	if(tree[i].l == tree[i].r) return tree[i].l;
	push_down(i);
	if(!tree[i << 1].mn) return query(i << 1);
	return query(i << 1 | 1);
}
int main() {
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= 3; i++)
		for(int j = 1, x; j <= n; j++) cin >> x, pos[x][i] = j;
	for(int x = 1; x <= n; x++) {
		int l = min(pos[x][1], min(pos[x][2], pos[x][3]));
		int r = max(pos[x][1], max(pos[x][2], pos[x][3]));
		d[l]++, d[r]--;
	}
	for(int i = 1; i <= n; i++) d[i] += d[i - 1];
	build(1, 1, n);
	while(q--) {
		int opt; cin >> opt;
		if(opt == 1) {
			int x; cin >> x;
			cout << (pos[x][1] <= query(1) ? "Yes" : "No") << '\n';
		}
		else {
			int p, a, b; cin >> p >> a >> b;
			change(a, -1), change(b, -1);
			swap(pos[a][p], pos[b][p]);
			change(a, 1), change(b, 1);
		}
	}
	return 0;
}
