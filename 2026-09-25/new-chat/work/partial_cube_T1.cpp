#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
const long long NEG = -(1LL << 60);
int n,x[N],b[4],maskValue[9];
long long dp[9],nextDp[9];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> b[0] >> b[1] >> b[2] >> b[3];
	for(int i = 1; i <= n; i++) cin >> x[i];
	int temp[9] = {0,b[0],0,b[1],0,b[2],0,b[3],0};
	for(int p = 0; p < 9; p++) maskValue[p] = temp[p];
	long long answer = NEG;
	for(int left = 1; left <= n; left++){
		for(int right = left; right <= n; right++){
			for(int p = 0; p < 9; p++) dp[p] = NEG;
			dp[0] = 0;
			for(int i = 1; i <= n; i++){
				for(int p = 0; p < 9; p++) nextDp[p] = NEG;
				for(int p = 0; p < 9; p++){
					if(dp[p] == NEG) continue;
					for(int step = 0; step <= 2; step++){
						int q = p + step;
						if(q >= 9) continue;
						if(step == 2 && (p % 2 == 0 || p >= 7)) continue;
						long long value = dp[p];
						if(left <= i && i <= right) value += x[i] ^ maskValue[q];
						nextDp[q] = max(nextDp[q],value);
					}
				}
				for(int p = 0; p < 9; p++) dp[p] = nextDp[p];
			}
			answer = max(answer,max(dp[7],dp[8]));
		}
	}
	cout << answer << '\n';
	return 0;
}
