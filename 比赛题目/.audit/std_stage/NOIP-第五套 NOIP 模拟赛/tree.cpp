#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
int n,l[N],r[N],lo[N],hi[N];
long long dp[N];
vector<int> son[N];
int clamp_value(int x,int left,int right){
	return min(right,max(left,x));
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) son[i].clear();
	for(int i = 2; i <= n; i++){
		int p;
		cin >> p;
		son[p].push_back(i);
	}
	for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
	for(int x = n; x >= 1; x--){
		dp[x] = 0;
		if(son[x].empty()){
			lo[x] = l[x];
			hi[x] = r[x];
			continue;
		}
		vector<int> ends;
		for(int j = 0; j < (int)son[x].size(); j++){
			int y = son[x][j];
			ends.push_back(lo[y]);
			ends.push_back(hi[y]);
			dp[x] += dp[y];
		}
		sort(ends.begin(),ends.end());
		int k = son[x].size();
		lo[x] = clamp_value(ends[k - 1],l[x],r[x]);
		hi[x] = clamp_value(ends[k],l[x],r[x]);
		for(int j = 0; j < (int)son[x].size(); j++){
			int y = son[x][j];
			if(lo[x] < lo[y]) dp[x] += lo[y] - lo[x];
			if(lo[x] > hi[y]) dp[x] += lo[x] - hi[y];
		}
	}
	cout << dp[1] << '\n';
	return 0;
}
