#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 50;
const long long INF = 4e18;
int n,L;
long long a[N];
// cost[i][t]：从位置 i 开始、长度为 t 的一段全部改成同一个数的最小代价（t 在 L ~ 2L-1 之间）
long long cost[N][20];
long long b[25];
long long f[N];
int main(){
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
	cin >> n >> L;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i + n] = a[i];   // 复制一份，处理环
	}
	int maxT = 2 * L - 1;
	int maxS = min(maxT - 1,n - 1);   // 环上第一段的起点只需试 1 ~ maxS+1
	for(int i = 1; i <= maxS + n; i++){
		int m = 0;
		for(int t = 1; t <= maxT && i + t - 1 <= 2 * n; t++){
			// 把 a[i+t-1] 插入有序数组 b[1..m]
			long long x = a[i + t - 1];
			int p = ++m;
			while(p > 1 && b[p - 1] > x){
				b[p] = b[p - 1];
				p--;
			}
			b[p] = x;
			if(t >= L){
				long long mid = b[(t + 1) / 2],s = 0;   // 改成中位数代价最小
				for(int j = 1; j <= t; j++) s += abs(b[j] - mid);
				cost[i][t] = s;
			}
		}
	}
	long long ans = INF;
	for(int s = 0; s <= maxS; s++){
		// 从位置 s+1 起把环剪开，f[j]：前 j 个数分好段的最小代价
		f[0] = 0;
		for(int j = 1; j <= n; j++){
			f[j] = INF;
			for(int t = L; t <= maxT && t <= j; t++){
				if(f[j - t] == INF) continue;
				long long v = f[j - t] + cost[s + j - t + 1][t];
				if(v < f[j]) f[j] = v;
			}
		}
		if(f[n] < ans) ans = f[n];
	}
	cout << ans << endl;
	return 0;
}
