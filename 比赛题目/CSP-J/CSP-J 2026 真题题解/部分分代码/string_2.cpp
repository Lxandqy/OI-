// 回文串，部分分 2：展开字符串，逐对比较镜像位置。
// 时间 O(n + L)，空间 O(n + L)，L 为各段长度之和。
// 测试点 1 至 12、17 至 18 的 L <= 200000；19 至 21 的 L <= 100000000。
// 覆盖测试点 1 至 12、17 至 21，共 68 分；预分配空间后逐对比较。
#include<bits/stdc++.h>
using namespace std;

const int N = 200000 + 10;
long long a[N];
char c[N];

int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	long long sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> c[i];
		sum += a[i];
	}
	string s;
	s.reserve(sum);
	for(int i = 1; i <= n; i++){
		s.append(a[i],c[i]);
	}
	long long ans = 0;
	for(long long i = 0; i < sum / 2; i++){
		if(s[i] != s[sum - 1 - i]) ans++;
	}
	cout << ans << '\n';
	return 0;
}
