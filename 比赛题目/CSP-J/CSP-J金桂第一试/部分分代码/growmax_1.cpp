// 数组升格（growmax），部分分第 1 项。
// 算法: 递归枚举合法操作。
// 适用条件: n<=5,k<=6
// 保证点号: 1,2,3,4; 保证分: 20。
// 时间复杂度: O(n*(n-1)^k)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

int n,k;
int a[10];

int dfs(int used){
	int best = 0;
	for(int i = 1; i <= n; i++) best = max(best,a[i]);
	if(used == k) return best;
	for(int i = 1; i < n; i++){
		if(a[i] <= a[i + 1]){
			a[i]++;
			best = max(best,dfs(used + 1));
			a[i]--;
		}
	}
	return best;
}

int main(){
	freopen("growmax.in","r",stdin);
	freopen("growmax.out","w",stdout);
	int t;
	cin >> t;
	while(t--){
		cin >> n >> k;
		for(int i = 1; i <= n; i++) cin >> a[i];
		cout << dfs(0) << '\n';
	}
	return 0;
}
