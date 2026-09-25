#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int a[N],partner[N],distanceValue[N],parentNode[N],componentSize[N];

int root(int u){
	while(parentNode[u] != u){
		parentNode[u] = parentNode[parentNode[u]];
		u = parentNode[u];
	}
	return u;
}

void join(int u,int v){
	u = root(u);
	v = root(v);
	if(u == v) return;
	if(componentSize[u] < componentSize[v]) swap(u,v);
	parentNode[v] = u;
	componentSize[u] += componentSize[v];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		distanceValue[i] = INT_MAX;
		parentNode[i] = i;
		componentSize[i] = 1;
	}
	if(n == 1){
		cout << 1 << '\n';
		return 0;
	}
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		int d = a[u] ^ a[v];
		if(d < distanceValue[u]){
			distanceValue[u] = d;
			partner[u] = v;
		}
		if(d < distanceValue[v]){
			distanceValue[v] = d;
			partner[v] = u;
		}
	}
	for(int i = 1; i <= n; i++) join(i,partner[i]);
	int answer = 0;
	for(int i = 1; i <= n; i++){
		if(root(i) == i) answer = max(answer,componentSize[i]);
	}
	cout << answer << '\n';
	return 0;
}
