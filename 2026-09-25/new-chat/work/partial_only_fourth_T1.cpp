#include<bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
long long dp[3][3],nextDp[3][3];

void update(int from,int to,int value){
	if(dp[from][0] != NEG){
		nextDp[to][0] = 0;
		nextDp[to][1] = max(nextDp[to][1],(long long)value);
	}
	if(dp[from][1] != NEG){
		nextDp[to][1] = max(nextDp[to][1],dp[from][1] + value);
		nextDp[to][2] = max(nextDp[to][2],dp[from][1]);
	}
	if(dp[from][2] != NEG) nextDp[to][2] = max(nextDp[to][2],dp[from][2]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,b[4],x;
	cin >> n >> b[0] >> b[1] >> b[2] >> b[3];
	for(int p = 0; p < 3; p++){
		for(int s = 0; s < 3; s++) dp[p][s] = NEG;
	}
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++){
		cin >> x;
		for(int p = 0; p < 3; p++){
			for(int s = 0; s < 3; s++) nextDp[p][s] = NEG;
		}
		update(0,0,x);
		if(i >= 4) update(0,1,x ^ b[3]);
		update(1,1,x ^ b[3]);
		update(1,2,x);
		update(2,2,x);
		for(int p = 0; p < 3; p++){
			for(int s = 0; s < 3; s++) dp[p][s] = nextDp[p][s];
		}
	}
	long long answer = NEG;
	for(int p = 1; p <= 2; p++){
		for(int s = 1; s <= 2; s++) answer = max(answer,dp[p][s]);
	}
	cout << answer << '\n';
	return 0;
}
