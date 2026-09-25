#include<bits/stdc++.h>
using namespace std;

int a[2005], greaterRight[2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	long long ans = 0;
	for(int j = 2; j <= n - 2; j++){
		greaterRight[n] = 0;
		for(int k = n - 1; k > j; k--){
			greaterRight[k] = greaterRight[k + 1];
			if(a[k + 1] > a[j]){
				greaterRight[k]++;
			}
		}
		for(int i = 1; i < j; i++){
			for(int k = j + 1; k < n; k++){
				if(a[i] < a[k] && a[k] < a[j]){
					ans += greaterRight[k];
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
