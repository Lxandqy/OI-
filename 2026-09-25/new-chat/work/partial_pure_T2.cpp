#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int deg[N],neighbor[N][2],edgeId[N][2],ringEdge[N];
int candidate[N],answer[N],bestCount = -1;
bool cutEdge[N];

void consider(int n){
	int count = 0;
	for(int id = 1; id <= n; id++){
		if(cutEdge[id]) candidate[++count] = id;
	}
	if(bestCount == -1 || lexicographical_compare(candidate + 1,candidate + count + 1,answer + 1,answer + bestCount + 1)){
		bestCount = count;
		for(int i = 1; i <= count; i++) answer[i] = candidate[i];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for(int id = 1; id <= n; id++){
		int u,v;
		cin >> u >> v;
		neighbor[u][deg[u]] = v;
		edgeId[u][deg[u]++] = id;
		neighbor[v][deg[v]] = u;
		edgeId[v][deg[v]++] = id;
	}
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	int current = 1,last = 0;
	for(int i = 1; i <= n; i++){
		int side = neighbor[current][0] == last ? 1 : 0;
		ringEdge[i] = edgeId[current][side];
		int next = neighbor[current][side];
		last = current;
		current = next;
	}
	if(n == 3){
		cout << "0\n\n";
		return 0;
	}
	for(int offset = 0; offset < 3; offset++){
		for(int id = 1; id <= n; id++) cutEdge[id] = false;
		for(int i = 1; i <= n; i++){
			if((i - 1) % 3 == offset) cutEdge[ringEdge[i]] = true;
		}
		consider(n);
	}
	cout << bestCount << '\n';
	for(int i = 1; i <= bestCount; i++){
		if(i > 1) cout << ' ';
		cout << answer[i];
	}
	cout << '\n';
	return 0;
}
