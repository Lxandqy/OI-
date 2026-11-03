#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m;
ll k[maxn], b[maxn];
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	while(m--) {
		int l, r; cin >> l >> r;
		k[l]++, k[r + 1]--, b[l] += 1 - l, b[r + 1] -= 1 - l;
	}
	for(int i = 1; i <= n; i++) {
		k[i] += k[i - 1], b[i] += b[i - 1];
		cout << k[i] * i + b[i] << (i == n ? '\n' : ' ');
	}
	return 0;
}
