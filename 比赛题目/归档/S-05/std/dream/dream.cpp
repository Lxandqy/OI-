#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
int n, f[maxn][4];
int main() {
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	memset(f, -0x3f, sizeof(f));
	f[0][3] = 0;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		for(int j = i; j >= 1; j--) {
			int a = max(f[j][0], f[j - 1][3]);
			int b = max(f[j][1], a + x), c = max(f[j][2], a - x);
			int d = max(max(f[j][3], a), max(f[j][1] - x, f[j][2] + x));
			f[j][0] = a, f[j][1] = b, f[j][2] = c, f[j][3] = d;
		}
	}
	for(int i = 1; i <= n; i++) cout << f[i][3] << '\n';
	return 0;
}
