# T1 彩灯（lamp）

---

## 题意

---

给定 $n$ 个闭区间 $[l_i,r_i]$ 和整数 $k,L$，求有多少个大小为 $k$ 的区间集合满足 $\min r-\max l\ge L$，答案对 $998244353$ 取模。

## 每个集合只在“左端点最大”的那盏灯处计数

---

直接枚举集合太多。观察条件 $\min r-\max l\ge L$：一旦确定了集合中左端点最大的那盏灯 $s$，$\max l$ 就固定为 $l_s$，条件变成“集合里每盏灯的右端点都至少是 $l_s+L$”，各盏灯之间不再互相牵制。

为了让每个集合恰好被数一次，把彩灯按 $(l_i,\ \text{编号})$ 从小到大排序，规定集合在其中**排得最靠后**的那盏灯 $s$ 处计数。左端点相同的灯用编号定先后；否则左端点相同的几盏灯都会认为自己是“最大的”，同一个集合被重复计数。

以 $s$ 为最后一盏的集合满足要求，当且仅当：

- $s$ 自己满足 $r_s-l_s\ge L$；
- 另外 $k-1$ 盏灯都排在 $s$ 之前（于是它们的左端点都不超过 $l_s$），并且每盏都满足 $r\ge l_s+L$。

反过来，任何满足要求的集合，取其中排最后的灯作为 $s$，就落在上面的情形里，所以不重不漏。记 $cnt_s$ 为排在 $s$ 之前且 $r\ge l_s+L$ 的灯数，这 $cnt_s$ 盏灯可以任选 $k-1$ 盏，于是

$$
\text{答案}=\sum_{s:\ r_s-l_s\ge L}\binom{cnt_s}{k-1}.
$$

## 求 $cnt_s$：二维数点

---

$cnt_s$ 同时限制“排序位置在 $s$ 之前”和“右端点 $\ge l_s+L$”。按排好的顺序依次处理每盏灯：处理第 $q$ 盏灯 $s$ 之前，树状数组里恰好放着排在它前面的 $q-1$ 盏灯的右端点（右端点事先排序，用排名作下标）。查询其中右端点 $<l_s+L$ 的个数 $x$，则

$$
cnt_s=(q-1)-x .
$$

处理完 $s$ 后再把 $r_s$ 插入树状数组。组合数用阶乘和阶乘逆元 $O(1)$ 计算，总复杂度 $O(n\log n)$，空间 $O(n)$。

细节：

- 条件是 $\ge L$，所以查询的是**严格小于** $l_s+L$ 的右端点个数（代码中用 `lower_bound` 求这个排名）；
- $l_s+L$ 可能达到 $2\times10^9$，要用 `long long`；
- $k=1$ 时 $\binom{cnt}{0}=1$，答案就是长度不小于 $L$ 的灯数。

## 部分分

---

| 条件 | 分值 | 做法 |
|---|---:|---|
| $n\le 20$（测试点 $1\sim3$） | 15 分 | 枚举所有大小为 $k$ 的子集，直接算 $\min r-\max l$，$O(2^n n)$。 |
| $n\le 3000$（测试点 $4\sim7$） | 20 分 | 用上面“在排最后的灯处计数”的式子，对每个 $s$ 直接扫一遍排在它前面的灯求 $cnt_s$，$O(n^2)$。它同样覆盖测试点 $1\sim3$，共 35 分。 |
| 性质 A：$L=0$（测试点 $8\sim10$） | 15 分 | 此时只需数排在 $s$ 前面且 $r\ge l_s$ 的灯。$r<l_s$ 的灯满足 $l\le r<l_s$，一定排在 $s$ 前面，所以 $cnt_s=(q-1)-\#\{\text{全部灯中 } r<l_s\}$，右端点排序后二分即可，$O(n\log n)$。 |
| 性质 B：长度都等于 $d$（测试点 $11\sim13$） | 15 分 | $r\ge l_s+L$ 等价于 $l\ge l_s+L-d$。若 $d<L$ 答案为 $0$；否则满足条件的灯恰好是排序后紧挨在 $s$ 前面的一段，段的左端随 $s$ 单调右移，用双指针维护，$O(n\log n)$（排序）。 |

