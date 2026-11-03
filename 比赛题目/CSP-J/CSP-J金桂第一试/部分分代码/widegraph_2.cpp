// 广阔图（widegraph），部分分第 2 项。
// 算法: 链或菊花结构公式。
// 适用条件: path or star
// 保证点号: 5,6,7,8,9,10,11,12; 保证分: 40。
// 时间复杂度: O(n*log n)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int n,deg[N],dist[N];
vector<int> e[N];

void bfs(int s){
	for(int i = 1; i <= n; i++) dist[i] = -1;
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = 0; i < (int)e[u].size(); i++){
			int v = e[u][i];
			if(dist[v] == -1){
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
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
		deg[u]++;
		deg[v]++;
	}
	bool path = true;
	int center = 0;
	for(int i = 1; i <= n; i++){
		if(deg[i] > 2) path = false;
		if(deg[i] == n - 1) center = i;
	}
	if(path){
		int s = 1;
		for(int i = 1; i <= n; i++){
			if(deg[i] == 1) s = i;
		}
		bfs(s);
		vector<int> ecc(n + 1);
		for(int i = 1; i <= n; i++){
			ecc[i] = max(dist[i],n - 1 - dist[i]);
		}
		sort(ecc.begin() + 1,ecc.end());
		for(int k = 1; k <= n; k++){
			int ans;
			if(k >= n){
				ans = n;
			}else{
				int isolated = (int)(lower_bound(ecc.begin() + 1,ecc.end(),k) - ecc.begin() - 1);
				ans = 1 + isolated;
			}
			cout << ans << (k == n ? '\n' : ' ');
		}
	}else if(center){
		for(int k = 1; k <= n; k++){
			int ans;
			if(k == 1){
				ans = 1;
			}else if(k == 2){
				ans = 2;
			}else{
				ans = n;
			}
			cout << ans << (k == n ? '\n' : ' ');
		}
	}else{
		for(int k = 1; k <= n; k++) cout << 0 << (k == n ? '\n' : ' ');
	}
	return 0;
}
