#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,t,a[N],s[N];
int main(){
	freopen("pairs.in","r",stdin);
	freopen("pairs.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		s[0] = 0;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			s[i] = s[i - 1];
			if(a[i] < i) s[i]++;
		}
		long long ans = 0;
		for(int j = 1; j <= n; j++){
			if(a[j] > 0 && a[j] < j){
				ans += s[a[j] - 1];
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
