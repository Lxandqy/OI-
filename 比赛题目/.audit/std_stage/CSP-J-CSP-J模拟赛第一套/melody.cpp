#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int K = 25;
int n,k;
int a[N];
// f[i][j]：保留第 i 个音符、它是上升段的最后一个，段内最多删除 j 个音符时，上升段的最大长度
int f[N][K];
int main(){
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= k; j++){
			f[i][j] = 1;
			// 上升段中 i 的前一个保留的音符是 p，中间删掉 g = i - p - 1 个
			for(int g = 0; g <= j; g++){
				int p = i - 1 - g;
				if(p < 1) break;
				if(a[p] < a[i]) f[i][j] = max(f[i][j],f[p][j - g] + 1);
			}
			ans = max(ans,f[i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}
