#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int w[1010],value[1010];
long long ans;

void dfs(int i,int weight,long long gain){
	if(weight > m) return;
	if(i > n){
		ans = max(ans,gain);
		return;
	}
	dfs(i + 1,weight,gain);
	dfs(i + 1,weight + w[i],gain + value[i] - k);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> w[i] >> value[i];
	ans = 0;
	dfs(1,0,0);
	cout << ans << '\n';
	return 0;
}
