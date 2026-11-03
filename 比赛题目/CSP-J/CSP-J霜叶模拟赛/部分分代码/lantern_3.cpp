// 灯带，部分分3：枚举末段长度的动态规划。适用 n,m<=120 或 k=1，保证点1至12共60分。
// 时间 O((n+1)(m+1)k)，空间 O((n+1)(m+1)+n+m)。
#include<bits/stdc++.h>
using namespace std;

const int N = 2010;
const int P = 1000000007;
int n,m,k,f[N][N],g[N][N];
int r[N * 2],b[N * 2];
string s;

int main(){
	freopen("lantern.in","r",stdin);
	freopen("lantern.out","w",stdout);
	cin >> n >> m >> k >> s;
	s = " " + s;
	for(int p = 1; p <= n + m; p++){
		r[p] = r[p - 1];
		b[p] = b[p - 1];
		if(s[p] == 'R') r[p] = p;
		if(s[p] == 'B') b[p] = p;
	}
	f[0][0] = 1;
	g[0][0] = 1;
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= m; j++){
			int p = i + j;
			if(p == 0) continue;
			int x = min(i,min(k,p - b[p]));
			for(int t = 1; t <= x; t++){
				f[i][j] += g[i - t][j];
				if(f[i][j] >= P) f[i][j] -= P;
			}
			int y = min(j,min(k,p - r[p]));
			for(int t = 1; t <= y; t++){
				g[i][j] += f[i][j - t];
				if(g[i][j] >= P) g[i][j] -= P;
			}
		}
	}
	cout << (f[n][m] + g[n][m]) % P << '\n';
	return 0;
}
