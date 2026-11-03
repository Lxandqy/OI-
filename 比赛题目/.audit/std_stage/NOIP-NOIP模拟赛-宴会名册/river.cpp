#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int n,len,x[N];
long long budget,sum,c[N],f[N];

bool check(int d){
	int p = 0;
	long long best = -1;
	f[0] = 0;
	for(int i = 1; i <= n + 1; i++){
		while(p < i && x[i] - x[p] >= d){
			best = max(best,f[p]);
			p++;
		}
		f[i] = -1;
		if(best >= 0) f[i] = best + c[i];
	}
	return sum - f[n + 1] <= budget;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> len >> n >> budget;
	for(int i = 1; i <= n; i++){
		cin >> x[i] >> c[i];
		sum += c[i];
	}
	x[n + 1] = len;
	int l = 1,r = len,ans = 1;
	while(l <= r){
		int mid = l + (r - l) / 2;
		if(check(mid)){
			ans = mid;
			l = mid + 1;
		}else{
			r = mid - 1;
		}
	}
	cout << ans << '\n';
	return 0;
}
