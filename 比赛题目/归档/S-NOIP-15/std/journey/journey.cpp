#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
int n, q1[maxn], q2[maxn];
ll k, l[maxn], r[maxn], p[maxn];
int main() {
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
		p[1] = 0;
		for(int i = 2; i <= n; i++) {
			int x; cin >> x;
			p[i] = p[i - 1] + x;
		}
		for(int i = 1; i <= n; i++) l[i] -= p[i], r[i] -= p[i];
		int h1 = 1, t1 = 0, h2 = 1, t2 = 0, now = 1;
		ll ans = 0;
		for(int i = 1; i <= n; i++) {
			while(h1 <= t1 && l[q1[t1]] <= l[i]) t1--;
			while(h2 <= t2 && r[q2[t2]] >= r[i]) t2--;
			q1[++t1] = i, q2[++t2] = i;
			while(l[q1[h1]] > r[i] || p[i] - p[now] + max(0ll, l[q1[h1]] - r[q2[h2]]) > k) {
				now++;
				if(q1[h1] < now) h1++;
				if(q2[h2] < now) h2++;
			}
			ans += i - now + 1;
		}
		cout << ans << '\n';
	}
	return 0;
}
