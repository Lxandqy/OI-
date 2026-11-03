#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,k,m,q;
int a[N];
int main(){
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	cin >> n >> k >> m >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	int l = 1,bad = 0;   // bad：区间 [l,r] 中多云夜晚的个数
	for(int r = 1; r <= n; r++){
		if(a[r] > q) bad++;
		// 多云夜晚超过 m 个时，左端点右移
		while(bad > m){
			if(a[l] > q) bad--;
			l++;
		}
		// 以 r 结尾的合法区间，左端点可取 l ~ r-k+1
		if(r - k + 1 >= l) ans += r - k + 1 - l + 1;
	}
	cout << ans << endl;
	return 0;
}
