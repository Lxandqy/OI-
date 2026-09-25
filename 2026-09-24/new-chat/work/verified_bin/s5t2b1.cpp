#include<bits/stdc++.h>
using namespace std;

const int N = 1010;
const int M = 3010;
int n,m,k;
int w[N],value[N];
long long dp[N][M];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> w[i] >> value[i];
	for(int i = n; i >= 1; i--){
		for(int c = 0; c <= m; c++){
			dp[i][c] = dp[i + 1][c];
			if(c >= w[i]){
				dp[i][c] = max(dp[i][c],dp[i + 1][c - w[i]] + value[i] - k);
			}
		}
	}
	cout << dp[1][m] << '\n';
	return 0;
}
