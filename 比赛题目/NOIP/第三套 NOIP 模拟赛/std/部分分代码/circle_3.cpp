// 朋友圈 部分分 3：没有加边时倒序恢复被删的边，覆盖第 11-12 点共 10 分。
// 总时间 O(n+(m+q)(log(n+1)+alpha(n)))，空间 O(n+m+q)。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<utility>
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
const int Q = 200005;
int op[Q],x[Q],y[Q];
long long out[Q];
int main(){
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m,q;
	cin >> n >> m;
	set<pair<int,int> > left;
	for(int i = 1; i <= m; i++){
		int u,v;
		cin >> u >> v;
		if(u > v) swap(u,v);
		left.insert(make_pair(u,v));
	}
	cin >> q;
	for(int i = 1; i <= q; i++){
		cin >> op[i];
		if(op[i] == 3) continue;
		cin >> x[i] >> y[i];
		if(x[i] > y[i]) swap(x[i],y[i]);
		if(op[i] == 2) left.erase(make_pair(x[i],y[i]));
	}
	init(n);
	set<pair<int,int> >::iterator it;
	for(it = left.begin(); it != left.end(); it++) join(it->first,it->second);
	for(int i = q; i >= 1; i--){
		if(op[i] == 3) out[i] = ans;
		else if(op[i] == 2) join(x[i],y[i]);
	}
	for(int i = 1; i <= q; i++){
		if(op[i] == 3) cout << out[i] << '\n';
	}
	return 0;
}
