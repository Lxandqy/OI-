#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int K = 205;
const long long NEG = -1e18;   // 表示不可能的状态
int c,n,k;
long long a[N];
vector<int> g[N];
int sz[N];
// f[u][j][0]：u 的子树中恰好形成 j 个景区、u 不开放时的最大收益
// f[u][j][1]：u 开放（u 所在的景区已经计入 j）时的最大收益
long long f[N][K][2];
long long t0[K],t1[K];         // 合并一个儿子时的临时结果
void dfs(int u,int fa){
	sz[u] = 1;
	f[u][0][0] = 0;
	f[u][0][1] = NEG;
	f[u][1][0] = NEG;
	f[u][1][1] = a[u];
	for(int i = 0; i < (int)g[u].size(); i++){
		int v = g[u][i];
		if(v == fa) continue;
		dfs(v,u);
		// 只枚举到“已合并的点数”和 k 中较小的那个
		int lu = min(sz[u],k),lv = min(sz[v],k),lim = min(sz[u] + sz[v],k);
		for(int j = 0; j <= lim; j++){
			t0[j] = NEG;
			t1[j] = NEG;
		}
		for(int x = 0; x <= lu; x++){
			for(int y = 0; y <= lv; y++){
				long long best = max(f[v][y][0],f[v][y][1]);
				// u 不开放：v 一侧的景区各自独立
				if(f[u][x][0] != NEG && best != NEG && x + y <= lim){
					t0[x + y] = max(t0[x + y],f[u][x][0] + best);
				}
				if(f[u][x][1] == NEG) continue;
				// u 开放、v 不开放：景区数相加
				if(f[v][y][0] != NEG && x + y <= lim){
					t1[x + y] = max(t1[x + y],f[u][x][1] + f[v][y][0]);
				}
				// u、v 都开放：v 所在的景区与 u 所在的景区连成一个
				if(f[v][y][1] != NEG && x + y - 1 <= lim){
					t1[x + y - 1] = max(t1[x + y - 1],f[u][x][1] + f[v][y][1]);
				}
			}
		}
		for(int j = 0; j <= lim; j++){
			f[u][j][0] = t0[j];
			f[u][j][1] = t1[j];
		}
		sz[u] += sz[v];
	}
}
int main(){
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	cout << max(f[1][k][0],f[1][k][1]) << endl;
	return 0;
}
