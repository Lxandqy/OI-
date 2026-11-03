#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
const long long inf = (1LL << 60);
int n,p[N];
long long w[N],f[N][4],cnt[N][4];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 2; i <= n; i++) cin >> p[i] >> w[i];
	for(int i = 1; i <= n; i++){
		f[i][0] = 0;
		f[i][1] = 0;
		cnt[i][0] = 1;
		cnt[i][1] = 1;
		f[i][2] = -inf;
		f[i][3] = -inf;
	}
	// p[i] < i，倒序时儿子的所有后代已经合并完成。
	for(int i = n; i >= 2; i--){
		int u = p[i];
		long long g[4],ways[4] = {0,0,0,0};
		for(int j = 0; j <= 3; j++) g[j] = -inf;
		for(int j = 0; j <= 3; j++){
			if(cnt[u][j] == 0) continue;
			for(int k = 0; j + k <= 3; k++){
				if(cnt[i][k] == 0) continue;
				long long val = f[u][j] + f[i][k];
				if(k == 1 || k == 2) val += w[i];
				long long num = cnt[u][j] * cnt[i][k];
				if(val > g[j + k]){
					g[j + k] = val;
					ways[j + k] = num;
				}else if(val == g[j + k]){
					ways[j + k] += num;
				}
			}
		}
		for(int j = 0; j <= 3; j++){
			f[u][j] = g[j];
			cnt[u][j] = ways[j];
		}
	}
	cout << cnt[1][3] << '\n';
	return 0;
}
