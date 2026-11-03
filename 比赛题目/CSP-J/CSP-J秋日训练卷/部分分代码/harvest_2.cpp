// 丰收（harvest），部分分第 2 项。
// 算法: 枚举上一段端点的动态规划。
// 适用条件: n<=180
// 保证点号: 1,2,3,4,5,6,7,8; 保证分: 40。
// 时间复杂度: O(k*n^2)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 5010;
const long long INF = 4e18;
int n,m,k;
long long a[N],s[N],g[N][N];

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
	for(int j = 1; j <= k; j++){
		for(int i = 0; i <= n; i++) g[j][i] = -INF;
	}
	for(int i = m; i <= n; i++) g[1][i] = s[i] - s[i - m];
	for(int j = 2; j <= k; j++){
		for(int i = j * m; i <= n; i++){
			for(int p = (j - 1) * m; p <= i - m; p++){
				long long x = g[j - 1][p] + s[i] - s[i - m];
				if(x > g[j][i]) g[j][i] = x;
			}
		}
	}
	long long ans = 0;
	for(int i = k * m; i <= n; i++){
		if(g[k][i] > ans) ans = g[k][i];
	}
	cout << ans << '\n';
	return 0;
}
