#include<bits/stdc++.h>
using namespace std;

const int N = 5005,mod = 998244353;
int n,k,a,b,f[N][N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	f[0][0] = 1;
	for(int i = 1; i <= n; i++){
		cin >> a >> b;
		for(int j = 0; j <= min(i,k); j++){
			f[i][j] = f[i - 1][j];
			if(j >= 1 && j - 1 <= b && k - j <= a){
				f[i][j] += f[i - 1][j - 1];
				if(f[i][j] >= mod) f[i][j] -= mod;
			}
		}
	}
	cout << f[n][k] << '\n';
	return 0;
}
