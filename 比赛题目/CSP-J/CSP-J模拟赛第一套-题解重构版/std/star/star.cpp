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
	int r = 0,bad = 0;   // bad：窗口 [l,r] 中的坏位置数
	for(int l = 1; l <= n; l++){
		while(r < n && bad + (a[r + 1] > q) <= m){
			r++;
			if(a[r] > q) bad++;
		}
		if(r - l + 1 >= k) ans += r - l - k + 2;
		if(l <= r){
			if(a[l] > q) bad--;
		}else{
			r = l;   // 当前窗口为空，下一轮从位置 l+1 开始
		}
	}
	cout << ans << endl;
	return 0;
}
