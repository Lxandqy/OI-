#include<bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
long long dp[4][3],nextDp[4][3];

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
	for(int j = 0; j < 4; j++){
		for(int s = 0; s < 3; s++) dp[j][s] = NEG;
	}
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++){
		cin >> x;
		for(int j = 0; j < 4; j++){
			for(int s = 0; s < 3; s++) nextDp[j][s] = NEG;
		}
		for(int j = 0; j < 4; j++){
			update(j,j,x ^ b[j]);
			if(i > 1 && j < 3) update(j,j + 1,x ^ b[j + 1]);
		}
		for(int j = 0; j < 4; j++){
			for(int s = 0; s < 3; s++) dp[j][s] = nextDp[j][s];
		}
	}
	cout << max(dp[3][1],dp[3][2]) << '\n';
	return 0;
}
