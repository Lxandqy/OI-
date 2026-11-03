#include<bits/stdc++.h>
using namespace std;

const int N = 1000 + 10;
int n;
long long k,a[N];

bool possible(long long target){
	for(int l = 1; l <= n; l++){
		long long need = target;
		long long cost = 0;
		bool ok = true;
		for(int i = l; i <= n; i++){
			if(a[i] >= need) break;
			if(i == n){
				ok = false;
				break;
			}
			cost += need - a[i];
			if(cost > k) break;
			need--;
		}
		if(ok && cost <= k) return true;
	}
	return false;
}

int main(){
	freopen("growmax.in","r",stdin);
	freopen("growmax.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		cin >> n >> k;
		long long hi = 0;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			hi = max(hi,a[i]);
		}
		long long low = hi;
		hi += k + 1;
		while(low + 1 < hi){
			long long mid = (low + hi) / 2;
			if(possible(mid)) low = mid;
			else hi = mid;
		}
		cout << low << '\n';
	}
	return 0;
}
