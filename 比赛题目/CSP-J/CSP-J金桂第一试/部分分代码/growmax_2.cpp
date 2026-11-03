// 数组升格（growmax），部分分第 2 项。
// 算法: 两元素公式或严格递减特判。
// 适用条件: n=2 or strictly decreasing
// 保证点号: 5,6,7,8,9,10,11,12; 保证分: 40。
// 时间复杂度: O(n)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

int main(){
	freopen("growmax.in","r",stdin);
	freopen("growmax.out","w",stdout);
	int t;
	cin >> t;
	while(t--){
		int n,k;
		cin >> n >> k;
		vector<int> a(n + 1);
		for(int i = 1; i <= n; i++) cin >> a[i];
		long long ans;
		if(n == 2){
			if(a[1] > a[2]){
				ans = a[1];
			}else{
				long long limit = a[2] - a[1] + 1;
				long long gain = min((long long)k,limit);
				ans = max((long long)a[2],(long long)a[1] + gain);
			}
		}else{
			ans = a[1];
		}
		cout << ans << '\n';
	}
	return 0;
}
