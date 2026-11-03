#include<bits/stdc++.h>
using namespace std;
int T;
long long n,a,b;
int main(){
	freopen("slime.in","r",stdin);
	freopen("slime.out","w",stdout);
	cin >> T;
	while(T--){
		cin >> n >> a >> b;
		// s 为 n 的整数平方根：s * s <= n < (s + 1) * (s + 1)
		long long s = (long long)sqrt((double)n);
		while(s * s > n) s--;
		while((s + 1) * (s + 1) <= n) s++;
		long long ans = -1;
		// 最终有 y 只史莱姆、每只大小为 x，需要 x * y >= n，花费 a(x-1) + b(y-1)
		// 情况一：x <= s + 1，枚举 x，y 取最小的 ceil(n / x)
		for(long long x = 1; x <= s + 1; x++){
			long long y = (n + x - 1) / x;
			long long cost = a * (x - 1) + b * (y - 1);
			if(ans == -1 || cost < ans) ans = cost;
		}
		// 情况二：x > s + 1，此时 y <= s + 1，枚举 y，x 取最小的 ceil(n / y)
		for(long long y = 1; y <= s + 1; y++){
			long long x = (n + y - 1) / y;
			long long cost = a * (x - 1) + b * (y - 1);
			if(cost < ans) ans = cost;
		}
		cout << ans << endl;
	}
	return 0;
}
