#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int n,u[N],v[N],bit[N],fa[N],sizeD[N],cnt[N],cur[N],best[N],cn,bn = -1;

int findRoot(int x){
	int root = x;
	while(fa[root] != root) root = fa[root];
	while(fa[x] != x){
		int y = fa[x];
		fa[x] = root;
		x = y;
	}
	return root;
}

bool smaller(){
	if(bn == -1) return true;
	int m = min(cn,bn);
	for(int i = 1; i <= m; i++){
		if(cur[i] != best[i]) return cur[i] < best[i];
	}
	return cn < bn;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) cin >> u[i] >> v[i];
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	while(true){
		for(int i = 1; i <= n; i++){
			fa[i] = i;
			sizeD[i] = 1;
			cnt[i] = 0;
		}
		cn = 0;
		for(int i = 1; i <= n; i++){
			if(bit[i]){
				cur[++cn] = i;
			}else{
				int a = findRoot(u[i]),b = findRoot(v[i]);
				if(a != b){
					if(sizeD[a] < sizeD[b]) swap(a,b);
					fa[b] = a;
					sizeD[a] += sizeD[b];
				}
			}
		}
		for(int i = 1; i <= n; i++) cnt[findRoot(i)]++;
		bool good = true;
		for(int i = 1; i <= n; i++){
			if(cnt[i] != 0 && cnt[i] != 3) good = false;
		}
		if(good && smaller()){
			bn = cn;
			for(int i = 1; i <= cn; i++) best[i] = cur[i];
		}
		int p = 1;
		while(p <= n && bit[p] == 1){
			bit[p] = 0;
			p++;
		}
		if(p > n) break;
		bit[p] = 1;
	}
	if(bn == -1){
		cout << -1 << '\n';
	}else{
		cout << bn << '\n';
		for(int i = 1; i <= bn; i++){
			if(i > 1) cout << ' ';
			cout << best[i];
		}
		cout << '\n';
	}
	return 0;
}
