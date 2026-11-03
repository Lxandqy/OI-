#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int c,n,m,K;
int head[N],nxt[2 * N],to[2 * N],w[2 * N],tot;   // 邻接表：w 为 1 表示两人身份不同，0 表示相同
int col[N],q[N];         // col[x]：x 的染色（-1 表示未访问）；q 为 BFS 队列
int num[N];              // num[d]：两侧人数之差为 d 的连通块个数
bitset<N> dp;            // dp[s]：多出 s 个说谎者能否凑出
void addEdge(int u,int v,int t){
	nxt[++tot] = head[u];
	to[tot] = v;
	w[tot] = t;
	head[u] = tot;
}
int main(){
	freopen("liar.in","r",stdin);
	freopen("liar.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> m >> K;
	for(int k = 1; k <= m; k++){
		int i,j,t;
		cin >> i >> j >> t;
		// t = 1：i 说 j 是说谎者，两人身份不同；t = 0：两人身份相同
		addEdge(i,j,t);
		addEdge(j,i,t);
	}
	for(int i = 1; i <= n; i++) col[i] = -1;
	long long base = 0;
	// 对每个连通块 BFS 染色，统计两种颜色的人数；颜色冲突说明陈述矛盾
	for(int s = 1; s <= n; s++){
		if(col[s] != -1) continue;
		int h = 0,tl = 0,cnt0 = 0,cnt1 = 0;
		col[s] = 0;
		q[tl++] = s;
		while(h < tl){
			int u = q[h++];
			if(col[u] == 0) cnt0++;
			else cnt1++;
			for(int e = head[u]; e != 0; e = nxt[e]){
				int v = to[e];
				int need = col[u] ^ w[e];
				if(col[v] == -1){
					col[v] = need;
					q[tl++] = v;
				}else if(col[v] != need){
					cout << -1 << endl;
					return 0;
				}
			}
		}
		// 每个连通块只能整体二选一：先取人数少的一侧，多出的 d 个作为背包物品
		base += min(cnt0,cnt1);
		num[abs(cnt0 - cnt1)]++;
	}
	if(base > K){
		cout << -1 << endl;
		return 0;
	}
	// 不同的 d 至多约 sqrt(2n) 种，对每种 d 的个数做二进制拆分，用 bitset 做 0/1 背包
	dp[0] = 1;
	for(int d = 1; d <= n; d++){
		int left = num[d];
		int piece = 1;
		while(left > 0){
			int take = min(piece,left);
			dp |= dp << (d * take);
			left -= take;
			piece *= 2;
		}
	}
	int cap = K - base;
	if(cap > n) cap = n;
	int best = 0;
	for(int s = cap; s >= 0; s--){
		if(dp[s]){
			best = s;
			break;
		}
	}
	cout << base + best << endl;
	return 0;
}
