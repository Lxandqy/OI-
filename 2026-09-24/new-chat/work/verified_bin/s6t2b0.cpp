#include<bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
int n,x,b[15];
int a[100010];
long long ans = NEG;

void dfs(int start,int chosen,long long sum){
	if(chosen == x){
		ans = max(ans,sum);
		return;
	}
	int last = n - (x - chosen) + 1;
	for(int i = start; i <= last; i++){
		dfs(i + 1,chosen + 1,sum + 1LL * a[i] * b[chosen + 1]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int j = 1; j <= x; j++) cin >> b[j];
	dfs(1,0,0);
	cout << ans << '\n';
	return 0;
}
