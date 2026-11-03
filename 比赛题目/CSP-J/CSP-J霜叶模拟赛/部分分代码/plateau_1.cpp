// 高台，部分分1：逐格计算每个方块的费用，再枚举不重叠的方块对。
// 适用n,m<=8，保证测试点1至3，共15分。令q为可放下两块的最大边长。
// 时间O(n*m*q^3+n*n*m*m*q)，空间O(n*m)。
#include<bits/stdc++.h>
using namespace std;

const int N = 2010;
int n,m,a[N][N];
long long b;

struct node{
	int x,y;
	long long cost;
};

bool check(int len){

	vector<node> v;
	for(int i = 1; i + len - 1 <= n; i++){
		for(int j = 1; j + len - 1 <= m; j++){
			long long cost = 0;
			for(int x = i; x < i + len; x++){
				for(int y = j; y < j + len; y++){
					cost += max(0,len - a[x][y]);
				}
			}
			v.push_back({i,j,cost});
		}
	}
	for(int i = 0; i < (int)v.size(); i++){
		for(int j = i + 1; j < (int)v.size(); j++){
			if(abs(v[i].x - v[j].x) < len && abs(v[i].y - v[j].y) < len) continue;
			if(v[i].cost + v[j].cost <= b) return true;
		}
	}
	return false;
}

int main(){
	freopen("plateau.in","r",stdin);
	freopen("plateau.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> b;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cin >> a[i][j];
	}
	int ans = 0,q = min(min(n,m),max(n,m) / 2);
	for(int len = 1; len <= q; len++){
		if(!check(len)) break;
		ans = len;
	}
	cout << ans << '\n';
	return 0;
}
