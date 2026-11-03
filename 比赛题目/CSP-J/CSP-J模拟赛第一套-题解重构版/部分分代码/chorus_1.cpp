// 部分分 1
/*
T4 chorus; enumerate nonempty sets of block starts. Valid for n <= 10.
Guaranteed: points 1-2 (10). Time O(2^n*n*log n); space O(n).
*/
#include<bits/stdc++.h>
using namespace std;
// 枚举环上哪些位置是一段的开头
int n,L;
long long a[30];
long long segCost(int st,int len){
	vector<long long> v;
	for(int t = 0; t < len; t++) v.push_back(a[(st + t) % n]);
	sort(v.begin(),v.end());
	long long mid = v[(len - 1) / 2],s = 0;
	for(int t = 0; t < len; t++) s += abs(v[t] - mid);
	return s;
}
int main(){
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
	cin >> n >> L;
	for(int i = 0; i < n; i++) cin >> a[i];
	long long ans = -1;
	for(int mask = 1; mask < (1 << n); mask++){
		vector<int> st;
		for(int i = 0; i < n; i++){
			if((mask >> i) & 1) st.push_back(i);
		}
		int c = st.size();
		bool ok = true;
		long long tot = 0;
		for(int j = 0; j < c; j++){
			int len;
			if(c == 1) len = n;
			else len = (st[(j + 1) % c] - st[j] + n) % n;
			if(len < L){
				ok = false;
				break;
			}
			tot += segCost(st[j],len);
		}
		if(ok && (ans == -1 || tot < ans)) ans = tot;
	}
	cout << ans << endl;
	return 0;
}
