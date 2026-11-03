#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 10;
int n, k, a[maxn], b[maxn], cnt;
vector<int> d;
void get(int x) {
	for(int i = 1; i * i <= x; i++)
		if(x % i == 0) {
			d.push_back(i);
			if(i * i != x) d.push_back(x / i);
		}
}
bool check(int x) {
	cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] % x == 0) continue;
		if(b[i] % x != 0) return 0;
		// 原装不能分完时，才必须使用备用装。
		if(++cnt > k) return 0;
	}
	return 1;
}
int main() {
	freopen("pack.in", "r", stdin);
	freopen("pack.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
		d.clear();
		get(a[1]), get(b[1]);
		sort(d.begin(), d.end());
		d.erase(unique(d.begin(), d.end()), d.end());
		for(int i = (int)d.size() - 1; i >= 0; i--)
			if(check(d[i])) {
				cout << d[i] << ' ' << cnt << '\n';
				break;
			}
	}
	return 0;
}
