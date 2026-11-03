#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int n, k, a[maxn];
bool vis[maxn];
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	if(n < 2 * k) { cout << -1 << '\n'; return 0; }
	int pos = 1;
	for(int i = 1; i <= n; i++) {
		while(vis[pos]) pos++;
		if(i > n - 2 * k && i <= n - k) a[i] = i + k;
		else a[i] = pos <= i - k ? pos : i + k;
		vis[a[i]] = 1;
	}
	for(int i = 1; i <= n; i++) cout << a[i] << (i == n ? '\n' : ' ');
	return 0;
}
