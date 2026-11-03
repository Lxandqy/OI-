#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, k, a[maxn], stk[maxn], top, b[maxn], cnt;
int main() {
	freopen("stand.in", "r", stdin);
	freopen("stand.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		sort(a + 1, a + n + 1);
		top = cnt = 0;
		int x = a[1], j = 1, num = 0;
		while(j <= n || top) {
			if(!top) x = a[j];
			if(j <= n && a[j] == x) {
				num++, j++;
				while(j <= n && a[j] == x) stk[++top] = a[j++];
			}
			else b[++cnt] = x - stk[top--];
			x++;
		}
		sort(b + 1, b + cnt + 1);
		ll ans = 0;
		for(int i = 1; i <= k - num; i++) ans += b[i];
		cout << ans << '\n';
	}
	return 0;
}
