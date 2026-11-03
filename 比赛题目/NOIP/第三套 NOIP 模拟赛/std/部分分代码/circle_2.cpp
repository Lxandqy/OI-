// 朋友圈 部分分 2：没有删边时正序合并，覆盖第 9-10 点共 10 分。
// 按大小合并并压缩路径，总时间 O(n+(m+q)alpha(n))，空间 O(n)。
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100005;
int fa[N],sz[N],mx[N];
long long ans;
int find(int x){
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
void join(int u,int v){
	u = find(u);
	v = find(v);
	if(u == v) return;
	if(sz[u] < sz[v]) swap(u,v);
	ans -= min(mx[u],mx[v]);
	fa[v] = u;
	sz[u] += sz[v];
	mx[u] = max(mx[u],mx[v]);
}
void init(int n){
	ans = 1LL * n * (n + 1) / 2;
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		sz[i] = 1;
		mx[i] = i;
	}
}
int main(){
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m,q;
	cin >> n >> m;
	init(n);
	for(int i = 1; i <= m; i++){
		int u,v;
		cin >> u >> v;
		join(u,v);
	}
	cin >> q;
	for(int i = 1; i <= q; i++){
		int op;
		cin >> op;
		if(op == 3) cout << ans << '\n';
		else{
			int u,v;
			cin >> u >> v;
			if(op == 1) join(u,v);
		}
	}
	return 0;
}
