#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	long long k;
	cin >> n >> m >> k;
	vector<long long> dp(m + 1, 0);

	for(int i = 1; i <= n; i++){
		int w;
		long long value;
		cin >> w >> value;
		long long gain = value - k;
		for(int j = m; j >= w; j--){
			dp[j] = max(dp[j], dp[j - w] + gain);
		}
	}

	cout << *max_element(dp.begin(), dp.end()) << '\n';
	return 0;
}
