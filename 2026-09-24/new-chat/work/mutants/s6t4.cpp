#include<bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
int dp[8005][405], rightEnd[8005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	string s = " ";
	for(int i = 1; i <= n; i++){
		string t;
		cin >> t;
		int start = (int)s.size();
		s += t;
		int finish = (int)s.size() - 1;
		for(int j = start; j <= finish; j++){
			rightEnd[j] = finish;
		}
	}
	int length = (int)s.size() - 1;
	for(int i = 0; i <= length; i++){
		for(int r = 0; r < k; r++){
			dp[i][r] = INF;
		}
	}
	dp[0][0] = 0;
	// dp[i][r]：前 i 位已分段完成，数字和模 k 为 r 的最少切割数。
	for(int i = 0; i < length; i++){
		int value = 0;
		for(int j = i + 1; j <= rightEnd[i + 1]; j++){
			value = (value * 10 + s[j] - '0') % k;
			int cost = 0;
			if(j <= rightEnd[i + 1]){
				cost = 1;
			}
			for(int r = 0; r < k; r++){
				if(dp[i][r] == INF){
					continue;
				}
				int next = (r + value) % k;
				dp[j][next] = min(dp[j][next], dp[i][r] + cost);
			}
		}
	}
	if(dp[length][0] == INF){
		cout << -1 << '\n';
	}else{
		cout << dp[length][0] << '\n';
	}
	return 0;
}
