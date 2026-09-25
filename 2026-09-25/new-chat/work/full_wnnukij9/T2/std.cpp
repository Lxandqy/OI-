#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int head[N],to[2 * N],nxt[2 * N],eid[2 * N],ecnt;
int deg[N],que[N],par[N],pe[N],sz[N];
int cyc[N],ce[N],residue[N],forced[N],fcnt;
bool alive[N],mark[N];
int answer[N],acnt,candidate[N],ccnt;

void add(int u,int v,int id){
	ecnt++;
	to[ecnt] = v;
	eid[ecnt] = id;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
	deg[u]++;
}

void consider(){
	sort(candidate + 1,candidate + ccnt + 1);
	if(acnt == -1 || lexicographical_compare(candidate + 1,candidate + ccnt + 1,answer + 1,answer + acnt + 1)){
		acnt = ccnt;
		for(int i = 1; i <= ccnt; i++) answer[i] = candidate[i];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,u,v;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> u >> v;
		add(u,v,i);
		add(v,u,i);
	}
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	for(int i = 1; i <= n; i++){
		alive[i] = true;
		sz[i] = 1;
	}
	int front = 1,back = 0;
	for(int i = 1; i <= n; i++){
		if(deg[i] == 1) que[++back] = i;
	}
	while(front <= back){
		int x = que[front++];
		alive[x] = false;
		for(int e = head[x]; e; e = nxt[e]){
			int y = to[e];
			if(!alive[y]) continue;
			par[x] = y;
			pe[x] = eid[e];
			deg[y]--;
			if(deg[y] == 1) que[++back] = y;
		}
	}
	for(int i = 1; i <= back; i++){
		int x = que[i],y = par[x];
		if(sz[x] > 3){
			cout << -1 << '\n';
			return 0;
		}
		if(sz[x] == 3){
			forced[++fcnt] = pe[x];
		}else{
			sz[y] += sz[x];
			if(sz[y] > 3){
				cout << -1 << '\n';
				return 0;
			}
		}
	}
	int start = 0;
	for(int i = 1; i <= n; i++){
		if(alive[i]){
			start = i;
			break;
		}
	}
	int x = start,last = 0,len = 0;
	do{
		cyc[++len] = x;
		int next = 0,edge = 0;
		for(int e = head[x]; e; e = nxt[e]){
			int y = to[e];
			if(alive[y] && y != last){
				next = y;
				edge = eid[e];
				break;
			}
		}
		ce[len] = edge;
		last = x;
		x = next;
	}while(x != start);
	acnt = -1;
	if(len == 3 && sz[cyc[1]] == 1 && sz[cyc[2]] == 1 && sz[cyc[3]] == 1){
		ccnt = 0;
		for(int i = 1; i <= fcnt; i++) candidate[++ccnt] = forced[i];
		consider();
	}
	int prefix = 0;
	for(int i = 1; i <= len; i++){
		prefix += sz[cyc[i]];
		residue[i] = prefix % 3;
	}
	for(int r = 0; r < 3; r++){
		int first = 0;
		for(int i = 1; i <= len; i++){
			mark[i] = residue[i] == r;
			if(mark[i] && first == 0) first = i;
		}
		if(first == 0) continue;
		bool good = true;
		int sum = 0,i = first;
		do{
			i = i % len + 1;
			sum += sz[cyc[i]];
			if(mark[i]){
				if(sum != 3) good = false;
				sum = 0;
			}
		}while(i != first);
		if(!good) continue;
		ccnt = 0;
		for(int j = 1; j <= fcnt; j++) candidate[++ccnt] = forced[j];
		for(int j = 1; j <= len; j++){
			if(mark[j]) candidate[++ccnt] = ce[j];
		}
		consider();
	}
	if(acnt == -1){
		cout << -1 << '\n';
	}else{
		cout << acnt << '\n';
		for(int i = 1; i <= acnt; i++){
			if(i > 1) cout << ' ';
			cout << answer[i];
		}
		cout << '\n';
	}
	return 0;
}
