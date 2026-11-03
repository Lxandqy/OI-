#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, a[maxn], vis[maxn];
ll cnt[maxn];
int main() {
	freopen("practice.in", "r", stdin);
	freopen("practice.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 0; i <= n + 2; i++) vis[i] = cnt[i] = 0;
		int p = 0, q = 1;
		ll sum = 0;
		for(int i = 0; i <= n; i++) {
			if(i) vis[a[i]] = 1;
			while(vis[p]) p++;
			q = max(q, p + 1);
			while(vis[q]) q++;
			// 当前前缀只有补上 p，进度才会从 p 增至 q。
			sum += p, cnt[p] += q - p;
		}
		ll ans = -1;
		int num = 0;
		for(int i = 0; i <= n; i++) {
			if(cnt[i] > ans) ans = cnt[i], num = 1;
			else if(cnt[i] == ans) num++;
		}
		cout << sum + ans << ' ' << num << '\n';
	}
	return 0;
}
