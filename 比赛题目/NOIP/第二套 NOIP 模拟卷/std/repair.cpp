#include<bits/stdc++.h>
using namespace std;

const int N = 300010;
const int INF = 2000000000;
int n,a[N],f[N][3];

int main(){
	freopen("repair.in","r",stdin);
	freopen("repair.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	f[0][1] = INF;
	f[0][2] = INF;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= 2; j++){
			f[i][j] = INF;
			if(j > i || 2 - j > n - i) continue;
			int t;
			if(j == 0) t = n - i - 1;
			if(j == 1) t = n - 2;
			if(j == 2) t = i - 2;
			f[i][j] = max(f[i - 1][j],a[i] + t);
			if(j > 0){
				f[i][j] = min(f[i][j],max(f[i - 1][j - 1],a[i]));
			}
		}
	}
	cout << f[n][2] << '\n';
	return 0;
}
