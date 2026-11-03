#include<bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
long long dp[100005][11];
int a[100005], b[11];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, x;
	cin >> n >> x;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int j = 1; j <= x; j++){
		cin >> b[j];
		dp[0][j] = NEG;
	}
	// dp[i][j]：前 i 个元素中恰好选 j 个，与 b 的前 j 项配对。
	for(int i = 1; i <= n; i++){
		dp[i][0] = 0;
		for(int j = 1; j <= x; j++){
			dp[i][j] = dp[i - 1][j];
			if(dp[i - 1][j - 1] != NEG){
				long long value = dp[i - 1][j - 1] + 1LL * a[i] * b[j];
				dp[i][j] = max(dp[i][j], value);
			}
		}
	}
	cout << dp[n][x] << '\n';
	return 0;
}
