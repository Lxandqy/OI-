// 高台，部分分3：枚举边长，用二维前缀和与分隔线两侧最小值判定。
// 适用n,m<=250或min(n,m)<=20，保证测试点1至3、7至10，共35分。
// 时间O(n*m*q)，空间O(n*m)，q为可放下两块的最大边长。
#include<bits/stdc++.h>
using namespace std;

const int N = 2010;
const long long INF = 4000000000000000000ll;
int n,m,a[N][N];
long long b,s[N][N],row[N],col[N];

bool check(int len){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int cost = max(0,len - a[i][j]);
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + cost;
		}
	}
	for(int i = 0; i <= n; i++) row[i] = INF;
	for(int j = 0; j <= m; j++) col[j] = INF;
	for(int i = len; i <= n; i++){
		for(int j = len; j <= m; j++){
			long long cost = s[i][j] - s[i - len][j] - s[i][j - len] + s[i - len][j - len];
			row[i] = min(row[i],cost);
			col[j] = min(col[j],cost);
		}
	}
	for(int i = 1; i <= n; i++) row[i] = min(row[i],row[i - 1]);
	for(int j = 1; j <= m; j++) col[j] = min(col[j],col[j - 1]);
	for(int i = len; i <= n; i++){
		for(int j = len; j <= m; j++){
			long long cost = s[i][j] - s[i - len][j] - s[i][j - len] + s[i - len][j - len];
			if(row[i - len] + cost <= b) return true;
			if(col[j - len] + cost <= b) return true;
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
