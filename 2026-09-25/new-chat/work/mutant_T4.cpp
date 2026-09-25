#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
long long a[N],sum[N],num[N];
int leftEnd[N],rightEnd[N],length[N],den[N];
int opL[N],opR[N];

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
	cin >> k >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int top = 0;
	for(int i = 1; i <= n; i++){
		top++;
		leftEnd[top] = rightEnd[top] = i;
		length[top] = 1;
		sum[top] = a[i];
		while(top > 1 && lessEqual(sum[top - 1],length[top - 1],sum[top],length[top])){
			sum[top - 1] += sum[top];
			length[top - 1] += length[top];
			rightEnd[top - 1] = rightEnd[top];
			top--;
		}
	}
	for(int i = 1; i <= n; i++){
		num[i] = a[i];
		den[i] = 1;
	}
	int used = 0;
	for(int b = 1; b <= top; b++){
		int l = leftEnd[b],r = rightEnd[b];
		int last = 0;
		for(int i = l; i <= r; i++){
			if(a[i] * length[b] != sum[b]) last = i;
		}
		if(last == 0 || used == k) continue;
		used++;
		opL[used] = l;
		opR[used] = last;
		long long g = gcdValue(sum[b],length[b]);
		for(int i = l; i <= r; i++){
			num[i] = sum[b] / g;
			den[i] = length[b] / g;
		}
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
