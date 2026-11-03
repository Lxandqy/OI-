// 部分分 2
// Problem: slime; method: linear.
// Applicable condition: n <= 1000000 in every case.
// Guaranteed test points: 1-9; guaranteed score: 45/100.
// Time: O(n) per case; space: O(1) (includes stored input / DP table).
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
		long long ans = -1;
		// 枚举每只的最终大小 x，y = ceil(n / x)
		for(long long x = 1; x <= n; x++){
			long long y = (n + x - 1) / x;
			long long cost = a * (x - 1) + b * (y - 1);
			if(ans == -1 || cost < ans) ans = cost;
		}
		cout << ans << endl;
	}
	return 0;
}
