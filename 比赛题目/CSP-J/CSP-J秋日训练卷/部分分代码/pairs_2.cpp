// 配对（pairs），部分分第 2 项。
// 算法: 按右端标签缩小左端枚举。
// 适用条件: n<=1500 or max(a)<=300
// 保证点号: 1,2,3,4,5,6,7,8,9,10,11,12; 保证分: 60。
// 时间复杂度: O(n*(1+min(n,V)))。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,t,a[N];
int main(){
	freopen("pairs.in","r",stdin);
	freopen("pairs.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		long long ans = 0;
		for(int j = 1; j <= n; j++){
			if(a[j] >= j) continue;
			for(int i = 1; i < a[j]; i++){
				if(a[i] < i) ans++;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
