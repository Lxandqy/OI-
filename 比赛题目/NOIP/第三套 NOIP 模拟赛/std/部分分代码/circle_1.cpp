// 朋友圈 部分分 1：邻接表增删边，查询时 BFS，覆盖第 1-8 点共 40 分。
// 总时间 O(n+m+q(n+m+q))，空间 O(n+m+q)。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N = 100005;
vector<int> g[N];
bool vis[N];
int main(){
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m,q;
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cin >> q;
	for(int i = 1; i <= q; i++){
		int op;
		cin >> op;
		if(op != 3){
			int u,v;
			cin >> u >> v;
			if(op == 1){
				g[u].push_back(v);
				g[v].push_back(u);
			}else{
				g[u].erase(find(g[u].begin(),g[u].end(),v));
				g[v].erase(find(g[v].begin(),g[v].end(),u));
			}
			continue;
		}
		fill(vis + 1,vis + n + 1,false);
		long long ans = 0;
		queue<int> qu;
		for(int s = 1; s <= n; s++){
			if(vis[s]) continue;
			vis[s] = true;
			qu.push(s);
			int mx = s;
			while(!qu.empty()){
				int u = qu.front();
				qu.pop();
				mx = max(mx,u);
				for(int j = 0; j < (int)g[u].size(); j++){
					int v = g[u][j];
					if(vis[v]) continue;
					vis[v] = true;
					qu.push(v);
				}
			}
			ans += mx;
		}
		cout << ans << '\n';
	}
	return 0;
}
