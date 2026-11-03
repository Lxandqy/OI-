// 部分分 1
// Problem: slime; method: dp.
// Applicable condition: n <= 1000 in every case.
// Guaranteed test points: 1-3; guaranteed score: 15/100.
// Time: O(n^2) per case; space: O(n^2) (includes stored input / DP table).
#include<bits/stdc++.h>
using namespace std;
// 只增大最大的史莱姆、只复制最大的史莱姆：状态 (总大小 s, 最大一只的大小 v)
int T;
long long n,a,b;
long long f[1010][1010];
int main(){
	freopen("slime.in","r",stdin);
	freopen("slime.out","w",stdout);
	cin >> T;
	while(T--){
		cin >> n >> a >> b;
		for(int s = 1; s <= n; s++){
			for(int v = 1; v <= n; v++) f[s][v] = -1;
		}
		f[1][1] = 0;
		for(int s = 1; s < n; s++){
			for(int v = 1; v <= s; v++){
				if(f[s][v] == -1) continue;
				// 把最大的一只加 1
				int s1 = s + 1,v1 = v + 1;
				if(s1 > n) s1 = n;
				if(v1 > n) v1 = n;
				if(f[s1][v1] == -1 || f[s][v] + a < f[s1][v1]) f[s1][v1] = f[s][v] + a;
				// 复制最大的一只
				int s2 = s + v;
				if(s2 > n) s2 = n;
				if(f[s2][v] == -1 || f[s][v] + b < f[s2][v]) f[s2][v] = f[s][v] + b;
			}
		}
		long long ans = -1;
		for(int v = 1; v <= n; v++){
			if(f[n][v] != -1 && (ans == -1 || f[n][v] < ans)) ans = f[n][v];
		}
		cout << ans << endl;
	}
	return 0;
}
