#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
long long a[N];

long long gcdValue(long long a,long long b){
	while(b){
		long long c = a % b;
		a = b;
		b = c;
	}
	return a;
}

bool lessEqualAverage(long long x,int nx,long long y,int ny){
	long long qx = x / nx,qy = y / ny;
	if(qx != qy) return qx < qy;
	return (x % nx) * ny <= (y % ny) * nx;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long sum = 0,bestSum = -1;
	int bestLength = 1,end = 1;
	for(int i = 1; i <= n; i++){
		sum += a[i];
		if(bestSum == -1 || lessEqualAverage(bestSum,bestLength,sum,i)){
			bestSum = sum;
			bestLength = i;
			end = i;
		}
	}
	int last = 0;
	for(int i = 1; i <= end; i++){
		if(a[i] * bestLength != bestSum) last = i;
	}
	long long g = gcdValue(bestSum,bestLength);
	cout << 1 << '\n';
	for(int i = 1; i <= n; i++){
		if(i > 1) cout << ' ';
		if(i <= end) cout << bestSum / g << '/' << bestLength / g;
		else cout << a[i] << "/1";
	}
	cout << '\n' << 1 << ' ' << last << '\n';
	return 0;
}
