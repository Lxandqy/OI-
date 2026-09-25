#include<bits/stdc++.h>
using namespace std;

map<long long,pair<long long,long long> > best;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	long long k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		long long r = x * x % n;
		pair<long long,long long> &p = best[r];
		if(x > p.first){
			p.second = p.first;
			p.first = x;
		}else if(x > p.second){
			p.second = x;
		}
	}

	long long ans = 0;
	for(map<long long,pair<long long,long long> >::iterator it = best.begin(); it != best.end(); it++){
		long long r = it->first;
		long long other = (k - r) % k;
		map<long long,pair<long long,long long> >::iterator jt = best.find(other);
		if(jt == best.end()) continue;
		long long x = it->second.first;
		long long y = jt->second.first;
		if(r == other) y = it->second.second;
		if(y > 0) ans = max(ans,x * x + y * y);
	}
	cout << ans << '\n';
	return 0;
}
