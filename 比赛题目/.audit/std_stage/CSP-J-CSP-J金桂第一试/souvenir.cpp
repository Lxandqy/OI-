#include<bits/stdc++.h>
using namespace std;

const int N = 30000 + 10;
int n,w,a[N];

int main(){
	freopen("souvenir.in","r",stdin);
	freopen("souvenir.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> w >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1,a + n + 1);
	int l = 1,r = n,ans = 0;
	while(l <= r){
		if(l < r && a[l] + a[r] <= w){
			l++;
			r--;
		}else{
			r--;
		}
		ans++;
	}
	cout << ans << '\n';
	return 0;
}
