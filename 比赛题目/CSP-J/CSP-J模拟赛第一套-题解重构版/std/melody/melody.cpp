#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int K = 25;
int n,k;
int a[N];
// f[i][j]: 以 i 结尾、片段内部恰好删去 j 个数的最大长度
int f[N][K];
int main(){
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) f[i][0] = 1;
	int ans = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= k; j++){
			if(f[i][j] == 0) continue;
			ans = max(ans,f[i][j]);
			for(int g = 0; g <= k - j; g++){
				int p = i + g + 1;
				if(p > n) break;
				if(a[i] < a[p]){
					f[p][j + g] = max(f[p][j + g],f[i][j] + 1);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
