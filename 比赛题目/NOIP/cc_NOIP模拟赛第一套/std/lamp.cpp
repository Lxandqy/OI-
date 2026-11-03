#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
const long long MOD = 998244353;
int c,n,k;
long long L;
long long l[N],r[N],b[N];
int id[N],t[N];
long long fac[N],inv[N];
bool cmp(int x,int y){
	if(l[x] != l[y]) return l[x] < l[y];
	return x < y;
}
long long power(long long a,long long e){
	long long res = 1;
	a %= MOD;
	while(e > 0){
		if(e & 1) res = res * a % MOD;
		a = a * a % MOD;
		e >>= 1;
	}
	return res;
}
long long C(int a,int bb){
	if(bb < 0 || bb > a) return 0;
	return fac[a] * inv[bb] % MOD * inv[a - bb] % MOD;
}
// 树状数组：按右端点排名统计已加入的线段个数
void add(int p){
	for(; p <= n; p += p & -p) t[p]++;
}
int ask(int p){
	int res = 0;
	for(; p > 0; p -= p & -p) res += t[p];
	return res;
}
int main(){
	freopen("lamp.in","r",stdin);
	freopen("lamp.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> k >> L;
	for(int i = 1; i <= n; i++){
		cin >> l[i] >> r[i];
		id[i] = i;
		b[i] = r[i];
	}
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	inv[n] = power(fac[n],MOD - 2);
	for(int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i % MOD;
	sort(b + 1,b + n + 1);
	sort(id + 1,id + n + 1,cmp);
	long long ans = 0;
	// 按 (l, 编号) 排序后依次处理：每个方案归到其中排在最后的线段 s 上，
	// 其余 k-1 条从 s 之前、右端点不小于 l_s + L 的线段中选
	for(int q = 1; q <= n; q++){
		int s = id[q];
		if(r[s] - l[s] >= L){
			long long need = l[s] + L;
			int less = lower_bound(b + 1,b + n + 1,need) - b - 1;
			int cnt = (q - 1) - ask(less);
			ans = (ans + C(cnt,k - 1)) % MOD;
		}
		int p = lower_bound(b + 1,b + n + 1,r[s]) - b;
		add(p);
	}
	cout << ans << endl;
	return 0;
}
