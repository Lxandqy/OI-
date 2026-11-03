#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m, p[6][3], mul[6][6], id[3][3][3];
char a[maxn];
struct Node {
	int l, r, f[6][3], tag;
}tree[maxn << 2];
void init() {
	int v[3] = {0, 1, 2}, cnt = 0;
	do {
		for(int j = 0; j < 3; j++) p[cnt][j] = v[j];
		id[v[0]][v[1]][v[2]] = cnt++;
	}while(next_permutation(v, v + 3));
	for(int i = 0; i < 6; i++) for(int j = 0; j < 6; j++)
		mul[i][j] = id[p[i][p[j][0]]][p[i][p[j][1]]][p[i][p[j][2]]];
}
void push_up(int i) {
	for(int j = 0; j < 6; j++) for(int x = 0; x < 3; x++)
		tree[i].f[j][x] = tree[i << 1 | 1].f[j][tree[i << 1].f[j][x]];
}
void get(int i, int t) {
	int f[6][3];
	for(int j = 0; j < 6; j++) for(int x = 0; x < 3; x++) f[j][x] = tree[i].f[mul[j][t]][x];
	memcpy(tree[i].f, f, sizeof f);
	tree[i].tag = mul[t][tree[i].tag];
}
void push_down(int i) {
	if(!tree[i].tag) return;
	get(i << 1, tree[i].tag), get(i << 1 | 1, tree[i].tag);
	tree[i].tag = 0;
}
void build(int i, int l, int r) {
	tree[i].l = l, tree[i].r = r;
	if(l == r) {
		for(int j = 0; j < 6; j++) for(int x = 0; x < 3; x++) {
			int y = p[j][a[l] - 'A'];
			tree[i].f[j][x] = (x + 1) % 3 == y ? x : y;
		}
		return;
	}
	int mid = (l + r) >> 1;
	build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r);
	push_up(i);
}
void modify(int i, int l, int r, int t) {
	if(l <= tree[i].l && tree[i].r <= r) { get(i, t); return; }
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) modify(i << 1, l, r, t);
	if(r > mid) modify(i << 1 | 1, l, r, t);
	push_up(i);
}
int query(int i, int l, int r, int x) {
	if(l <= tree[i].l && tree[i].r <= r) return tree[i].f[0][x];
	push_down(i);
	int mid = (tree[i].l + tree[i].r) >> 1;
	if(l <= mid) x = query(i << 1, l, r, x);
	if(r > mid) x = query(i << 1 | 1, l, r, x);
	return x;
}
int main() {
	freopen("jkp.in", "r", stdin);
	freopen("jkp.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
cin >> n >> m >> (a + 1);
	init(); build(1, 1, n);
	while(m--) {
		int op, l, r; char x, y;
		cin >> op >> l >> r >> x;
		if(op) cout << char('A' + query(1, l, r, x - 'A')) << '\n';
		else {
			cin >> y;
			int v[3] = {0, 1, 2}; swap(v[x - 'A'], v[y - 'A']);
			modify(1, l, r, id[v[0]][v[1]][v[2]]);
		}
	}
	return 0;
}
