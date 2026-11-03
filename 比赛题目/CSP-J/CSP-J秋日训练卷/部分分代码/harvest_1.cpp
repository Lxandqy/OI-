// 丰收（harvest），部分分第 1 项。
// 算法: 枚举各段右端点。
// 适用条件: n<=16
// 保证点号: 1,2,3,4; 保证分: 20。
// 时间复杂度: O(n+k*C(n-k*m+k,k))。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 5010;
int n,m,k;
long long a[N],s[N],ans;

void dfs(int p,int c,long long sum){
	if(c == k){
		if(sum > ans) ans = sum;
		return;
	}
	// p 是上一段的右端点；剩下的段也必须留出足够位置。
	int r = n - (k - c - 1) * m;
	for(int i = p + m; i <= r; i++){
		dfs(i,c + 1,sum + s[i] - s[i - m]);
	}
}

int main(){
	freopen("harvest.in","r",stdin);
	freopen("harvest.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	dfs(0,0,0);
	cout << ans << '\n';
	return 0;
}
