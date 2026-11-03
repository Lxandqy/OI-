#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n;
long long a[N],b[N],c[N];

bool check(long long t){
	long long need = 0,help = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] > t){
			need += a[i] - t;
		}else if(t > a[i] + c[i]){
			help += (t - a[i] - c[i]) / b[i];
		}
	}
	return help >= need;
}

int main(){
	freopen("workshop.in","r",stdin);
	freopen("workshop.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	long long l = 0,r = 0;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> c[i];
		r = max(r,a[i]);
	}
	while(l < r){
		long long mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << '\n';
	return 0;
}
