#include<bits/stdc++.h>
using namespace std;

const int N = 200000 + 10;
int n,d,fa[N],dep[N],q[N],a[N],b[N],ha[N],hb[N];
int sum,ans;
vector<int> g[N];

int main(){
	freopen("patrol.in","r",stdin);
	freopen("patrol.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> d;
	for(int i = 1; i < n; i++){
		int x,y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	int l = 1,r = 1;
	q[1] = 1;
	while(l <= r){
		int x = q[l++];
		for(int i = 0; i < (int)g[x].size(); i++){
			int y = g[x][i];
			if(y == fa[x]) continue;
			fa[y] = x;
			dep[y] = dep[x] + 1;
			q[++r] = y;
		}
	}
	for(int i = 1; i <= n; i++){
		a[i] = -1;
		b[i] = -1;
	}
	int m,x;
	cin >> m;
	for(int i = 1; i <= m; i++){
		cin >> x;
		a[x] = dep[x];
	}
	cin >> m;
	for(int i = 1; i <= m; i++){
		cin >> x;
		b[x] = dep[x];
	}
	for(int i = n; i >= 1; i--){
		x = q[i];
		ha[x] = max(a[x],b[x] - d) - dep[x];
		hb[x] = max(b[x],a[x] - d) - dep[x];
		if(ha[x] < 0) ha[x] = -1;
		if(hb[x] < 0) hb[x] = -1;
		if(x != 1){
			if(ha[x] >= 0) sum += 2;
			if(hb[x] >= 0) sum += 2;
			a[fa[x]] = max(a[fa[x]],a[x]);
			b[fa[x]] = max(b[fa[x]],b[x]);
		}
		if(ha[x] >= 0 && hb[x] >= 0){
			ans = max(ans,2 * dep[x] + min(d,ha[x] + hb[x]));
		}
	}
	cout << sum - ans << '\n';
	return 0;
}
