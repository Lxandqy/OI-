// ²¿·Ö·Ö 1
// Problem: star; method: cubic.
// Applicable condition: n <= 100.
// Guaranteed test points: 1-4; guaranteed score: 20/100.
// Time: O(n^3); space: O(n) (includes stored input / DP table).
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
		for(int r = l + k - 1; r <= n; r++){
			int bad = 0;
			for(int i = l; i <= r; i++){
				if(a[i] > q) bad++;
			}
			if(bad <= m) ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
