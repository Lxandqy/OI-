#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
int n,x[N],b[5];
long long ans = -(1LL << 60);

void dfs(int j,int start){
	if(j == 5){
		long long best = -(1LL << 60),end = 0;
		for(int i = 1; i <= n; i++){
			end = max((long long)x[i],end + x[i]);
			best = max(best,end);
		}
		ans = max(ans,best);
		return;
	}
	for(int l = start; l <= n; l++){
		for(int r = l; r <= n; r++){
			for(int i = l; i <= r; i++) x[i] ^= b[j];
			dfs(j + 1,r + 1);
			for(int i = l; i <= r; i++) x[i] ^= b[j];
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for(int j = 1; j <= 4; j++) cin >> b[j];
	for(int i = 1; i <= n; i++) cin >> x[i];
	dfs(1,1);
	cout << ans << '\n';
	return 0;
}
