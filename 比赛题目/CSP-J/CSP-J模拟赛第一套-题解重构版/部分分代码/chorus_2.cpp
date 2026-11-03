// 部分分 2
/*
T4 chorus; prefix DP with block lengths 2 and 3. Valid for L = 2.
Guaranteed: points 3-6 (20). Time O(n); source space O(n).
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
// L = 2：每段长 2 或 3，长 2 代价 |x-y|，长 3 代价 max-min；第一段起点试 1~3
const long long INF = 4e18;
int n,L;
long long a[N],f[N];
int main(){
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
	cin >> n >> L;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i + n] = a[i];
	}
	long long ans = INF;
	for(int s = 0; s <= 2 && s < n; s++){
		f[0] = 0;
		for(int j = 1; j <= n; j++){
			f[j] = INF;
			if(j >= 2 && f[j - 2] != INF){
				f[j] = min(f[j],f[j - 2] + abs(a[s + j] - a[s + j - 1]));
			}
			if(j >= 3 && f[j - 3] != INF){
				long long x = a[s + j - 2],y = a[s + j - 1],z = a[s + j];
				long long mx = max(x,max(y,z)),mn = min(x,min(y,z));
				f[j] = min(f[j],f[j - 3] + mx - mn);
			}
		}
		ans = min(ans,f[n]);
	}
	cout << ans << endl;
	return 0;
}
