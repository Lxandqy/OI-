#include<bits/stdc++.h>
using namespace std;

int a[2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			for(int k = j + 1; k <= n; k++){
				for(int l = k + 1; l <= n; l++){
					if(a[i] < a[k] && a[k] < a[j] && a[j] < a[l]){
						ans++;
					}
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
