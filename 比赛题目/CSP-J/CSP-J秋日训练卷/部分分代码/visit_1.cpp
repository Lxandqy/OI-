// 远行（visit），部分分第 1 项。
// 算法: 搜索驿站子集。
// 适用条件: n<=18
// 保证点号: 1,2,3,4; 保证分: 20。
// 时间复杂度: O(2^n)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n,s[N],a[N];
long long ans[N];
void dfs(int x,int cnt,long long sum,int far){
	if(x > n){
		if(cnt > 0) ans[cnt] = max(ans[cnt],sum + 2LL * far);
		return;
	}
	dfs(x + 1,cnt,sum,far);
	dfs(x + 1,cnt + 1,sum + a[x],max(far,s[x]));
}
int main(){
	freopen("visit.in","r",stdin);
	freopen("visit.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> s[i];
	for(int i = 1; i <= n; i++) cin >> a[i];
	dfs(1,0,0,0);
	for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
	return 0;
}
