#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct node{
	int s,a;
}b[N];
int n,far[N];
long long pre[N],suf[N];
bool cmp(node x,node y){
	return x.a > y.a;
}
int main(){
	freopen("visit.in","r",stdin);
	freopen("visit.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> b[i].s;
	for(int i = 1; i <= n; i++) cin >> b[i].a;
	sort(b + 1,b + n + 1,cmp);
	for(int i = 1; i <= n; i++){
		pre[i] = pre[i - 1] + b[i].a;
		far[i] = max(far[i - 1],b[i].s);
	}
	for(int i = n; i >= 1; i--){
		suf[i] = max(suf[i + 1],b[i].a + 2LL * b[i].s);
	}
	for(int k = 1; k <= n; k++){
		long long ans = pre[k] + 2LL * far[k];
		if(k < n) ans = max(ans,pre[k - 1] + suf[k + 1]);
		cout << ans << '\n';
	}
	return 0;
}
