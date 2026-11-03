#include<bits/stdc++.h>
using namespace std;

const int N = 5005;
const long long INF = 4000000000000000000LL;
int n,m,k;
long long s[N],f[N][N];

int main(){
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		s[i] = s[i - 1] + x;
	}
	for(int j = 1; j <= k; j++){
		for(int i = 0; i <= n; i++) f[j][i] = -INF;
		for(int i = j * m; i <= n; i++){
			f[j][i] = max(f[j][i - 1],f[j - 1][i - m] + s[i] - s[i - m]);
		}
	}
	cout << f[k][n] << '\n';
	return 0;
}
