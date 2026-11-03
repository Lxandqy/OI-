// dance, partial 2: all boys distinct, count only girl conflicts.
// Otherwise fall back to pair enumeration. Points 1-9, guaranteed 45 points.
// O(sum(a+b+k)) for the property; O(sum(a+b+k^2)) otherwise.
#include<iostream>
#include<algorithm>
#include<cstdio>
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
		bool ok = true;
		for(int i = 1; i <= a; i++){
			if(c[i] > 1) ok = false;
		}
		long long ans = 0;
		if(ok){
			ans = 1ll * k * (k - 1) / 2;
			for(int i = 1; i <= b; i++) ans -= 1ll * d[i] * (d[i] - 1) / 2;
		}else{
			for(int i = 1; i <= k; i++){
				for(int j = i + 1; j <= k; j++){
					if(x[i] != x[j] && y[i] != y[j]) ans++;
				}
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
