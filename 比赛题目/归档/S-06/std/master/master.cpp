#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int f[18][18] = {
	{2, 2, 2, 2, 2, 1, 2, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{4, 2, 1, 1, 2, 4, 1, 0, 4, 2, 2, 2, 2, 1, 4, 2, 4, 1},
	{2, 4, 2, 2, 2, 1, 4, 2, 1, 2, 2, 4, 2, 2, 2, 2, 2, 4},
	{2, 2, 2, 1, 1, 1, 2, 1, 0, 2, 2, 4, 2, 2, 2, 2, 2, 4},
	{2, 2, 0, 4, 2, 4, 1, 2, 4, 4, 2, 1, 4, 2, 2, 2, 2, 2},
	{2, 1, 4, 2, 1, 2, 4, 2, 1, 4, 2, 2, 2, 2, 4, 2, 2, 2},
	{2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 4, 2, 4, 2, 2, 4, 1},
	{0, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 1, 2},
	{2, 2, 2, 2, 2, 4, 2, 2, 1, 1, 1, 2, 1, 2, 4, 2, 2, 4},
	{2, 2, 2, 2, 2, 1, 4, 2, 4, 1, 1, 4, 2, 2, 4, 1, 2, 2},
	{2, 2, 2, 2, 4, 4, 2, 2, 2, 4, 1, 1, 2, 2, 2, 1, 2, 2},
	{2, 2, 1, 1, 4, 4, 1, 2, 1, 1, 4, 1, 2, 2, 2, 1, 2, 2},
	{2, 2, 4, 2, 0, 2, 2, 2, 2, 2, 4, 1, 1, 2, 2, 1, 2, 2},
	{2, 4, 2, 4, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 0, 2},
	{2, 2, 4, 2, 4, 2, 2, 2, 1, 1, 1, 4, 2, 2, 1, 4, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 4, 2, 0},
	{2, 1, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 1, 1},
	{2, 4, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 4, 4, 2}
};
struct Node {
	int a, d, s, h, t[4], p[4], k, b[2];
}a[7], b[7];
void read(Node *a) {
	for(int i = 1; i <= 6; i++) {
		cin >> a[i].a >> a[i].d >> a[i].s >> a[i].h;
		for(int j = 0; j < 4; j++) cin >> a[i].t[j] >> a[i].p[j];
		cin >> a[i].k;
		for(int j = 0; j < a[i].k; j++) cin >> a[i].b[j];
	}
}
int cal(Node x, Node y) {
	int ans = 0;
	for(int i = 0; i < 4; i++) {
		ll p = 110ll * x.a * x.p[i], q = 250ll * y.d;
		for(int j = 0; j < y.k; j++) p *= f[x.t[i]][y.b[j]], q *= 2;
		for(int j = 0; j < x.k; j++) if(x.t[i] == x.b[j]) p *= 3, q *= 2;
		ans = max(ans, (int)(p / q));
	}
	return ans;
}
int main() {
	freopen("master.in", "r", stdin);
	freopen("master.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		read(a), read(b);
		int i = 1, j = 1;
		while(i <= 6 && j <= 6) {
			int x = cal(a[i], b[j]), y = cal(b[j], a[i]);
			if(!x) { i++; continue; }
			if(!y) { j++; continue; }
			int p = (b[j].h + x - 1) / x, q = (a[i].h + y - 1) / y;
			if(p < q || (p == q && a[i].s >= b[j].s)) {
				a[i].h -= (p - (a[i].s >= b[j].s)) * y;
				j++;
			}
			else {
				b[j].h -= (q - (b[j].s > a[i].s)) * x;
				i++;
			}
		}
		cout << (i <= 6 ? 'Y' : 'N') << '\n';
	}
	return 0;
}
