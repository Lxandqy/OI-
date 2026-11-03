#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
int n,m,c[N],p;
bool check(int t){
	int x = 0;
	for(int j = 1; j <= n; j++){
		int i = (p + j - 1) % n + 1;
		x = max(0,c[i] + 2 * x - t);
		if(x > c[i]) return false;
	}
	return true;
}
int main(){
	freopen("relay.in","r",stdin);
	freopen("relay.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) c[i] = 0;
	for(int i = 1; i <= m; i++){
		int x;
		cin >> x;
		c[x]++;
	}
	for(int i = 1; i <= n; i++){
		if(c[i] == 0){
			p = i;
			break;
		}
	}
	int l = 1,r = m;
	while(l < r){
		int mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << '\n';
	return 0;
}
