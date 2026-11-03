// 纪念品分组（souvenir），部分分第 1 项。
// 算法: 未处理集合记忆化配对。
// 适用条件: n<=15
// 保证点号: 1,2,3,4,5,6,7,8; 保证分: 40。
// 时间复杂度: O(n*2^n)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 15;
int n,w,a[N],dp[1 << N];

int solve(int mask){
	if(mask == 0) return 0;
	if(dp[mask] != -1) return dp[mask];
	int i = 0;
	while(((mask >> i) & 1) == 0) i++;
	int rest = mask ^ (1 << i);
	int ans = 1 + solve(rest);
	for(int j = i + 1; j < n; j++){
		if(((mask >> j) & 1) && a[i] + a[j] <= w){
			ans = min(ans,1 + solve(rest ^ (1 << j)));
		}
	}
	dp[mask] = ans;
	return ans;
}

int main(){
	freopen("souvenir.in","r",stdin);
	freopen("souvenir.out","w",stdout);
	cin >> w >> n;
	for(int i = 0; i < n; i++) cin >> a[i];
	memset(dp,-1,sizeof(dp));
	cout << solve((1 << n) - 1) << '\n';
	return 0;
}
