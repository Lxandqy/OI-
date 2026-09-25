#include<bits/stdc++.h>
using namespace std;

int a[2005], leftLess[2005][2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	// leftLess[j][k]：下标小于 j、数值小于 a[k] 的元素数。
	for(int k = 1; k <= n; k++){
		for(int j = 2; j < k; j++){
			leftLess[j][k] = leftLess[j - 1][k];
			if(a[j - 1] < a[k]){
				leftLess[j][k]++;
			}
		}
	}
	long long ans = 0;
	for(int j = 2; j <= n - 2; j++){
		long long rightGreater = 0;
		for(int k = n; k > j; k--){
			if(a[k] <= a[j]){
				ans += leftLess[j][k] * rightGreater;
			}
			// 更新放在计数之后，保证第四个位置严格大于 k。
			if(a[k] > a[j]){
				rightGreater++;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