性质 A 的减法之所以成立，是因为 $L=0$ 时“不满足条件”的灯必然排在前面；$L>0$ 时 $r<l_s+L$ 的灯可能有 $l>l_s$、排在 $s$ 之后，不能再从全部灯里直接减去，这就需要上面的二维数点。

对每个 $s$ 只往前扫“左端点不小于 $l_s+L-\max(r-l)$”的灯，最坏仍是 $O(n^2)$：只要有一盏很长的灯，这个范围就覆盖全部灯。

### 参考代码

```cpp
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
```

# T2 说谎者（liar）

---

## 题意

---

$n$ 个人，每人是诚实者或说谎者。给出 $m$ 句“$i$ 说 $j$ 是说谎者/诚实者”，并要求说谎者不超过 $K$ 人。若存在合法的身份分配，求说谎者人数的最大值，否则输出 $-1$。

## 一句话就是一条“相同/不同”的约束

---

分两种情况看“$i$ 说 $j$ 是说谎者”：若 $i$ 诚实，则 $j$ 确实是说谎者；若 $i$ 说谎，则 $j$ 是诚实者。两种情况下 $i,j$ 的身份都**不同**。同理，“$i$ 说 $j$ 是诚实者”等价于 $i,j$ 身份**相同**。反过来，只要每句话对应的“相同/不同”关系成立，无论说话人是谁，这句话都符合其身份。所以全部约束就是这些关系。

把每句话看作一条无向边，边权 $t$ 表示两端是否不同。对每个连通块任选一人染成颜色 $0$，沿边 BFS：经过权为 $t$ 的边时颜色异或 $t$。若某人被要求染成两种不同的颜色，说明存在一圈关系的异或和为 $1$，陈述矛盾，输出 $-1$；否则染色就给出了块内所有“相同/不同”关系的一组解，而且块内只有“整体翻转”这一种别的解。

于是每个连通块被分成两侧：颜色为 $0$ 的 $a_c$ 人、颜色为 $1$ 的 $b_c$ 人。块内身份由“哪一侧是说谎者”唯一确定，不同块互不影响。于是问题变成：每个连通块从 $a_c,b_c$ 中选一个数，总和不超过 $K$，使总和最大。

## 转化为子集和

---

先让每个块都取较小的一侧，得到最少的说谎者人数 $base=\sum_c\min(a_c,b_c)$。若 $base>K$，无解。

否则，块 $c$ 改取较大一侧会多出 $d_c=|a_c-b_c|$ 人。问题变为：从物品 $d_c$ 中选一个子集，和不超过 $cap=K-base$，使和最大。答案为 $base$ 加上这个最大和。这是只问“能否凑出”的 0/1 背包，直接做是 $O(\text{块数}\cdot K)$，块数和 $K$ 都可达 $10^6$。

## 关键：不同的重量只有 $O(\sqrt n)$ 种

---

每个块的 $d_c\le a_c+b_c$，所以 $\sum_c d_c\le n$。若共有 $t$ 种不同的正重量，它们的和至少是 $1+2+\cdots+t=\frac{t(t+1)}{2}$，因此 $t\le\sqrt{2n}\approx1414$。

物品虽然多达 $10^6$ 个，按重量分组后只有 $O(\sqrt n)$ 组，变成多重背包。重量为 $0$ 的块不影响和，直接跳过。

参考代码对每种重量 $d$ 的 $num_d$ 个物品做二进制拆分：拆成 $1,2,4,\ldots$ 个一捆（最后一捆取余数），任何 $0\sim num_d$ 的个数都能由若干捆拼出；每捆相当于一个重量为 $d\cdot take$ 的物品，做一次 0/1 背包。拆出的捆数为 $\sum_d O(\log num_d)$，每次移位 $O(n/w)$。最后在 $[0,\min(cap,n)]$ 中找最大的能凑出的和。

