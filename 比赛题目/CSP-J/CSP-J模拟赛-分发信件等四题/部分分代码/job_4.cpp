// job, partial 4: DP by the exact endpoint; enumerate the previous endpoint.
// Condition: n <= 500 and k <= 150, or k = 1.
// Points 1-4 and 7-12, 50 points guaranteed. O(k * n^2) time, O(k * n) space.
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int N = 5005;
const long long INF = 4000000000000000000LL;
int n,m,k;
long long s[N],f[N][N],ans;

int main(){
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		s[i] = s[i - 1] + x;
	}
	for(int i = m; i <= n; i++) f[1][i] = s[i] - s[i - m];
	for(int j = 2; j <= k; j++){
		for(int i = j * m; i <= n; i++){
			long long now = -INF;
			for(int t = (j - 1) * m; t <= i - m; t++) now = max(now,f[j - 1][t]);
			f[j][i] = now + s[i] - s[i - m];
		}
	}
	for(int i = k * m; i <= n; i++) ans = max(ans,f[k][i]);
	cout << ans << '\n';
	return 0;
}
