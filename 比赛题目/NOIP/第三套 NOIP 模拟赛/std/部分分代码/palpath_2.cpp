// 回文通路：部分分 2，枚举子矩形的两个端点。保证第 1 至 10 点，共 50 分。
// 时间和空间均为 O(n^2*m^2)，单行或单列时均为 O((n+m)^2)。
#include<algorithm>
#include<climits>
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
int n,m;
vector<vector<int> > a,w;

int id(int x,int y){
	return (x - 1) * m + y;
}

int main(){
	freopen("palpath.in","r",stdin);
	freopen("palpath.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	a.assign(n + 1,vector<int>(m + 1));
	w.assign(n + 1,vector<int>(m + 1));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> w[i][j];
	}
	int cells = n * m;
	vector<vector<long long> > f(cells + 1,vector<long long>(cells + 1));
	// f[p][q] 表示从编号 p 的格子走到编号 q 的格子所需的最小翻转费用。
	for(int h = 0; h < n; h++){
		for(int b = 0; b < m; b++){
			for(int x = 1; x + h <= n; x++){
				for(int y = 1; y + b <= m; y++){
					int u = x + h,v = y + b;
					long long cost = 0;
					if(a[x][y] != a[u][v]) cost = min(w[x][y],w[u][v]);
					long long best = 0;
					if(h + b >= 2){
						best = LLONG_MAX;
						if(h >= 2) best = min(best,f[id(x + 1,y)][id(u - 1,v)]);
						if(b >= 2) best = min(best,f[id(x,y + 1)][id(u,v - 1)]);
						if(h >= 1 && b >= 1){
							best = min(best,f[id(x + 1,y)][id(u,v - 1)]);
							best = min(best,f[id(x,y + 1)][id(u - 1,v)]);
						}
					}
					f[id(x,y)][id(u,v)] = best + cost;
				}
			}
		}
	}
	cout << f[id(1,1)][id(n,m)] << '\n';
	return 0;
}
