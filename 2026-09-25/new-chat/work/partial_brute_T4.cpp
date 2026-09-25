#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
struct fraction{
	long long p,q;
};
fraction cur[N],best[N];
int n,k,opL[N],opR[N],bestL[N],bestR[N],bestUsed = 100;

long long gcdValue(long long x,long long y){
	while(y){
		long long z = x % y;
		x = y;
		y = z;
	}
	return x;
}

fraction add(fraction a,fraction b){
	long long g = gcdValue(a.q,b.q);
	long long den = a.q / g * b.q;
	long long num = a.p * (den / a.q) + b.p * (den / b.q);
	g = gcdValue(num,den);
	fraction result = {num / g,den / g};
	return result;
}

bool better(int used){
	if(bestUsed == 100) return true;
	for(int i = 1; i <= n; i++){
		long long x = cur[i].p * best[i].q;
		long long y = best[i].p * cur[i].q;
		if(x != y) return x > y;
	}
	if(used != bestUsed) return used < bestUsed;
	for(int i = 1; i <= used; i++){
		if(opL[i] != bestL[i]) return opL[i] < bestL[i];
		if(opR[i] != bestR[i]) return opR[i] < bestR[i];
	}
	return false;
}

void dfs(int used){
	if(better(used)){
		bestUsed = used;
		for(int i = 1; i <= n; i++) best[i] = cur[i];
		for(int i = 1; i <= used; i++){
			bestL[i] = opL[i];
			bestR[i] = opR[i];
		}
	}
	if(used == k) return;
	for(int l = 1; l <= n; l++){
		for(int r = l + 1; r <= n; r++){
			vector<fraction> old(r - l + 1);
			fraction sum = {0,1};
			for(int i = l; i <= r; i++){
				old[i - l] = cur[i];
				sum = add(sum,cur[i]);
			}
			sum.q *= r - l + 1;
			long long g = gcdValue(sum.p,sum.q);
			sum.p /= g;
			sum.q /= g;
			for(int i = l; i <= r; i++) cur[i] = sum;
			opL[used + 1] = l;
			opR[used + 1] = r;
			dfs(used + 1);
			for(int i = l; i <= r; i++) cur[i] = old[i - l];
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> cur[i].p;
		cur[i].q = 1;
	}
	dfs(0);
	cout << bestUsed << '\n';
	for(int i = 1; i <= n; i++){
		if(i > 1) cout << ' ';
		cout << best[i].p << '/' << best[i].q;
	}
	cout << '\n';
	for(int i = 1; i <= bestUsed; i++) cout << bestL[i] << ' ' << bestR[i] << '\n';
	return 0;
}
