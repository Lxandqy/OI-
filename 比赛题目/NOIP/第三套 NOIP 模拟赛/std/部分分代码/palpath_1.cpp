// 回文通路：部分分 1，枚举单调通路。保证第 1 至 4、9 至 10 点，共 30 分。
// 设 L=n+m-1，每条路用 O(L) 计费，总时间 O(C(L-1,n-1)*L)，空间 O(nm+L)。
#include<algorithm>
#include<climits>
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
int n,m;
vector<vector<int> > a,w;
vector<int> val,fee;
long long ans = LLONG_MAX;

void dfs(int x,int y){
	int t = x + y - 1;
	val[t] = a[x][y];
	fee[t] = w[x][y];
	if(x == n && y == m){
		long long sum = 0;
		for(int l = 1; l <= t / 2; l++){
			int r = t + 1 - l;
			if(val[l] != val[r]) sum += min(fee[l],fee[r]);
		}
		ans = min(ans,sum);
		return;
	}
	if(x < n) dfs(x + 1,y);
	if(y < m) dfs(x,y + 1);
}

int main(){
	freopen("palpath.in","r",stdin);
	freopen("palpath.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	a.assign(n + 1,vector<int>(m + 1));
	w.assign(n + 1,vector<int>(m + 1));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> w[i][j];
	}
	val.resize(n + m);
	fee.resize(n + m);
	dfs(1,1);
	cout << ans << '\n';
	return 0;
}
