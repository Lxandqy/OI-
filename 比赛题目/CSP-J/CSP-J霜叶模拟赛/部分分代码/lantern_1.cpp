// 灯带，部分分1：逐位搜索。适用 n+m<=22 或 k=1，保证点1至7共35分。一般时间 O(2^(n+m))，k=1 时 O(n+m)，空间 O(n+m)。
#include<bits/stdc++.h>
using namespace std;

const int P = 1000000007;
int n,m,k,ans;
string s;

void dfs(int p,int x,int y,char last,int len){
	if(p == n + m){
		ans++;
		if(ans == P) ans = 0;
		return;
	}
	if(x < n && s[p] != 'B'){
		int z = 1;
		if(last == 'R') z = len + 1;
		if(z <= k) dfs(p + 1,x + 1,y,'R',z);
	}
	if(y < m && s[p] != 'R'){
		int z = 1;
		if(last == 'B') z = len + 1;
		if(z <= k) dfs(p + 1,x,y + 1,'B',z);
	}
}

int main(){
	freopen("lantern.in","r",stdin);
	freopen("lantern.out","w",stdout);
	cin >> n >> m >> k >> s;
	dfs(0,0,0,'?',0);
	cout << ans << '\n';
	return 0;
}
