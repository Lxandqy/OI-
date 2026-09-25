#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
vector<int> g[N];
int degreeNow[N],degreeOld[N],leaf[N],que[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++){
			g[i].clear();
			degreeNow[i] = 0;
			leaf[i] = 0;
		}
		for(int i = 1; i < n; i++){
			int u,v;
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
			degreeNow[u]++;
			degreeNow[v]++;
		}
		int total = 0,head = 0,tail = 0;
		for(int i = 1; i <= n; i++){
			degreeOld[i] = degreeNow[i];
			if(degreeNow[i] == 1){
				leaf[i] = 1;
				total++;
				que[tail++] = i;
			}
		}
		int ans = n,ways = 0;
		while(head < tail){
			int u = que[head++];
			if(degreeNow[u] != 1) continue;
			int v = 0;
			for(int j = 0; j < (int)g[u].size(); j++){
				int x = g[u][j];
				if(degreeNow[x] > 0){
					v = x;
					break;
				}
			}
			if(v == 0) continue;
			int left = leaf[u] + (degreeOld[u] == 2);
			int right = total - leaf[u] + (degreeOld[v] == 2);
			int delta = abs(left - right);
			if(delta < ans){
				ans = delta;
				ways = 1;
			}else if(delta == ans){
				ways++;
			}
			leaf[v] += leaf[u];
			degreeNow[u] = 0;
			degreeNow[v]--;
			if(degreeNow[v] == 1) que[tail++] = v;
		}
		cout << ans << ' ' << ways << '\n';
	}
	return 0;
}
