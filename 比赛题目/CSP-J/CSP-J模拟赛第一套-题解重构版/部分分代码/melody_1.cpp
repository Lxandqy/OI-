// 部分分 1
/*
T3 melody; enumerate deletions. Valid for n <= 18 or k = 0.
Guaranteed: points 1-6 (30). Time O(2^n*n), reduced to O(n) for k=0; space O(n).
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k,m,ans;
int a[N],b[N];
// 依次决定每个音符删不删，del 为已删除的个数，保留的音符放在 b[1..m]
void dfs(int i,int del){
	if(i > n){
		int len = 0;
		for(int t = 1; t <= m; t++){
			if(t > 1 && b[t - 1] < b[t]) len++;
			else len = 1;
			ans = max(ans,len);
		}
		return;
	}
	b[++m] = a[i];
	dfs(i + 1,del);
	m--;
	if(del < k) dfs(i + 1,del + 1);
}
int main(){
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	dfs(1,0);
	cout << ans << endl;
	return 0;
}
