#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int n,dist1[N],dists[N],distt[N],ecc[N];
vector<int> e[N];

void bfs(int s,int dist[]){
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

int farthest(int dist[]){
	int p = 1;
	for(int i = 2; i <= n; i++){
		if(dist[i] > dist[p]) p = i;
	}
	return p;
}

int main(){
	freopen("widegraph.in","r",stdin);
	freopen("widegraph.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	bfs(1,dist1);
	int s = farthest(dist1);
	bfs(s,dists);
	int t = farthest(dists);
	bfs(t,distt);
	for(int i = 1; i <= n; i++){
		ecc[i] = max(dists[i],distt[i]);
	}
	sort(ecc + 1,ecc + n + 1);
	int diameter = ecc[n];
	for(int k = 1; k <= n; k++){
		if(k > diameter){
			cout << n;
		}else{
			int isolated = (int)(lower_bound(ecc + 1,ecc + n + 1,k) - ecc - 1);
			cout << 1 + isolated;
		}
		cout << (k == n ? '\n' : ' ');
	}
	return 0;
}
