// 高台，部分分2：所有格等高，检查摆放范围和两块的总补高费用。
// 适用特殊性质A，保证测试点4至6，共15分。
// 时间O(n*m+q)，空间O(n*m)，q为可放下两块的最大边长。
#include<bits/stdc++.h>
using namespace std;

const int N = 2010;
int n,m,a[N][N];
long long b;

int main(){
	freopen("plateau.in","r",stdin);
	freopen("plateau.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> b;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	}
	int ans = 0,q = min(min(n,m),max(n,m) / 2);
	for(int len = 1; len <= q; len++){
		long long cost = 2ll * len * len * max(0,len - a[1][1]);
		if(cost <= b) ans = len;
	}
	cout << ans << '\n';
	return 0;
}
