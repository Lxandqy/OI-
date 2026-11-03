#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
int n,a[N],bit[N];
void add(int x,int v){
	for(int i = x; i <= n; i += i & -i) bit[i] += v;
}
int query(int x){
	int ans = 0;
	for(int i = x; i > 0; i -= i & -i) ans += bit[i];
	return ans;
}
int main(){
	freopen("cross.in","r",stdin);
	freopen("cross.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) bit[i] = 0;
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] > 0 && a[i] < i) ans += query(a[i]);
		if(a[i] + 1 < i){
			add(a[i] + 1,1);
			add(i,-1);
		}
	}
	cout << ans << '\n';
	return 0;
}