**关于 bitset。** `bitset<N> dp` 可以看成一个长度为 $N$ 的 `bool` 数组，`dp[s]` 读写第 $s$ 位，但它把每 $64$ 位压进一个整数里，整体运算一次处理 $64$ 位。`dp << x` 得到一个新的 bitset，它的第 $s+x$ 位等于原来的第 $s$ 位（整体向高位平移 $x$ 位）；`|=` 是逐位“或”。所以 `dp |= dp << x` 的效果与下面的普通 0/1 背包循环完全相同，只是快了约 $64$ 倍：

```text
for(int s = n; s >= x; s--){
	if(dp[s - x]) dp[s] = 1;
}
```


不用 bitset 也可以：对每种重量 $d$ 从小到大枚举和 $s$，用 $used_s$ 记录“凑出 $s$ 时这种重量用了几个”。若 $s$ 还不能凑出、$s-d$ 能凑出且 $used_{s-d}<num_d$，则 $s$ 能凑出，令 $used_s=used_{s-d}+1$。处理一种新重量之前已经能凑出的和，$used$ 记为 $0$；之后从小到大第一次凑出 $s$ 时，$used_{s-d}$ 已经是凑出 $s-d$ 所需的最少个数，所以 $used_s$ 也是最少个数，不会因为个数上限误判能凑出的和。每种重量 $O(K)$，总复杂度 $O(n\sqrt n)$。这种写法只用普通数组，但最坏约 $1.4\times10^9$ 次简单操作，实测在最大数据上接近时限，不如 bitset 写法稳妥。

细节：

- 读入量很大，需要关闭同步或使用其他较快的读入。

## 部分分

---

| 条件 | 分值 | 做法 |
|---|---:|---|
| $n\le 20$（测试点 $1\sim3$） | 15 分 | 枚举每个人的身份，共 $2^n$ 种，逐句检查并统计说谎者人数，$O(2^n m)$。 |
| $n\le 5000$，$m\le 10^4$（测试点 $4\sim7$） | 20 分 | 按正文建模后对物品 $d_c$ 做普通 0/1 背包，$O(nK)$。它同样覆盖测试点 $1\sim3$，共 35 分。 |
| 性质 A：$K=n$（测试点 $8\sim10$） | 15 分 | 人数没有限制，每个块直接取较大的一侧，答案为 $\sum_c\max(a_c,b_c)$；矛盾时输出 $-1$。$O(n+m)$。 |
| 性质 B：每个连通块至多 $10$ 人（测试点 $11\sim14$） | 20 分 | 此时 $d_c\le 10$，重量至多 $10$ 种，用正文的 $used$ 计数法逐种做多重背包，$O(10n)$。 |

性质 B 的做法如果对所有出现的重量都执行，再配合“不同重量只有 $O(\sqrt n)$ 种”的结论，就是满分做法。对每个连通块单独做一次 bitset 背包的复杂度是 $O(\text{块数}\cdot n/w)$，块数可达 $5\times10^5$，在 $n=10^6$ 时仍然太慢。

### 参考代码

```cpp
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
```

# T3 关键道路（bridge）

---

## 题意

---

给定无向连通图（可能有重边），关键道路即桥。加一条连接 $u\ne v$ 的新边，求加边后桥数的最小值，以及达到最小值的无序点对 $\{u,v\}$ 个数。

## 加一条边会消去哪些桥

---

求出所有桥，删去桥后每个连通块是一个边双连通分量。把每个分量缩成一个点、桥作为边，得到一棵树，称为**桥树**。记分量 $x$ 的点数为 $sz_x$，原图桥数为 $B$。

