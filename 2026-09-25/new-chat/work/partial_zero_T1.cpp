#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,b[4],x;
	cin >> n >> b[0] >> b[1] >> b[2] >> b[3];
	long long answer = -(1LL << 60),endHere = 0;
	for(int i = 1; i <= n; i++){
		cin >> x;
		endHere = max((long long)x,endHere + x);
		answer = max(answer,endHere);
	}
	cout << answer << '\n';
	return 0;
}
