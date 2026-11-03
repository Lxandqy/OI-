#include<bits/stdc++.h>
using namespace std;

const int N = 2010;
const int P = 1000000007;
int n,m,k;
int f[N][N],g[N][N],sf[N][N],sg[N][N];
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
			if(p > 0){
				int x = min(i,min(k,p - b[p]));
				if(x > 0){
					f[i][j] = sg[i - 1][j];
					if(i > x) f[i][j] = (f[i][j] - sg[i - x - 1][j] + P) % P;
				}
				int y = min(j,min(k,p - r[p]));
				if(y > 0){
					g[i][j] = sf[i][j - 1];
					if(j > y) g[i][j] = (g[i][j] - sf[i][j - y - 1] + P) % P;
				}
			}
			sf[i][j] = f[i][j];
			sg[i][j] = g[i][j];
			if(j > 0) sf[i][j] = (sf[i][j] + sf[i][j - 1]) % P;
			if(i > 0) sg[i][j] = (sg[i][j] + sg[i - 1][j]) % P;
		}
	}
	cout << (f[n][m] + g[n][m]) % P << '\n';
	return 0;
}
