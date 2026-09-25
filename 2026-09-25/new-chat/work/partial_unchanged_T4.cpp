#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,k;
	cin >> n >> k;
	cout << 0 << '\n';
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		if(i > 1) cout << ' ';
		cout << x << "/1";
	}
	cout << '\n';
	return 0;
}
