// dance, partial 1: enumerate two candidate pairs.
// Sum k <= 2000; points 1-6, guaranteed 30 points.
// O(sum k^2) time, O(max k) space.
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int N = 200010;
int t,a,b,k,x[N],y[N];

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
		long long ans = 0;
		for(int i = 1; i <= k; i++){
			for(int j = i + 1; j <= k; j++){
				if(x[i] != x[j] && y[i] != y[j]) ans++;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
