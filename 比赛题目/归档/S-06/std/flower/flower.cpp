#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m, a[maxn], q[maxn];
int main() {
	freopen("flower.in", "r", stdin);
	freopen("flower.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int l = 1, r = 0, p = 0;
	for(int i = 1; i <= n; i++) {
		while(p < min(n, i + m)) {
			p++;
			while(l <= r && a[q[r]] <= a[p]) r--;
			q[++r] = p;
		}
		while(l <= r && q[l] < i - m) l++;
		cout << a[q[l]] + m << (i == n ? '\n' : ' ');
	}
	return 0;
}
