#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int c,n,m;
int eu[N],ev[N];
int head[N],nxt[2 * N],eid[2 * N],gcnt;     // 原图邻接表（链式前向星），存边的编号
int thead[N],tnxt[2 * N],tto[2 * N],tcnt;   // 桥树（缩点后的树）
int dfn[N],low[N],tim;
bool isBridge[N];
int comp[N],compCnt;
long long sz[N];
int dis[N],pre[N],dep[N],bel[N],q[N];
long long brSum[N];
long long sq;   // sumAtDepth 顺便求出的“各分支和的平方和”
void addEdge(int u,int e){
	nxt[++gcnt] = head[u];
	eid[gcnt] = e;
	head[u] = gcnt;
}
void addTree(int u,int v){
	tnxt[++tcnt] = thead[u];
	tto[tcnt] = v;
	thead[u] = tcnt;
}
// 边 e 的另一个端点
int other(int e,int u){
	if(eu[e] == u) return ev[e];
	return eu[e];
}
// Tarjan 求桥：inE 是走到 u 时经过的边的编号，只跳过这一条边，因此能正确处理重边
void tarjan(int u,int inE){
	dfn[u] = low[u] = ++tim;
	for(int i = head[u]; i != 0; i = nxt[i]){
		int e = eid[i];
		if(e == inE) continue;
		int v = other(e,u);
		if(dfn[v] == 0){
			tarjan(v,e);
			low[u] = min(low[u],low[v]);
			if(low[v] > dfn[u]) isBridge[e] = true;
		}else{
			low[u] = min(low[u],dfn[v]);
		}
	}
}
// 在桥树上从 s 出发 BFS，求距离并记录前驱，返回最远点
int bfs(int s){
	for(int i = 1; i <= compCnt; i++) dis[i] = -1;
	int h = 0,t = 0;
	q[t++] = s;
	dis[s] = 0;
	pre[s] = 0;
	int far = s;
	while(h < t){
		int u = q[h++];
		if(dis[u] > dis[far]) far = u;
		for(int i = thead[u]; i != 0; i = tnxt[i]){
			int v = tto[i];
			if(dis[v] == -1){
				dis[v] = dis[u] + 1;
				pre[v] = u;
				q[t++] = v;
			}
		}
	}
	return far;
}
// 从 s 出发（不经过 block），求与 s 距离恰为 d 的分量大小之和；
// brSum[x] 累加属于 s 的邻居分支 x 的部分，全局变量 sq 记录各分支和的平方和
long long sumAtDepth(int s,int block,int d){
	for(int i = 1; i <= compCnt; i++) dep[i] = -1;
	int h = 0,t = 0;
	q[t++] = s;
	dep[s] = 0;
	bel[s] = 0;
	long long total = 0;
	vector<int> used;
	while(h < t){
		int u = q[h++];
		if(dep[u] == d){
			total += sz[u];
			if(brSum[bel[u]] == 0) used.push_back(bel[u]);
			brSum[bel[u]] += sz[u];
			continue;
		}
		for(int i = thead[u]; i != 0; i = tnxt[i]){
			int v = tto[i];
			if(v == block || dep[v] != -1) continue;
			dep[v] = dep[u] + 1;
			if(u == s) bel[v] = v;
			else bel[v] = bel[u];
			q[t++] = v;
		}
	}
	sq = 0;
	for(int i = 0; i < (int)used.size(); i++){
		sq += brSum[used[i]] * brSum[used[i]];
		brSum[used[i]] = 0;
	}
	return total;
}
int main(){
	freopen("bridge.in","r",stdin);
	freopen("bridge.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		cin >> eu[i] >> ev[i];
		addEdge(eu[i],i);
		addEdge(ev[i],i);
	}
	tarjan(1,0);
	// 不经过桥的连通块就是边双连通分量
	for(int i = 1; i <= n; i++){
		if(comp[i]) continue;
		compCnt++;
		int h = 0,t = 0;
		q[t++] = i;
		comp[i] = compCnt;
		while(h < t){
			int u = q[h++];
			sz[compCnt]++;
			for(int j = head[u]; j != 0; j = nxt[j]){
				int e = eid[j];
				if(isBridge[e]) continue;
				int v = other(e,u);
				if(!comp[v]){
					comp[v] = compCnt;
					q[t++] = v;
				}
			}
		}
	}
	int B = 0;
	for(int e = 1; e <= m; e++){
		if(!isBridge[e]) continue;
		B++;
		addTree(comp[eu[e]],comp[ev[e]]);
		addTree(comp[ev[e]],comp[eu[e]]);
	}
	if(compCnt == 1){
		cout << 0 << ' ' << 1LL * n * (n - 1) / 2 << endl;
		return 0;
	}
	// 桥树直径 D：加的边连接的两个分量在树上距离为 D 时，消去的桥最多
	int a = bfs(1);
	int b = bfs(a);
	int D = dis[b];
	vector<int> path;
	for(int x = b; x != 0; x = pre[x]) path.push_back(x);
	long long ways;
	if(D % 2 == 0){
		// 直径中心是点 mid：两端点到 mid 的距离都是 D/2，且在 mid 的不同分支中
		int mid = path[D / 2];
		long long S = sumAtDepth(mid,0,D / 2);
		ways = (S * S - sq) / 2;
	}else{
		// 直径中心是边 (x,y)：两端点分别在这条边两侧，到 x、y 的距离都是 (D-1)/2
		int x = path[(D - 1) / 2],y = path[(D + 1) / 2];
		long long Wx = sumAtDepth(x,y,(D - 1) / 2);
		long long Wy = sumAtDepth(y,x,(D - 1) / 2);
		ways = Wx * Wy;
	}
	cout << B - D << ' ' << ways << endl;
	return 0;
}
