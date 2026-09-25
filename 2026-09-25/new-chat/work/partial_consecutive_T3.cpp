#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int a[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	if(n == 1){
		cout << 1 << '\n';
		return 0;
	}
	bool found = false;
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		if((a[u] ^ 1) == a[v]) found = true;
	}
	cout << (found ? 2 : 0) << '\n';
	return 0;
}
