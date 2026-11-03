// 双点巡查，部分分 1：枚举两个候选左端点，逐区间计算并集价值。
// n <= 14，覆盖第 1 至 4 点（20 分）。时间 O(n^3)，空间 O(n)。
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> l(n + 1),r(n + 1);
	vector<long long> w(n + 1);
	for(int i = 1; i <= n; i++) cin >> l[i] >> r[i] >> w[i];
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j++){
			long long sum = 0;
			for(int t = 1; t <= n; t++){
				if((l[t] <= l[i] && l[i] <= r[t]) || (l[t] <= l[j] && l[j] <= r[t])) sum += w[t];
			}
			ans = max(ans,sum);
		}
	}
	cout << ans << '\n';
	return 0;
}
