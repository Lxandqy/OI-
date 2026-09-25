#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int head[N],to[2 * N],nextEdge[2 * N],edgeId[2 * N],deg[N],originalDeg[N];
int queueNode[N],ringVertex[N],ringEdge[N],answer[N],candidate[N],edgeCount,bestCount = -1;
bool alive[N],mark[N];

void add(int u,int v,int id){
	edgeCount++;
	to[edgeCount] = v;
	edgeId[edgeCount] = id;
	nextEdge[edgeCount] = head[u];
	head[u] = edgeCount;
	deg[u]++;
}

void consider(int n){
	int count = 0;
	for(int id = 1; id <= n; id++){
		if(mark[id]) candidate[++count] = id;
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
		add(u,v,id);
		add(v,u,id);
	}
	for(int i = 1; i <= n; i++){
		alive[i] = true;
		originalDeg[i] = deg[i];
	}
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
	int start = 0;
	for(int i = 1; i <= n; i++){
		if(alive[i]){
			start = i;
			break;
		}
	}
	int current = start,last = 0,length = 0;
	do{
		ringVertex[++length] = current;
		int next = 0,id = 0;
		for(int e = head[current]; e; e = nextEdge[e]){
			int v = to[e];
			if(alive[v] && v != last){
				next = v;
				id = edgeId[e];
				break;
			}
		}
		ringEdge[length] = id;
		last = current;
		current = next;
	}while(current != start);
	for(int cut = 1; cut <= 2; cut++){
		for(int id = 1; id <= n; id++) mark[id] = false;
		int sum = 0;
		bool good = true;
		for(int step = 1; step <= length; step++){
			int j = (cut + step - 1) % length + 1;
			sum += originalDeg[ringVertex[j]] - 1;
			if(sum > 3){
				good = false;
				break;
			}
			if(sum == 3){
				mark[ringEdge[j]] = true;
				sum = 0;
			}
		}
		if(good && sum == 0) consider(n);
	}
	if(bestCount == -1){
		cout << -1 << '\n';
		return 0;
	}
	cout << bestCount << '\n';
	for(int i = 1; i <= bestCount; i++){
		if(i > 1) cout << ' ';
		cout << answer[i];
	}
	cout << '\n';
	return 0;
}
