#include<bits/stdc++.h>
using namespace std;

long long gcdValue(long long a,long long b){
	while(b){
		long long c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,k;
	cin >> n >> k;
	long long sum = 0;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		sum += x;
	}
	long long g = gcdValue(sum,n);
	cout << 1 << '\n';
	for(int i = 1; i <= n; i++){
		if(i > 1) cout << ' ';
		cout << sum / g << '/' << n / g;
	}
	cout << '\n' << 1 << ' ' << n << '\n';
	return 0;
}
