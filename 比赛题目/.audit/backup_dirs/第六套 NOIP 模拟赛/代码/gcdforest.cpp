#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
const int mod = 1000000007;
struct node{
	int u,v,w;
}e[N];
int n,mx,a[N],fa[N],sz[N],phi[N];
vector<int> dv[N],b[N];

int gcd(int x,int y){
	while(y){
		int z = x % y;
		x = y;
		y = z;
	}
	return x;
}

int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool cmp(node x,node y){
	return x.w > y.w;
}

int main(){
	freopen("gcdforest.in","r",stdin);
	freopen("gcdforest.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		mx = max(mx,a[i]);
	}
	for(int i = 1; i < n; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	for(int i = 1; i <= mx; i++) phi[i] = i;
	for(int i = 1; i <= mx; i++){
		for(int j = i; j <= mx; j += i) dv[j].push_back(i);
		if(i == 1 || phi[i] != i) continue;
		for(int j = i; j <= mx; j += i){
			phi[j] = phi[j] / i * (i - 1);
		}
	}
	sort(e + 1,e + n,cmp);
	for(int i = 1; i < n; i++){
		int g = gcd(a[e[i].u],a[e[i].v]);
		for(int j = 0; j < (int)dv[g].size(); j++){
			b[dv[g][j]].push_back(i);
		}
	}
	long long ans = 0;
	for(int d = 1; d <= mx; d++){
		// 初始化全部相关端点后，再按容量降序合并。
		for(int i = 0; i < (int)b[d].size(); i++){
			int id = b[d][i];
			fa[e[id].u] = e[id].u;
			fa[e[id].v] = e[id].v;
			sz[e[id].u] = 1;
			sz[e[id].v] = 1;
		}
		for(int i = 0; i < (int)b[d].size(); i++){
			int id = b[d][i];
			int x = find(e[id].u),y = find(e[id].v);
			if(x == y) continue;
			if(sz[x] < sz[y]) swap(x,y);
			long long add = 1LL * sz[x] * sz[y] % mod;
			add = add * e[id].w % mod;
			ans = (ans + add * phi[d]) % mod;
			fa[y] = x;
			sz[x] += sz[y];
		}
	}
	cout << ans << '\n';
	return 0;
}
