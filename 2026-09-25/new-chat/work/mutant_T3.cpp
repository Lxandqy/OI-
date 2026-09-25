#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
const int M = 6000005;
int trie[M][2],cnt[M],nodes = 1;
int a[N],f[N],dsu[N],sizeD[N],comp[N],core[N];
int head[N],to[2 * N],nxt[2 * N],ecnt;
int revHead[N],revNext[N];
int region[N],parentTree[N],bad[N],que[N],badQue[N];

void add(int u,int v){
	ecnt++;
	to[ecnt] = v;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
}

void insertValue(int x,int id){
	int u = 1;
	cnt[u]++;
	for(int b = 29; b >= 0; b--){
		int t = (x >> b) & 1;
		if(!trie[u][t]) trie[u][t] = ++nodes;
		u = trie[u][t];
		if(b == 0) cnt[u] = -id;
		else cnt[u]++;
	}
}

int nearest(int x){
	int u = 1;
	bool different = false;
	for(int b = 29; b >= 0; b--){
		int t = (x >> b) & 1;
		int same = trie[u][t],other = trie[u][t ^ 1];
		if(!different){
			if(same && cnt[same] > 1){
				u = same;
			}else{
				u = other;
				different = true;
			}
		}else{
			u = same ? same : other;
		}
	}
	return -cnt[u];
}

int findRoot(int x){
	if(dsu[x] == x) return x;
	dsu[x] = findRoot(dsu[x]);
	return dsu[x];
}

void unite(int x,int y){
	x = findRoot(x);
	y = findRoot(y);
	if(x == y) return;
	if(sizeD[x] < sizeD[y]) swap(x,y);
	dsu[y] = x;
	sizeD[x] += sizeD[y];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,u,v;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		insertValue(a[i],i);
		dsu[i] = i;
		sizeD[i] = 1;
	}
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	if(n == 1){
		cout << 1 << '\n';
		return 0;
	}
	for(int i = 1; i <= n; i++){
		f[i] = nearest(a[i]);
		unite(i,f[i]);
		revNext[i] = revHead[f[i]];
		revHead[f[i]] = i;
	}
	int only = 0;
	for(int i = 1; i <= n; i++) only = max(only,sizeD[findRoot(i)]);
	cout << only << '\n';
	return 0;
	for(int i = 1; i <= n; i++) comp[i] = findRoot(i);
	for(int i = 1; i <= n; i++){
		if(i < f[i] && f[f[i]] == i) core[comp[i]] = i;
	}
	int ans = 0;
	for(int c = 1; c <= n; c++){
		int root = core[c];
		if(root == 0) continue;
		int front = 1,back = 1;
		que[1] = root;
		region[root] = root;
		parentTree[root] = 0;
		while(front <= back){
			int x = que[front++];
			for(int e = head[x]; e; e = nxt[e]){
				int y = to[e];
				if(comp[y] != c || region[y] == root) continue;
				region[y] = root;
				parentTree[y] = x;
				que[++back] = y;
			}
		}
		if(region[f[root]] != root) continue;
		int removed = 0;
		front = 1;
		int badCount = 0;
		for(int i = 1; i <= back; i++){
			int x = que[i];
			if(region[f[x]] != root){
				bad[x] = root;
				badQue[++badCount] = x;
			}
		}
		while(front <= badCount){
			int x = badQue[front++];
			removed++;
			for(int e = head[x]; e; e = nxt[e]){
				int y = to[e];
				if(region[y] == root && parentTree[y] == x && bad[y] != root){
					bad[y] = root;
					badQue[++badCount] = y;
				}
			}
			for(int y = revHead[x]; y; y = revNext[y]){
				if(region[y] == root && bad[y] != root){
					bad[y] = root;
					badQue[++badCount] = y;
				}
			}
		}
		ans = max(ans,back - removed);
	}
	cout << ans << '\n';
	return 0;
}
