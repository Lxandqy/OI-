#include<bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 10;
int n, m, k, h[maxn], L[maxn], R[maxn], st[maxn], top;
char s[maxn];
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m >> k;
		for(int j = 1; j <= m; j++) h[j] = 0;
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			cin >> s + 1;
			for(int j = 1; j <= m; j++) h[j] = s[j] == '0' ? h[j] + 1 : 0;
			top = 0;
			for(int j = 1; j <= m; j++) {
				while(top && h[st[top]] >= h[j]) top--;
				L[j] = top ? st[top] : 0;
				st[++top] = j;
			}
			top = 0;
			for(int j = m; j >= 1; j--) {
				while(top && h[st[top]] >= h[j]) top--;
				R[j] = top ? st[top] : m + 1;
				st[++top] = j;
			}
			for(int j = 1; j <= m; j++) {
				int w = k - h[j];
				if(h[j] && w > 0 && w < R[j] - L[j])
					ans = max(ans, h[j] * w);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
