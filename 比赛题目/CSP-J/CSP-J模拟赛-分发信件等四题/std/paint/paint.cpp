#include<bits/stdc++.h>
using namespace std;

const int N = 5010;
int n,a[N];

int dfs(int l,int r,int h){
	if(l > r) return 0;
	int p = l;
	for(int i = l + 1; i <= r; i++){
		if(a[i] < a[p]) p = i;
	}
	int ans = a[p] - h;
	ans += dfs(l,p - 1,a[p]);
	ans += dfs(p + 1,r,a[p]);
	return min(r - l + 1,ans);
}

int main(){
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	cout << dfs(1,n,0) << '\n';
	return 0;
}