在 $u,v$ 之间加边后，桥树上 $u$ 所在分量到 $v$ 所在分量的路径与新边构成环，路径上的每条桥都落在环上，不再是桥；不在这条路径上的桥，删去后两侧仍只能经过它相连（新边的两端在它同一侧），所以仍是桥；原来不是桥的边加边后更不会变成桥。因此加边后桥数为

$$
B-\mathrm{dist}(\mathrm{comp}(u),\mathrm{comp}(v)),
$$

其中 $\mathrm{dist}$ 是桥树上的距离。最小值为 $B-D$，$D$ 为桥树的直径；方案数是桥树上距离等于 $D$ 的分量对按点数加权的个数

$$
\sum_{\{x,y\}:\ \mathrm{dist}(x,y)=D}sz_x\cdot sz_y .
$$

若没有桥（$D=0$），任意一对城市都可以，方案数为 $\frac{n(n-1)}{2}$。

## 求桥：注意重边

---

用 Tarjan 求桥：DFS 时记录 $low_u$ 为从 $u$ 的子树出发、不经过“来时那条边”所能到达的最小 $dfn$。树边 $(u,v)$ 是桥当且仅当 $low_v>dfn_u$。

“不经过来时那条边”必须按**边的编号**判断，而不是跳过父亲结点：两点之间有两条道路时，第二条道路能让 $low_v$ 回到 $dfn_u$，它们都不是桥；若按父亲结点跳过，就会把这样的重边误判为桥。

## 从直径中心计数

---

缩点后在桥树上两次 BFS 求出直径 $D$ 和一条直径路径 $e_1\to e_2$。下面按 $D$ 的奇偶，从直径的中心出发计数。

- **$D$ 为偶数**：中心是路径中点 $c$，两端到 $c$ 的距离都是 $D/2$。任何分量 $v$ 到 $c$ 的距离都不超过 $D/2$：$e_1,e_2$ 位于 $c$ 的不同分支，至少有一个与 $v$ 不在同一分支，$v$ 到它的距离等于 $\mathrm{dist}(v,c)+D/2$，不能超过 $D$。对任意两个分量 $u,v$，设 $z$ 是从 $c$ 到 $u$、到 $v$ 两条路径的分叉点，则

$$
\mathrm{dist}(u,v)=\mathrm{dist}(u,c)+\mathrm{dist}(v,c)-2\,\mathrm{dist}(c,z)\le D,
$$

等号成立当且仅当 $u,v$ 到 $c$ 的距离都是 $D/2$ 且 $z=c$，即两者位于 $c$ 的不同分支。从 $c$ 出发 BFS，把深度为 $D/2$ 的分量按所在分支累加点数，得到各分支的和 $w_1,\ldots,w_t$，记 $S=\sum w_i$，方案数为

$$
\frac{S^2-\sum_i w_i^2}{2}.
$$

- **$D$ 为奇数**：中心是路径中间的边 $(x,y)$，去掉它后桥树分成 $x$ 一侧和 $y$ 一侧，$e_1,e_2$ 分别到 $x,y$ 的距离都是 $\frac{D-1}{2}$。同理，$x$ 一侧的分量到 $x$ 的距离不超过 $\frac{D-1}{2}$（否则它到 $y$ 一侧端点的距离超过 $D$），$y$ 一侧同理。同侧两点的距离不超过 $D-1$；异侧两点 $u,v$ 的距离为 $\mathrm{dist}(u,x)+1+\mathrm{dist}(v,y)$，等于 $D$ 当且仅当两项都取到 $\frac{D-1}{2}$。分别求出两侧这些分量的点数和 $W_x,W_y$，方案数为 $W_x\cdot W_y$。

整个算法 $O(n+m)$。方案数最大约 $4.5\times10^{10}$，需要 `long long`。Tarjan 的递归深度可达 $n$，评测时栈空间与内存限制相同即可。

## 部分分

---

