// 远行（visit），部分分第 2 项。
// 算法: 固定最远编号并增量维护收益顺序。
// 适用条件: n<=1500
// 保证点号: 1,2,3,4,5,6,7,8; 保证分: 40。
// 时间复杂度: O(n^2)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int n,s[N],a[N],b[N];
long long ans[N];

int main(){
	freopen("visit.in","r",stdin);
	freopen("visit.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> s[i];
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int r = 1; r <= n; r++){
		long long sum = a[r] + 2LL * s[r];
		ans[1] = max(ans[1],sum);
		for(int k = 2; k <= r; k++){
			sum += b[k - 1];
			ans[k] = max(ans[k],sum);
		}
		int p = r;
		while(p > 1 && b[p - 1] < a[r]){
			b[p] = b[p - 1];
			p--;
		}
		b[p] = a[r];
	}
	for(int k = 1; k <= n; k++) cout << ans[k] << '\n';
	return 0;
}
