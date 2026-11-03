#include<bits/stdc++.h>
using namespace std;

const int N = 5010;
const long long INF = 4e18;
int n,m,k;
long long a[N],s[N],f[N][N];

int main(){
	freopen("harvest.in","r",stdin);
	freopen("harvest.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	// f[j][i]：前 i 块田中，恰好收割 j 段的最大产量。
	for(int j = 1; j <= k; j++){
		for(int i = 0; i <= n; i++){
			f[j][i] = -INF;
		}
		for(int i = j * m; i <= n; i++){
			f[j][i] = f[j][i - 1];
			long long x = f[j - 1][i - m] + s[i] - s[i - m];
			if(x > f[j][i]) f[j][i] = x;
		}
	}
	cout << f[k][n] << '\n';
	return 0;
}
