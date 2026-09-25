#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
const long long NEG = -(1LL << 60);
int n,x[N],b[4],maskValue[9];
long long dp[9][3],nextDp[9][3];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> b[0] >> b[1] >> b[2] >> b[3];
	for(int i = 1; i <= n; i++) cin >> x[i];
	int temp[9] = {0,b[0],0,b[1],0,b[2],0,b[3],0};
	for(int p = 0; p < 9; p++) maskValue[p] = temp[p];
	long long ans = NEG;
	for(int left = 1; left <= n; left++){
		for(int p = 0; p < 9; p++){
			for(int s = 0; s < 3; s++) dp[p][s] = NEG;
		}
		dp[0][0] = 0;
		for(int i = 1; i <= n; i++){
			for(int p = 0; p < 9; p++){
				for(int s = 0; s < 3; s++) nextDp[p][s] = NEG;
			}
			for(int p = 0; p < 9; p++){
				for(int step = 0; step <= 2; step++){
					int q = p + step;
					if(q >= 9) continue;
					if(step == 2 && (p % 2 == 0 || p >= 7)) continue;
					int v = x[i] ^ maskValue[q];
					if(i < left && dp[p][0] != NEG) nextDp[q][0] = 0;
					if(i == left && dp[p][0] != NEG) nextDp[q][1] = max(nextDp[q][1],(long long)v);
					if(i > left){
						if(dp[p][1] != NEG){
							nextDp[q][1] = max(nextDp[q][1],dp[p][1] + v);
							nextDp[q][2] = max(nextDp[q][2],dp[p][1]);
						}
						if(dp[p][2] != NEG) nextDp[q][2] = max(nextDp[q][2],dp[p][2]);
					}
				}
			}
			for(int p = 0; p < 9; p++){
				for(int s = 0; s < 3; s++) dp[p][s] = nextDp[p][s];
			}
		}
		for(int p = 7; p <= 8; p++){
			for(int s = 1; s <= 2; s++) ans = max(ans,dp[p][s]);
		}
	}
	cout << ans << '\n';
	return 0;
}
