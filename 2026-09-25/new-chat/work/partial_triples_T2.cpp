#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int eu[N],ev[N],head[N],to[2 * N],nextEdge[2 * N],deg[N],queueNode[N],countEdge;
bool alive[N];

void add(int u,int v){
	countEdge++;
	to[countEdge] = v;
	nextEdge[countEdge] = head[u];
	head[u] = countEdge;
	deg[u]++;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> eu[i] >> ev[i];
		add(eu[i],ev[i]);
		add(ev[i],eu[i]);
	}
	for(int i = 1; i <= n; i++) alive[i] = true;
	int front = 1,back = 0;
	for(int i = 1; i <= n; i++){
		if(deg[i] == 1) queueNode[++back] = i;
	}
	while(front <= back){
		int u = queueNode[front++];
		alive[u] = false;
		for(int e = head[u]; e; e = nextEdge[e]){
			int v = to[e];
			if(!alive[v]) continue;
			deg[v]--;
			if(deg[v] == 1) queueNode[++back] = v;
		}
	}
	int count = 0;
	for(int id = 1; id <= n; id++){
		if(alive[eu[id]] && alive[ev[id]]) count++;
	}
	cout << count << '\n';
	bool first = true;
	for(int id = 1; id <= n; id++){
		if(alive[eu[id]] && alive[ev[id]]){
			if(!first) cout << ' ';
			cout << id;
			first = false;
		}
	}
	cout << '\n';
	return 0;
}
