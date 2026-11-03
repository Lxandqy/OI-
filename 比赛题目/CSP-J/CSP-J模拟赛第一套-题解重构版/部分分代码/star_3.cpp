// 部分分 3
// Problem: star; method: zero.
// Applicable condition: m = 0.
// Guaranteed test points: 11-14; guaranteed score: 20/100.
// Time: O(n); space: O(n) (includes stored input / DP table).
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k,m,q;
int a[N];
int main(){
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	cin >> n >> k >> m >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0,len = 0;
	// 只处理 m = 0：每段连续晴朗的夜晚长度为 len，长度至少 k 的区间有 (len-k+1)(len-k+2)/2 个
	for(int i = 1; i <= n + 1; i++){
		if(i <= n && a[i] <= q){
			len++;
		}else{
			if(len >= k) ans += (len - k + 1) * (len - k + 2) / 2;
			len = 0;
		}
	}
	cout << ans << endl;
	return 0;
}
