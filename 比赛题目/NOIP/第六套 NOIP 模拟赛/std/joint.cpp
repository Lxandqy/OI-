#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
const int L = 19;
struct edge{
	int u,v,w;
};
edge e[N];
int n,m,q,fa[N],sz[N],dep[N],dfn[N],f[N][L],mx[N][L];
vector<pair<int,int> > g[N];
bool cmp(edge a,edge b){
	return a.w < b.w;
}
bool cmpdfn(int a,int b){
	return dfn[a] < dfn[b];
}
int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
bool merge(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return false;
	if(sz[x] < sz[y]) swap(x,y);
	fa[y] = x;
	sz[x] += sz[y];
	return true;
}
int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int j = L - 1; j >= 0; j--){
		if(dep[f[x][j]] >= dep[y]) x = f[x][j];
	}
	if(x == y) return x;
	for(int j = L - 1; j >= 0; j--){
		if(f[x][j] != f[y][j]){
			x = f[x][j];
			y = f[y][j];
		}
	}
	return f[x][0];
}
int query(int x,int y){
	int ans = 0;
	for(int j = L - 1; j >= 0; j--){
		if(dep[f[x][j]] >= dep[y]){
			ans = max(ans,mx[x][j]);
			x = f[x][j];
		}
	}
	return ans;
}
int main(){
	freopen("joint.in","r",stdin);
	freopen("joint.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> q;
	vector<edge> a;
	for(int i = 1; i <= m; i++){
		cin >> e[i].u >> e[i].v >> e[i].w;
		a.push_back(e[i]);
	}
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		sz[i] = 1;
	}
	sort(a.begin(),a.end(),cmp);
	long long sum = 0;
	for(int i = 0; i < m; i++){
		int x = a[i].u,y = a[i].v,w = a[i].w;
		if(merge(x,y)){
			sum += w;
			g[x].push_back(make_pair(y,w));
			g[y].push_back(make_pair(x,w));
		}
	}
	vector<int> st;
	st.push_back(1);
	dep[1] = 1;
	int timer = 0;
	while(!st.empty()){
		int x = st.back();
		st.pop_back();
		dfn[x] = ++timer;
		for(int i = 0; i < (int)g[x].size(); i++){
			int y = g[x][i].first,w = g[x][i].second;
			if(y == f[x][0]) continue;
			dep[y] = dep[x] + 1;
			f[y][0] = x;
			mx[y][0] = w;
			for(int j = 1; j < L; j++){
				f[y][j] = f[f[y][j - 1]][j - 1];
				mx[y][j] = max(mx[y][j - 1],mx[f[y][j - 1]][j - 1]);
			}
			st.push_back(y);
		}
	}
	while(q--){
		int k;
		cin >> k;
		vector<int> id(k),v;
		for(int i = 0; i < k; i++){
			cin >> id[i];
			v.push_back(e[id[i]].u);
			v.push_back(e[id[i]].v);
		}
		sort(v.begin(),v.end(),cmpdfn);
		v.erase(unique(v.begin(),v.end()),v.end());
		int s = v.size();
		for(int i = 1; i < s; i++) v.push_back(lca(v[i - 1],v[i]));
		sort(v.begin(),v.end(),cmpdfn);
		v.erase(unique(v.begin(),v.end()),v.end());
		for(int i = 0; i < (int)v.size(); i++){
			fa[v[i]] = v[i];
			sz[v[i]] = 1;
		}
		long long ans = sum;
		a.clear();
		st.clear();
		for(int i = 0; i < (int)v.size(); i++){
			int x = v[i];
			while(!st.empty() && lca(st.back(),x) != st.back()) st.pop_back();
			if(!st.empty()){
				int y = st.back(),w = query(x,y);
				edge b = {x,y,w};
				a.push_back(b);
				ans -= w;
			}
			st.push_back(x);
		}
		bool ok = true;
		for(int i = 0; i < k; i++){
			edge b = e[id[i]];
			if(!merge(b.u,b.v)) ok = false;
			ans += b.w;
		}
		if(!ok){
			cout << -1 << '\n';
			continue;
		}
		sort(a.begin(),a.end(),cmp);
		for(int i = 0; i < (int)a.size(); i++){
			if(merge(a[i].u,a[i].v)) ans += a[i].w;
		}
		cout << ans << '\n';
	}
	return 0;
}
