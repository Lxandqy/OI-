#include<bits/stdc++.h>
using namespace std;
const int N = 100010,Q = 200010;
struct node{
	int x,y,s,m;
	long long ans;
};
int n,m,q,fa[N],sz[N],mx[N],op[Q];
long long ans;
vector<pair<int,int> > v[Q * 4];
vector<node> stk;
map<pair<int,int>,int> st;
int find(int x){
	while(fa[x] != x) x = fa[x];
	return x;
}
void merge(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x,y);
	node t;
	t.x = x;
	t.y = y;
	t.s = sz[x];
	t.m = mx[x];
	t.ans = ans;
	stk.push_back(t);
	ans -= mx[x] + mx[y];
	fa[y] = x;
	sz[x] += sz[y];
	mx[x] = max(mx[x],mx[y]);
	ans += mx[x];
}
void add(int x,int l,int r,int ql,int qr,pair<int,int> e){
	if(ql > qr) return;
	if(ql <= l && r <= qr){
		v[x].push_back(e);
		return;
	}
	int mid = (l + r) / 2;
	if(ql <= mid) add(x * 2,l,mid,ql,qr,e);
	if(qr > mid) add(x * 2 + 1,mid + 1,r,ql,qr,e);
}
void dfs(int x,int l,int r){
	int k = stk.size();
	for(int i = 0; i < (int)v[x].size(); i++){
		merge(v[x][i].first,v[x][i].second);
	}
	if(l == r){
		if(op[l] == 3) cout << ans << '\n';
	}else{
		int mid = (l + r) / 2;
		dfs(x * 2,l,mid);
		dfs(x * 2 + 1,mid + 1,r);
	}
	while((int)stk.size() > k){
		node t = stk.back();
		stk.pop_back();
		fa[t.y] = t.y;
		sz[t.x] = t.s;
		mx[t.x] = t.m;
		ans = t.ans;
	}
}
int main(){
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	st.clear();
	stk.clear();
	for(int i = 1; i <= m; i++){
		int x,y;
		cin >> x >> y;
		if(x > y) swap(x,y);
		st[make_pair(x,y)] = 1;
	}
	cin >> q;
	for(int i = 1; i <= 4 * q; i++) v[i].clear();
	for(int i = 1; i <= q; i++){
		cin >> op[i];
		if(op[i] == 3) continue;
		int x,y;
		cin >> x >> y;
		if(x > y) swap(x,y);
		pair<int,int> e = make_pair(x,y);
		if(op[i] == 1) st[e] = i;
		else{
			add(1,1,q,st[e],i - 1,e);
			st.erase(e);
		}
	}
	map<pair<int,int>,int>::iterator it;
	for(it = st.begin(); it != st.end(); it++){
		add(1,1,q,it->second,q,it->first);
	}
	st.clear();
	ans = 1LL * n * (n + 1) / 2;
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		sz[i] = 1;
		mx[i] = i;
	}
	dfs(1,1,q);
	return 0;
}
