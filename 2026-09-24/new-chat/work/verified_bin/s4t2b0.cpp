#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	long long k;
	cin >> n >> k;
	static long long a[200010];
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			long long sum = a[i] * a[i] + a[j] * a[j];
			if(sum % k == 0) ans = max(ans,sum);
		}
	}
	cout << ans << '\n';
	return 0;
}
