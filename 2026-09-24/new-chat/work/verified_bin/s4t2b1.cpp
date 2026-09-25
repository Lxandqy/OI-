#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,k;
	cin >> n >> k;
	static long long a[200010];
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	if(k <= 100000){
		static long long first[100010],second[100010];
		for(int i = 1; i <= n; i++){
			long long x = a[i];
			int r = x * x % k;
			if(x > first[r]){
				second[r] = first[r];
				first[r] = x;
			}else if(x > second[r]){
				second[r] = x;
			}
		}
		for(int r = 0; r < k; r++){
			int s = (k - r) % k;
			long long x = first[r];
			long long y = r == s ? second[r] : first[s];
			if(x > 0 && y > 0) ans = max(ans,x * x + y * y);
		}
	}else{
		for(int i = 1; i <= n; i++){
			for(int j = i + 1; j <= n; j++){
				long long sum = a[i] * a[i] + a[j] * a[j];
				if(sum % k == 0) ans = max(ans,sum);
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
