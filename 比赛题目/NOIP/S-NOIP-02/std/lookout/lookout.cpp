#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 400010;
int n, h[maxn], s[maxn], top, pos;
ll w[maxn], f[maxn], ans = LLONG_MIN;
int main() {
	freopen("lookout.in", "r", stdin);
	freopen("lookout.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> h[i] >> w[i];
		h[i + n] = h[i], w[i + n] = w[i];
	}
	for(int i = n * 2; i >= 1; i--) {
		while(top && h[s[top]] <= h[i]) top--;
		f[i] = w[i] + (top ? f[s[top]] : 0);
		s[++top] = i;
	}
	for(int i = 1; i <= n; i++) {
		if(f[i] > ans) ans = f[i], pos = i;
	}
	cout << ans << ' ' << pos << '\n';
	return 0;
}
