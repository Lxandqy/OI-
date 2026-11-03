// 回文串，部分分 3：枚举原段与镜像段，统计字母不同的区间交。
// 适用 n <= 2000，保证覆盖测试点 1 至 16，共 64 分。
// 每对不相同的镜像字符被计算两次，最终将总数除以 2。
// 时间 O(n^2)，空间 O(n)。
#include<bits/stdc++.h>
using namespace std;

const int N = 200000 + 10;
long long b[N];
char c[N];

int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x >> c[i];
		b[i] = b[i - 1] + x;
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(c[i] == c[j]) continue;
			long long l = max(b[i - 1] + 1,b[n] - b[j] + 1);
			long long r = min(b[i],b[n] - b[j - 1]);
			if(l <= r) ans += r - l + 1;
		}
	}
	cout << ans / 2 << '\n';
	return 0;
}
