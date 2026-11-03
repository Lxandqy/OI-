#include<bits/stdc++.h>
using namespace std;

const int N = 200000 + 10;
const int mod = 998244353;
struct edge{
	int u,v,w;
};
int n,m,fa[N],sz[N],deg[N],mark[N],sum[N];
bool active[N],seen[N];
vector<pair<int,int> > g[N];

int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x,y);
	fa[y] = x;
	sz[x] += sz[y];
}

bool cmp_weight(edge x,edge y){
	return x.w < y.w;
}

bool cmp_pair(edge x,edge y){
	if(x.u != y.u) return x.u < y.u;
	return x.v < y.v;
}

bool lower_rank(int x,int y){
	if(deg[x] != deg[y]) return deg[x] < deg[y];
	return x < y;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	vector<edge> a(m);
	for(int i = 0; i < m; i++) cin >> a[i].u >> a[i].v >> a[i].w;
	sort(a.begin(),a.end(),cmp_weight);
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		sz[i] = 1;
	}
	long long total = 0,f[5] = {1,0,0,0,0};
	long long triangles = 0,weighted = 0,cycles = 0;
	for(int l = 0; l < m; ){
		int r = l;
		while(r < m && a[r].w == a[l].w) r++;
		vector<edge> current;
		vector<int> vertices;
		for(int i = l; i < r; i++){
			int x = find(a[i].u),y = find(a[i].v);
			if(x == y) continue;
			if(x > y) swap(x,y);
			current.push_back({x,y,0});
			total++;
		}
		sort(current.begin(),current.end(),cmp_pair);
		for(int i = 0; i < (int)current.size(); ){
			int j = i + 1;
			while(j < (int)current.size() && current[j].u == current[i].u
				&& current[j].v == current[i].v) j++;
			int x = current[i].u,y = current[i].v,c = j - i;
			for(int k = 4; k >= 1; k--) f[k] = (f[k] + f[k - 1] * c) % mod;
			g[x].push_back(make_pair(y,c));
			g[y].push_back(make_pair(x,c));
			deg[x]++;
			deg[y]++;
			if(!active[x]){
				active[x] = true;
				vertices.push_back(x);
			}
			if(!active[y]){
				active[y] = true;
				vertices.push_back(y);
			}
			i = j;
		}
		for(int i = 0; i < (int)vertices.size(); i++){
			int v = vertices[i];
			vector<int> touched;
			for(int j = 0; j < (int)g[v].size(); j++){
				mark[g[v][j].first] = g[v][j].second;
			}
			for(int j = 0; j < (int)g[v].size(); j++){
				int u = g[v][j].first,c = g[v][j].second;
				if(!lower_rank(u,v)) continue;
				for(int k = 0; k < (int)g[u].size(); k++){
					int w = g[u][k].first,d = g[u][k].second;
					if(!lower_rank(w,v)) continue;
					long long path = 1LL * c * d % mod;
					if(mark[w] && lower_rank(u,w)){
						long long value = path * mark[w] % mod;
						triangles = (triangles + value) % mod;
						weighted = (weighted + value * (c + d + mark[w])) % mod;
					}
					cycles = (cycles + sum[w] * path) % mod;
					sum[w] = (sum[w] + path) % mod;
					if(!seen[w]){
						seen[w] = true;
						touched.push_back(w);
					}
				}
			}
			for(int j = 0; j < (int)touched.size(); j++){
				sum[touched[j]] = 0;
				seen[touched[j]] = false;
			}
			for(int j = 0; j < (int)g[v].size(); j++) mark[g[v][j].first] = 0;
		}
		for(int i = 0; i < (int)vertices.size(); i++){
			int x = vertices[i];
			g[x].clear();
			deg[x] = 0;
			active[x] = false;
		}
		for(int i = l; i < r; i++) join(a[i].u,a[i].v);
		l = r;
	}
	long long answer = (f[4] - total * triangles % mod + weighted - cycles) % mod;
	cout << (answer + mod) % mod << '\n';
	return 0;
}
