#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
const int mod = 1000000007;
int n,l,r,a[N],p[N],c[N],q[2][N],h[2],t[2];
int signans = -2,expans;
void update(int s,int e){
	if(s > signans || (s == signans && s == 1 && e > expans) ||
		(s == signans && s == -1 && e < expans)){
		signans = s;
		expans = e;
	}
}
int main(){
	freopen("product.in","r",stdin);
	freopen("product.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> l >> r;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		p[i] = p[i - 1] ^ (a[i] < 0);
		c[i] = c[i - 1] + (abs(a[i]) == 2);
	}
	int zero = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] == 0) zero = i;
		if(i < l) continue;
		int j = i - l;
		if(j >= zero) q[p[j]][t[p[j]]++] = j;
		int left = max(i - r,zero);
		for(int s = 0; s < 2; s++){
			while(h[s] < t[s] && q[s][h[s]] < left) h[s]++;
		}
		int s = p[i];
		if(h[s] < t[s]) update(1,c[i] - c[q[s][h[s]]]);
		s ^= 1;
		if(h[s] < t[s]) update(-1,c[i] - c[q[s][t[s] - 1]]);
		if(zero >= max(1,i - r + 1)) update(0,0);
	}
	long long ans = 1;
	for(int i = 1; i <= expans; i++) ans = ans * 2 % mod;
	if(signans == 0) ans = 0;
	if(signans == -1) ans = mod - ans;
	cout << ans << '\n';
	return 0;
}
