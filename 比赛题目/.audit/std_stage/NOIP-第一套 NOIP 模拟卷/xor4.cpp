#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const long long inf = 1LL << 60;
int n,m,p[5];
long long f[N][9];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		cin >> p[i];
	}
	for(int j = 0; j <= 2 * m; j++){
		f[0][j] = -inf;
	}
	long long ans = -inf;
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		for(int j = 0; j <= 2 * m; j++){
			long long w = x;
			if(j % 2 == 1) w = x ^ p[(j + 1) / 2];
			f[i][j] = -inf;

			// 子段从 i 开始，前面要能放下该阶段之前的操作。
			int first = 1;
			if(j > 0) first = j / 2 + 1;
			if(i >= first) f[i][j] = w;

			long long pre = f[i - 1][j];
			if(j >= 1) pre = max(pre,f[i - 1][j - 1]);
			// 两个操作段可以相邻，中间的空隙可以跳过。
			if(j >= 3 && j % 2 == 1) pre = max(pre,f[i - 1][j - 2]);
			if(pre != -inf) f[i][j] = max(f[i][j],pre + w);

			int need = m - (j + 1) / 2;
			if(n - i >= need) ans = max(ans,f[i][j]);
		}
	}
	cout << ans << '\n';
	return 0;
}
