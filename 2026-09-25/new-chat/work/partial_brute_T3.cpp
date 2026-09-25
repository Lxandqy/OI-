#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int n,a[N],f[N],u[N],v[N],fa[N],chosen[N];

int findRoot(int x){
	if(fa[x] == x) return x;
	fa[x] = findRoot(fa[x]);
	return fa[x];
}

bool connected(bool association){
	for(int i = 1; i <= n; i++) fa[i] = i;
	if(association){
		for(int i = 1; i <= n; i++){
			if(chosen[i]){
				int x = findRoot(i),y = findRoot(f[i]);
				fa[x] = y;
			}
		}
	}else{
		for(int i = 1; i < n; i++){
			if(chosen[u[i]] && chosen[v[i]]){
				int x = findRoot(u[i]),y = findRoot(v[i]);
				fa[x] = y;
			}
		}
	}
	int first = 0;
	for(int i = 1; i <= n; i++){
		if(chosen[i]){
			if(first == 0) first = findRoot(i);
			else if(findRoot(i) != first) return false;
		}
	}
	return true;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++) cin >> u[i] >> v[i];
	if(n == 1){
		cout << 1 << '\n';
		return 0;
	}
	for(int i = 1; i <= n; i++){
		int best = -1;
		for(int j = 1; j <= n; j++){
			if(i == j) continue;
			if(best == -1 || (a[i] ^ a[j]) < (a[i] ^ a[best])) best = j;
		}
		f[i] = best;
	}
	int ans = 0;
	while(true){
		int count = 0;
		for(int i = 1; i <= n; i++){
			if(chosen[i]) count++;
		}
		if(count > ans){
			bool closed = true;
			for(int i = 1; i <= n; i++){
				if(chosen[i] && !chosen[f[i]]) closed = false;
			}
			if(closed && connected(false) && connected(true)) ans = count;
		}
		int p = 1;
		while(p <= n && chosen[p]){
			chosen[p] = 0;
			p++;
		}
		if(p > n) break;
		chosen[p] = 1;
	}
	cout << ans << '\n';
	return 0;
}
