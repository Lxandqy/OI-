#include<bits/stdc++.h>
using namespace std;

int color(char c){
	if(c == 'r') return 0;
	if(c == 'g') return 1;
	return 2;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	string s;
	cin >> n >> s;
	const int INF = 1000000000;
	int ans = INF;
	for(int first = 0; first < 3; first++){
		int dp[3] = {INF,INF,INF};
		dp[first] = (first - color(s[0]) + 3) % 3;
		for(int i = 1; i < n; i++){
			int next[3] = {INF,INF,INF};
			for(int last = 0; last < 3; last++){
				for(int now = 0; now < 3; now++){
					if(last == now) continue;
					int cost = (now - color(s[i]) + 3) % 3;
					next[now] = min(next[now],dp[last] + cost);
				}
			}
			for(int c = 0; c < 3; c++) dp[c] = next[c];
		}
		for(int last = 0; last < 3; last++){
			if(last != first) ans = min(ans,dp[last]);
		}
	}
	cout << ans << '\n';
	return 0;
}
