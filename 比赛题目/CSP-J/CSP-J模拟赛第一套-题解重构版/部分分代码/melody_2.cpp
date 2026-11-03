// ²¿·Ö·Ö 2
/*
T3 melody; scan increasing runs. Valid for k = 0.
Guaranteed: points 4-6 (15), already covered by search. Time O(n); source space O(n).
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k;
int a[N];
int main(){
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int ans = 0,len = 0;
	for(int i = 1; i <= n; i++){
		if(i > 1 && a[i - 1] < a[i]) len++;
		else len = 1;
		ans = max(ans,len);
	}
	cout << ans << endl;
	return 0;
}
