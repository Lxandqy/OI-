#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 环线协作，部分分 1：逐项枚举负责人。n <= 12，m <= 18，第 1 至 4 点，共 20 分。
// 时间 O(n + m + 2^m)，空间 O(n + m)，含递归栈。
int n,m,ans;
vector<int> a,work;

void dfs(int j,int longest){
	if(j > m){
		ans = min(ans,longest);
		return;
	}
	int x = a[j],y = x % n + 1;
	work[x]++;
	dfs(j + 1,max(longest,work[x]));
	work[x]--;
	work[y] += 2;
	dfs(j + 1,max(longest,work[y]));
	work[y] -= 2;
}

int main(){
	freopen("relay.in","r",stdin);
	freopen("relay.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	a.resize(m + 1);
	work.resize(n + 1);
	for(int j = 1; j <= m; j++) cin >> a[j];
	ans = m;
	dfs(1,0);
	cout << ans << '\n';
	return 0;
}
