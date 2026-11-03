// 配对（pairs），部分分第 1 项。
// 算法: 枚举所有位置对。
// 适用条件: n<=1500,total n<=20000
// 保证点号: 1,2,3,4,5,6; 保证分: 30。
// 时间复杂度: O(n^2)。重叠点只计一次。
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
		for(int j = 2; j <= n; j++){
			for(int i = 1; i < j; i++){
				if(a[i] < i && i < a[j] && a[j] < j) ans++;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
