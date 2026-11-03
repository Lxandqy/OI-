// 部分分 3
// Problem: slime; method: oneside.
// Applicable condition: a >= b in every case.
// Guaranteed test points: 10-13; guaranteed score: 20/100.
// Time: O(sqrt(n)) per case; space: O(1) (includes stored input / DP table).
#include<bits/stdc++.h>
using namespace std;
// 只枚举 x <= s + 1：a >= b 时正确
int T;
long long n,a,b;
int main(){
	freopen("slime.in","r",stdin);
	freopen("slime.out","w",stdout);
	cin >> T;
	while(T--){
		cin >> n >> a >> b;
		long long s = (long long)sqrt((double)n);
		while(s * s > n) s--;
		while((s + 1) * (s + 1) <= n) s++;
		long long ans = -1;
		for(long long x = 1; x <= s + 1; x++){
			long long y = (n + x - 1) / x;
			long long cost = a * (x - 1) + b * (y - 1);
			if(ans == -1 || cost < ans) ans = cost;
		}
		cout << ans << endl;
	}
	return 0;
}
