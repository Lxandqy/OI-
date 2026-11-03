#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, a[maxn], id[maxn], c[maxn];
int lowbit(int x) { return x & -x; }
void modify(int x) { for(int i = x; i <= n; i += lowbit(i)) c[i]++; }
int query(int x) {
	int ans = 0;
	for(int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}
int main() {
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], id[i] = i;
	sort(id + 1, id + n + 1, [](int x, int y) { return a[x] < a[y]; });
	int l = 1, r = n, ans = 2;
	for(int i = 1; i <= n;) {
		int j = i;
		while(j <= n && a[id[j]] == a[id[i]]) j++;
		while(l <= r && a[l] < a[id[i]]) l++;
		while(l <= r && a[r] < a[id[i]]) r--;
		if(l < r) ans = max(ans, query(r - 1) - query(l) + 2);
		for(int k = i; k < j; k++) modify(id[k]);
		i = j;
	}
	cout << ans << '\n';
	return 0;
}
