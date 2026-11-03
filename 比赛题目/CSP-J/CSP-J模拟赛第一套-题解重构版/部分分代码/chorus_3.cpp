// 部分分 3
/*
T4 chorus; short-block DP with all n circular cuts. Valid for n <= 1000.
Guaranteed: points 1-2 and 7-11 (35). Time O(n*L^2+n^2*L); space O(n*L).
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
// 每段长度只需 L ~ 2L-1，但第一段起点把 n 个位置都试一遍：O(n^2 L)
const long long INF = 4e18;
int n,L;
long long a[N],f[N];
long long cost[N][20];
long long b[25];
int main(){
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
	cin >> n >> L;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i + n] = a[i];
	}
	int maxT = 2 * L - 1;
	for(int i = 1; i <= 2 * n; i++){
		int m = 0;
		for(int t = 1; t <= maxT && i + t - 1 <= 2 * n; t++){
			long long x = a[i + t - 1];
			int p = ++m;
			while(p > 1 && b[p - 1] > x){
				b[p] = b[p - 1];
				p--;
			}
			b[p] = x;
			if(t >= L){
				long long mid = b[(t + 1) / 2],s = 0;
				for(int j = 1; j <= t; j++) s += abs(b[j] - mid);
				cost[i][t] = s;
			}
		}
	}
	long long ans = INF;
	for(int s = 0; s < n; s++){
		f[0] = 0;
		for(int j = 1; j <= n; j++){
			f[j] = INF;
			for(int t = L; t <= maxT && t <= j; t++){
				if(f[j - t] == INF) continue;
				f[j] = min(f[j],f[j - t] + cost[s + j - t + 1][t]);
			}
		}
		ans = min(ans,f[n]);
	}
	cout << ans << endl;
	return 0;
}
