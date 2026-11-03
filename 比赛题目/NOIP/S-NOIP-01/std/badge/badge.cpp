#include<bits/stdc++.h>
#define ll long long
#define PII pair<ll, int>
using namespace std;
const int maxn = 2e5 + 10;
int n, k, cnt, pos;
// a[c] 是图案 c 的历史最大值，vis[c] 表示当前是否在册中；sum 为在册总分。
ll a[maxn], sum, cost, ans;
bool vis[maxn];
priority_queue<PII, vector<PII>, greater<PII>> q;
// 更新时旧记录留在堆中，用到堆顶前再清掉失效记录。
void clean() {
	while(!q.empty() && (!vis[q.top().second] || a[q.top().second] != q.top().first)) q.pop();
}
int main() {
	freopen("badge.in", "r", stdin);
	freopen("badge.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		int c;
		ll v, w;
		cin >> c >> v >> w;
		cost += w;
		if(v > a[c]) {
			// 已经收下这个图案，只补上美观值的增量。
			if(vis[c]) {
				sum += v - a[c];
				a[c] = v;
				q.push({v, c});
			}
			else {
				a[c] = v;
				clean();
				if(cnt < k) {
					cnt++;
					vis[c] = true;
					sum += v;
					q.push({v, c});
				}
				// 册子满了，用新徽章替换当前最差的一枚。
				else if(v > q.top().first) {
					sum -= q.top().first;
					vis[q.top().second] = false;
					q.pop();
					vis[c] = true;
					sum += v;
					q.push({v, c});
				}
			}
		}
		// 只在更优时更新，分数相同就保留更早的下车站。初始为不出发。
		if(sum - cost > ans) ans = sum - cost, pos = i;
	}
	cout << ans << ' ' << pos << '\n';
	return 0;
}
