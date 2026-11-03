#include<bits/stdc++.h>
using namespace std;

const int N = 200010;
int t,a,b,k,x[N],y[N],c[N],d[N];

int main(){
	freopen("dance.in","r",stdin);
	freopen("dance.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--){
		cin >> a >> b >> k;
		for(int i = 1; i <= k; i++) cin >> x[i];
		for(int i = 1; i <= k; i++) cin >> y[i];
		for(int i = 1; i <= a; i++) c[i] = 0;
		for(int i = 1; i <= b; i++) d[i] = 0;
		for(int i = 1; i <= k; i++){
			c[x[i]]++;
			d[y[i]]++;
		}
		long long ans = 1ll * k * (k - 1) / 2;
		for(int i = 1; i <= a; i++) ans -= 1ll * c[i] * (c[i] - 1) / 2;
		for(int i = 1; i <= b; i++) ans -= 1ll * d[i] * (d[i] - 1) / 2;
		cout << ans << '\n';
	}
	return 0;
}
