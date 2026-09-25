#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
long long a[N],num[N];
int den[N],opL[N],opR[N];

bool lessEqual(long long x,int nx,long long y,int ny){
	long long qx = x / nx,qy = y / ny;
	if(qx != qy) return qx < qy;
	return x % nx * ny <= y % ny * nx;
}

long long gcdValue(long long x,long long y){
	while(y){
		long long z = x % y;
		x = y;
		y = z;
	}
	return x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		num[i] = a[i];
		den[i] = 1;
	}
	int used = 0,start = 1;
	while(start <= n){
		long long prefix = 0,bestSum = -1;
		int end = start,bestLen = 1;
		for(int i = start; i <= n; i++){
			prefix += a[i];
			int len = i - start + 1;
			if(bestSum == -1 || lessEqual(bestSum,bestLen,prefix,len)){
				bestSum = prefix;
				bestLen = len;
				end = i;
			}
		}
		int last = 0;
		for(int i = start; i <= end; i++){
			if(a[i] * bestLen != bestSum) last = i;
		}
		if(last != 0 && used < k){
			used++;
			opL[used] = start;
			opR[used] = last;
			long long g = gcdValue(bestSum,bestLen);
			for(int i = start; i <= end; i++){
				num[i] = bestSum / g;
				den[i] = bestLen / g;
			}
		}
		start = end + 1;
	}
	cout << used << '\n';
	for(int i = 1; i <= n; i++){
		if(i > 1) cout << ' ';
		cout << num[i] << '/' << den[i];
	}
	cout << '\n';
	for(int i = 1; i <= used; i++) cout << opL[i] << ' ' << opR[i] << '\n';
	return 0;
}
