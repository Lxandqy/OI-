#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int N = 18;
const int M = 1 << N;
int n,k,m;
int force0[30],force1[30];
int need0[30][N + 1],need1[30][N + 1];
int f[M],g[M];
// 固定第 b 位，检查掩码 s 是否满足这一位的所有记录。
bool valid(int b,int s){
	if((s & force0[b]) != 0) return false;
	if((s & force1[b]) != force1[b]) return false;
	for(int r = 1; r <= n; r++){
		if(need0[b][r] != 0){
			int l = need0[b][r];
			int mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
			if((s & mask) == mask) return false;
		}
		if(need1[b][r] != 0){
			int l = need1[b][r];
			int mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
			if((s & mask) == 0) return false;
		}
	}
	return true;
}
int main(){
	freopen("bits.in","r",stdin);
	freopen("bits.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k >> m;
	for(int j = 1; j <= m; j++){
		char op;
		int l,r,x;
		cin >> op >> l >> r >> x;
		int mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
		for(int b = 0; b < k; b++){
			int v = (x >> b) & 1;
			if(op == 'A'){
				if(v == 1) force1[b] |= mask;
				else need0[b][r] = max(need0[b][r],l);
			}else{
				if(v == 0) force0[b] |= mask;
				else need1[b][r] = max(need1[b][r],l);
			}
		}
	}
	int all = (1 << n) - 1;
	// 尚未填写任何位时，把前一位视为全 0，空方案只有一种。
	f[0] = 1;
	for(int b = 0; b < k; b++){
		for(int s = 0; s <= all; s++) g[s] = f[s];
		// 逐个位置累加；完成后 g[s] 是所有 t 属于 s 的 f[t] 之和。
		for(int i = 0; i < n; i++){
			for(int s = 0; s <= all; s++){
				if((s & (1 << i)) != 0){
					g[s] += g[s ^ (1 << i)];
					if(g[s] >= MOD) g[s] -= MOD;
				}
			}
		}
		for(int s = 0; s <= all; s++){
			if(valid(b,s)) f[s] = g[all ^ s];
			else f[s] = 0;
		}
	}
	int ans = 0;
	for(int s = 0; s <= all; s++){
		ans += f[s];
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << '\n';
	return 0;
}
