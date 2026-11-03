#include<bits/stdc++.h>
using namespace std;
const int N = 355,T = 350;
const long long INF = 4000000000000000000LL;
int n,m,a[N][N];
long long w[N][N],f[T][N][N];
long long cost(int x,int y,int u,int v){
	if(a[x][y] == a[u][v]) return 0;
	return min(w[x][y],w[u][v]);
}
int main(){
	freopen("palpath.in","r",stdin);
	freopen("palpath.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> w[i][j];
	}
	if(n > m){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m && j < i; j++){
				swap(a[i][j],a[j][i]);
				swap(w[i][j],w[j][i]);
			}
		}
		swap(n,m);
	}
	int d = n + m - 2;
	for(int t = 0; t <= d / 2; t++){
		for(int x = 0; x <= n + 1; x++){
			for(int u = 0; u <= n + 1; u++) f[t][x][u] = INF;
		}
	}
	f[0][1][n] = cost(1,1,n,m);
	for(int t = 1; t <= d / 2; t++){
		for(int x = 1; x <= n; x++){
			int y = t + 2 - x;
			if(y < 1 || y > m) continue;
			for(int u = x; u <= n; u++){
				int v = n + m - t - u;
				if(v < y || v > m) continue;
				long long pre = min(f[t - 1][x][u],f[t - 1][x - 1][u]);
				pre = min(pre,f[t - 1][x][u + 1]);
				pre = min(pre,f[t - 1][x - 1][u + 1]);
				if(pre != INF) f[t][x][u] = pre + cost(x,y,u,v);
			}
		}
	}
	long long ans = INF;
	for(int x = 1; x <= n; x++){
		int y = d / 2 + 2 - x;
		if(y < 1 || y > m) continue;
		for(int u = x; u <= n; u++){
			int v = n + m - d / 2 - u;
			if(v < y || v > m) continue;
			ans = min(ans,f[d / 2][x][u]);
		}
	}
	cout << ans << '\n';
	return 0;
}
