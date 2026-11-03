#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1 << 20;
int n, m, c, f[maxn], q[maxn];
void modify(int x) {
	if(f[x] == 1) return;
	int l = 0, r = 0;
	f[x] = 1, q[r++] = x;
	while(l < r) {
		int u = q[l++];
		for(int i = 0; i < m; i++) {
			int v = u ^ (1 << i);
			if(f[v] > f[u] + 1) {
				f[v] = f[u] + 1;
				q[r++] = v;
			}
		}
	}
}
int main() {
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m >> c;
	fill(f, f + (1 << m), c);
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s;
		int x = 0;
		for(char ch : s) x = x * 2 + ch - '0';
		ans += f[x];
		modify(x);
	}
	cout << ans << '\n';
	return 0;
}
