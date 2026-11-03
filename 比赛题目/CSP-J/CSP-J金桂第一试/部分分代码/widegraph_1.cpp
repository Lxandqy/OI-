// 广阔图（widegraph），部分分第 1 项。
// 算法: 全距离表与逐阈值并查集。
// 适用条件: n<=10
// 保证点号: 1,2,3,4; 保证分: 20。
// 时间复杂度: O(n^3*log(n+1))。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 12;
int n,d[N][N],fa[N];
vector<int> e[N];

void dfs(int s,int u,int p,int dep){
	d[s][u] = dep;
	for(int i = 0; i < (int)e[u].size(); i++){
		int v = e[u][i];
		if(v != p) dfs(s,v,u,dep + 1);
	}
}

int find(int x){
	if(fa[x] == x) return x;
	fa[x] = find(fa[x]);
	return fa[x];
}

int main(){
	freopen("widegraph.in","r",stdin);
	freopen("widegraph.out","w",stdout);
	cin >> n;
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int s = 1; s <= n; s++) dfs(s,s,0,0);
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++) fa[i] = i;
		for(int u = 1; u <= n; u++){
			for(int v = u + 1; v <= n; v++){
				if(d[u][v] >= k){
					int a = find(u),b = find(v);
					if(a != b) fa[a] = b;
				}
			}
		}
		int ans = 0;
		for(int i = 1; i <= n; i++){
			if(find(i) == i) ans++;
		}
		cout << ans << (k == n ? '\n' : ' ');
	}
	return 0;
}
