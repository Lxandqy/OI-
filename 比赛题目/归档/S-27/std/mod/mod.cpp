#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 30;
int n;
ll a[maxn], ans;
void dfs(int pos, ll x) {
	ans = min(ans, x);
	if(!pos || !ans || x < a[1]) return;
	dfs(pos - 1, x);
	if(x >= a[pos]) dfs(pos - 1, x % a[pos]);
}
int main() {
	freopen("mod.in", "r", stdin);
	freopen("mod.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> ans;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	dfs(n, ans);
	cout << ans << '\n';
	return 0;
}