| 条件 | 分值 | 做法 |
|---|---:|---|
| $n\le 50$，$m\le 100$（测试点 $1\sim3$） | 15 分 | 枚举每一对 $u,v$，把新边加入后逐条删边、DFS 判断连通性来数桥，$O(n^2\cdot m(n+m))$。 |
| $n,m\le 3000$（测试点 $4\sim7$） | 20 分 | Tarjan 求桥并缩点，然后从每个分量出发在桥树上 BFS，求出所有分量对的距离，统计距离最大的分量对的点数乘积之和，$O(n+m+C^2)$，$C$ 为分量数。它同样覆盖测试点 $1\sim3$，共 35 分。 |
| 性质 A：$m=n-1$（测试点 $8\sim11$） | 20 分 | 图是树，每条边都是桥，每个点自成一个分量，不需要求桥；直接在原树上用正文的直径中心计数，$O(n)$。 |
| 性质 B：所有桥在一条简单路径上（测试点 $12\sim14$） | 15 分 | 桥树是一条链，直径就是整条链：答案为 $B-(C-1)$ 和两端分量点数之积（没有桥时为 $0$ 和 $\frac{n(n-1)}{2}$）。只需求桥与缩点，$O(n+m)$。 |

先求出所有“离心率等于 $D$”的端点、再两两求距离的做法，端点可能有 $10^5$ 个以上，最坏是 $O(n^2)$；它在性质 B 上端点只有两个，可以通过。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int c,n,m;
int eu[N],ev[N];
int head[N],nxt[2 * N],eid[2 * N],gcnt;     // 原图邻接表（链式前向星），存边的编号
int thead[N],tnxt[2 * N],tto[2 * N],tcnt;   // 桥树（缩点后的树）
int dfn[N],low[N],tim;
bool isBridge[N];
int comp[N],compCnt;
long long sz[N];
int dis[N],pre[N],dep[N],bel[N],q[N];
long long brSum[N];
long long sq;   // sumAtDepth 顺便求出的“各分支和的平方和”
void addEdge(int u,int e){
	nxt[++gcnt] = head[u];
	eid[gcnt] = e;
	head[u] = gcnt;
}
void addTree(int u,int v){
	tnxt[++tcnt] = thead[u];
	tto[tcnt] = v;
	thead[u] = tcnt;
}
// 边 e 的另一个端点
int other(int e,int u){
	if(eu[e] == u) return ev[e];
	return eu[e];
}
// Tarjan 求桥：inE 是走到 u 时经过的边的编号，只跳过这一条边，因此能正确处理重边
void tarjan(int u,int inE){
	dfn[u] = low[u] = ++tim;
	for(int i = head[u]; i != 0; i = nxt[i]){
		int e = eid[i];
		if(e == inE) continue;
		int v = other(e,u);
		if(dfn[v] == 0){
			tarjan(v,e);
			low[u] = min(low[u],low[v]);
			if(low[v] > dfn[u]) isBridge[e] = true;
		}else{
			low[u] = min(low[u],dfn[v]);
		}
	}
}
// 在桥树上从 s 出发 BFS，求距离并记录前驱，返回最远点
int bfs(int s){
	for(int i = 1; i <= compCnt; i++) dis[i] = -1;
	int h = 0,t = 0;
	q[t++] = s;
	dis[s] = 0;
	pre[s] = 0;
	int far = s;
	while(h < t){
		int u = q[h++];
		if(dis[u] > dis[far]) far = u;
		for(int i = thead[u]; i != 0; i = tnxt[i]){
			int v = tto[i];
			if(dis[v] == -1){
				dis[v] = dis[u] + 1;
				pre[v] = u;
				q[t++] = v;
			}
		}
	}
	return far;
}
// 从 s 出发（不经过 block），求与 s 距离恰为 d 的分量大小之和；
// brSum[x] 累加属于 s 的邻居分支 x 的部分，全局变量 sq 记录各分支和的平方和
long long sumAtDepth(int s,int block,int d){
	for(int i = 1; i <= compCnt; i++) dep[i] = -1;
	int h = 0,t = 0;
	q[t++] = s;
	dep[s] = 0;
	bel[s] = 0;
	long long total = 0;
	vector<int> used;
	while(h < t){
		int u = q[h++];
		if(dep[u] == d){
			total += sz[u];
			if(brSum[bel[u]] == 0) used.push_back(bel[u]);
			brSum[bel[u]] += sz[u];
			continue;
		}
		for(int i = thead[u]; i != 0; i = tnxt[i]){
			int v = tto[i];
			if(v == block || dep[v] != -1) continue;
			dep[v] = dep[u] + 1;
			if(u == s) bel[v] = v;
			else bel[v] = bel[u];
			q[t++] = v;
		}
	}
	sq = 0;
	for(int i = 0; i < (int)used.size(); i++){
		sq += brSum[used[i]] * brSum[used[i]];
		brSum[used[i]] = 0;
	}
	return total;
}
int main(){
	freopen("bridge.in","r",stdin);
	freopen("bridge.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		cin >> eu[i] >> ev[i];
		addEdge(eu[i],i);
		addEdge(ev[i],i);
	}
	tarjan(1,0);
	// 不经过桥的连通块就是边双连通分量
	for(int i = 1; i <= n; i++){
		if(comp[i]) continue;
		compCnt++;
		int h = 0,t = 0;
		q[t++] = i;
		comp[i] = compCnt;
		while(h < t){
			int u = q[h++];
			sz[compCnt]++;
			for(int j = head[u]; j != 0; j = nxt[j]){
				int e = eid[j];
				if(isBridge[e]) continue;
				int v = other(e,u);
				if(!comp[v]){
					comp[v] = compCnt;
					q[t++] = v;
				}
			}
		}
	}
	int B = 0;
	for(int e = 1; e <= m; e++){
		if(!isBridge[e]) continue;
		B++;
		addTree(comp[eu[e]],comp[ev[e]]);
		addTree(comp[ev[e]],comp[eu[e]]);
	}
	if(compCnt == 1){
		cout << 0 << ' ' << 1LL * n * (n - 1) / 2 << endl;
		return 0;
	}
	// 桥树直径 D：加的边连接的两个分量在树上距离为 D 时，消去的桥最多
	int a = bfs(1);
	int b = bfs(a);
	int D = dis[b];
	vector<int> path;
	for(int x = b; x != 0; x = pre[x]) path.push_back(x);
	long long ways;
	if(D % 2 == 0){
		// 直径中心是点 mid：两端点到 mid 的距离都是 D/2，且在 mid 的不同分支中
		int mid = path[D / 2];
		long long S = sumAtDepth(mid,0,D / 2);
		ways = (S * S - sq) / 2;
	}else{
		// 直径中心是边 (x,y)：两端点分别在这条边两侧，到 x、y 的距离都是 (D-1)/2
		int x = path[(D - 1) / 2],y = path[(D + 1) / 2];
		long long Wx = sumAtDepth(x,y,(D - 1) / 2);
		long long Wy = sumAtDepth(y,x,(D - 1) / 2);
		ways = Wx * Wy;
	}
	cout << B - D << ' ' << ways << endl;
	return 0;
}
```

# T4 景区（park）

---

## 题意

---

给定一棵 $n$ 个点的树，点权 $a_i$ 可正可负。选一个点集 $S$，使 $S$ 在树上形成的连通块（只走 $S$ 中的点）恰好有 $k$ 个，求 $S$ 的点权和的最大值。

## 先看 $k=1$

---

只要一个连通块时，以 $u$ 为最高点的最优连通块是 $u$ 自己再接上每个“收益为正”的儿子分支：$d_u=a_u+\sum_v\max(0,d_v)$，答案为 $\max_u d_u$。

$k$ 变大后，问题不再是“挑若干个最好的连通块”：两个好的块之间如果只隔一个小负数，把它们连起来可以少用一个块的名额；块不够时又可能要把一个块从中间断开，或者额外开放收益最大的负数点。两个开放的点只要有道路相连就属于同一个块，所以“断开”必须真的关掉一个点。块的数目和每个点是否开放互相牵制，需要把“块数”放进状态。

## 树上背包

---

以 $1$ 为根，对每个点 $u$ 定义

- $f_{u,0}[j]$：在 $u$ 的子树里选点、$u$ 不开放、子树内恰好有 $j$ 个块时的最大收益；
- $f_{u,1}[j]$：$u$ 开放、子树内恰好有 $j$ 个块（$u$ 所在的块也已计入）时的最大收益。

不可能的状态记为 $-\infty$。初始只有 $u$ 一个点：$f_{u,0}[0]=0$，$f_{u,1}[1]=a_u$。然后逐个合并儿子 $v$，设合并前 $u$ 一侧有 $x$ 个块、$v$ 的子树有 $y$ 个块：

- $u$ 不开放：$v$ 子树里的块都与外界隔开，块数相加，$f_{u,0}[x+y]\gets f_{u,0}[x]+\max(f_{v,0}[y],f_{v,1}[y])$；
- $u$ 开放、$v$ 不开放：仍然相加，$f_{u,1}[x+y]\gets f_{u,1}[x]+f_{v,0}[y]$；
- $u$ 和 $v$ 都开放：道路 $(u,v)$ 把 $v$ 所在的块与 $u$ 所在的块连成一个，块数少一个，$f_{u,1}[x+y-1]\gets f_{u,1}[x]+f_{v,1}[y]$。

这三种情况按 $u$、$v$ 是否开放互斥地覆盖了所有选法，而 $v$ 子树内部的块与 $u$ 一侧唯一可能的连接就是道路 $(u,v)$，所以合并是完整的。答案为 $\max(f_{1,0}[k],f_{1,1}[k])$。

块数超过 $k$ 的状态可以直接丢掉：某个子树里已有 $j$ 个块时，之后的合并最多只把它的根所在的块与上方一个已经计数的块合并，总块数不会小于 $j$。

## 复杂度：按子树大小限制循环

---

如果每次合并都让 $x,y$ 从 $0$ 枚举到 $k$，总复杂度是 $O(nk^2)$。注意 $x$ 不会超过 $u$ 一侧已合并的点数，$y$ 不会超过 $v$ 的子树大小，所以只需枚举 $x\le\min(s_u,k)$、$y\le\min(s_v,k)$，其中 $s_u$ 为 $u$ 一侧已合并的点数。

这样总复杂度为 $O(nk)$。把一次合并的代价 $\min(s_u,k)\cdot\min(s_v,k)$ 分三类看：

- 两边都小于 $k$：代价为 $s_u s_v$，可以看作两边各取一个点配成一对，每对点只在它们的最近公共祖先处被配对一次；而一个点参与这种配对时，合并后的大小小于 $2k$，所以它的配对对象少于 $2k$ 个。这一类总共 $O(nk)$。
- 一边小于 $k$、另一边至少为 $k$：代价不超过 $k$ 乘以小的一边的点数；小的一边合并进来后所在部分已经至少有 $k$ 个点，所以每个点至多当一次“小的一边”。这一类总共 $O(nk)$。
- 两边都至少为 $k$：代价 $k^2$；这样的合并每次都把两个各含至少 $k$ 个点、此前互不相交的部分并在一起，至多发生 $n/k$ 次。这一类总共 $O(nk)$。

空间上，参考代码直接开全局数组 `f[N][K][2]`（$K=205$），约 $10^5\times205\times2\times8$ 字节，即约 $328$ MB，在 $512$ MiB 之内。合并儿子时新结果要用到旧的 $f_u$，所以先写进临时数组 `t0`、`t1`，合并完再抄回去。DFS 的递归深度可达 $n$，评测时栈空间与内存限制相同即可。收益之和可达 $10^{14}$，需要 `long long`。

## 部分分

---

| 条件 | 分值 | 做法 |
|---|---:|---|
| $n\le 15$（测试点 $1\sim2$） | 10 分 | 枚举开放的点集，用并查集数块数，$O(2^n n)$。 |
| $n\le 2000$（测试点 $3\sim7$） | 25 分 | 正文的树上背包，但 $x,y$ 都从 $0$ 枚举到 $k$，$O(nk^2)$，约 $2000\times200^2=8\times10^7$。它同样覆盖测试点 $1\sim2$；在 $k=1$ 时只有 $O(n)$，也覆盖测试点 $8\sim9$，共 45 分。 |
| $k=1$（测试点 $8\sim9$） | 10 分 | 正文开头的 $d_u=a_u+\sum\max(0,d_v)$，$O(n)$。 |
| 性质 B：树是一条链（测试点 $10\sim12$） | 15 分 | 变成序列上选恰好 $k$ 段互不相邻的非空子段使和最大。设 $s_0[j],s_1[j]$ 分别表示处理到当前位置、恰好 $j$ 段、当前位置不选或选中时的最大和：$s_0[j]\gets\max(s_0[j],s_1[j])$，$s_1[j]\gets\max(s_1[j],s_0[j-1])+a_i$，$O(nk)$。 |

只对其中一侧按大小限制循环、另一侧总是枚举到 $k$，在链状或很深的树上仍会退化到 $O(nk^2)$，与 $O(nk^2)$ 做法得分相同。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int K = 205;
const long long NEG = -1e18;   // 表示不可能的状态
int c,n,k;
long long a[N];
vector<int> g[N];
int sz[N];
// f[u][j][0]：u 的子树中恰好形成 j 个景区、u 不开放时的最大收益
// f[u][j][1]：u 开放（u 所在的景区已经计入 j）时的最大收益
long long f[N][K][2];
long long t0[K],t1[K];         // 合并一个儿子时的临时结果
void dfs(int u,int fa){
	sz[u] = 1;
	f[u][0][0] = 0;
	f[u][0][1] = NEG;
	f[u][1][0] = NEG;
	f[u][1][1] = a[u];
	for(int i = 0; i < (int)g[u].size(); i++){
		int v = g[u][i];
		if(v == fa) continue;
		dfs(v,u);
		// 只枚举到“已合并的点数”和 k 中较小的那个
		int lu = min(sz[u],k),lv = min(sz[v],k),lim = min(sz[u] + sz[v],k);
		for(int j = 0; j <= lim; j++){
			t0[j] = NEG;
			t1[j] = NEG;
		}
		for(int x = 0; x <= lu; x++){
			for(int y = 0; y <= lv; y++){
				long long best = max(f[v][y][0],f[v][y][1]);
				// u 不开放：v 一侧的景区各自独立
				if(f[u][x][0] != NEG && best != NEG && x + y <= lim){
					t0[x + y] = max(t0[x + y],f[u][x][0] + best);
				}
				if(f[u][x][1] == NEG) continue;
				// u 开放、v 不开放：景区数相加
				if(f[v][y][0] != NEG && x + y <= lim){
					t1[x + y] = max(t1[x + y],f[u][x][1] + f[v][y][0]);
				}
				// u、v 都开放：v 所在的景区与 u 所在的景区连成一个
				if(f[v][y][1] != NEG && x + y - 1 <= lim){
					t1[x + y - 1] = max(t1[x + y - 1],f[u][x][1] + f[v][y][1]);
				}
			}
		}
		for(int j = 0; j <= lim; j++){
			f[u][j][0] = t0[j];
			f[u][j][1] = t1[j];
		}
		sz[u] += sz[v];
	}
}
int main(){
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	cout << max(f[1][k][0],f[1][k][1]) << endl;
	return 0;
}
```
