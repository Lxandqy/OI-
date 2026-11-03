// ²¿·Ö·Ö 2
// Problem: star; method: quadratic.
// Applicable condition: n <= 5000.
// Guaranteed test points: 1-10; guaranteed score: 50/100.
// Time: O(n^2); space: O(n) (includes stored input / DP table).
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k,m,q;
int a[N];
int main(){
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	cin >> n >> k >> m >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	for(int l = 1; l <= n; l++){
		int bad = 0;
		for(int r = l; r <= n; r++){
			if(a[r] > q) bad++;
			if(bad > m) break;
			if(r - l + 1 >= k) ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
