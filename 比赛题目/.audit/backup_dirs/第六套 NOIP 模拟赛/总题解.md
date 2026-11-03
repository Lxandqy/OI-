# NOIP 模拟赛 · 第六套题解

# T1 乘积裁剪（product）

---

长度限制使我们不能直接保留整个非零段，也不能只从两端删除一个负数。例如样例 1 的整个序列乘积为 $8$，却超出了长度上界。需要在所有合法区间中比较真实乘积，再对最终答案取模。

非零乘积一定是 $2^e$ 或 $-2^e$，其中 $e$ 是区间内绝对值为 $2$ 的数的个数。因此可以用“符号、指数”精确比较，不必存下巨大的整数：正数优于零，零优于负数；两个正数取指数更大者，两个负数取指数更小者。

固定左端点并向右延长，逐项维护零、负数和绝对值为 $2$ 的数，可以在 $O(nR)$ 时间内求解，保证完成前四个点。这里大量工作花在长度尚未达到 $L$ 的区间上。预处理负数个数的奇偶前缀 $p_i$、绝对值为 $2$ 的个数前缀 $c_i$，以及零的个数前缀，就能在 $O(1)$ 时间判断一个区间的符号和指数，只枚举长度 $L$ 到 $R$，复杂度变成 $O(n(R-L+1))$，保证完成前八个点。先滑动维护每个长度 $L$ 的区间，再逐步延长，也有相同复杂度。

一般数据中，合法长度仍然太多。固定右端点 $i$，将左端点写成 $j+1$，则长度限制恰好是

$$
\max(0,i-R)\le j\le i-L.
$$

设 $z$ 是不超过 $i$ 的最后一个零的位置，没有零时为 $0$。非零区间还必须满足 $j\ge z$。若 $p_j=p_i$，乘积为正，指数为 $c_i-c_j$；否则乘积为负。于是，在合法切点窗口内，正乘积应选同奇偶类中 $c_j$ 最小的切点，负乘积应选异奇偶类中 $c_j$ 最大的切点。

$c_j$ 随下标不减，所以同一奇偶类中最早的切点就具有最小 $c_j$，最晚的切点就具有最大 $c_j$。这里连按权值维护单调队列都不需要：分奇偶保存切点下标的普通队列即可。

扫描 $i$ 时，新获得长度资格的切点只有 $j=i-L$；若它不小于 $z$，将它加入对应队尾。再从两个队首删去所有小于 $\max(i-R,z)$ 的切点。此后两个队列恰好保存当前所有合法的非零切点。分别用同奇偶队首与异奇偶队尾更新全局最优值。最早切点和最晚切点的指数单调性证明了其余候选不会更优，并列指数任选一个即可。

含零的区间不能从上述队列中得到，须单独考虑。对于 $i\ge L$，以 $i$ 结尾的最长合法区间从 $\max(1,i-R+1)$ 开始；它含零当且仅当 $z\ge\max(1,i-R+1)$。满足时将 $0$ 作为候选。这样正数、负数和零三类互斥且覆盖了所有合法区间；即使所有合法乘积均为负数，也不会误用空区间的乘积 $1$。

每个切点至多入队一次、出队一次，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。最终用最优指数计算 $2^e\bmod(10^9+7)$；负答案输出其相反数的规范余数。代码中的 `signans` 与 `expans` 分别保存全局最优乘积的符号与指数，初始符号 $-2$ 仅表示还没有候选。

## 参考代码

---

```cpp
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
```


# T2 环盘（disk）

---

先直接模拟读取。设整圈的元素和为 $S$。同一位置在下一圈被读取时，累计值恰好增加 $S$。因此，当 $S\le0$ 时，第一圈没有达到阈值，以后也不会达到；当 $S>0$ 时，可以继续模拟，但阈值很大时会反复经过同一圈。

固定起点 $s$，记第一圈读取 $t$ 个数后的累计值为 $b_t$，其中 $1\le t\le n$，并记 $M=\max b_t$。跳过 $k$ 圈后，这一圈的最高累计值是 $kS+M$。如果 $M\ge x$，答案就在第一圈；否则，$S\le0$ 时无解，$S>0$ 时需要先跳过

$$
k=\left\lceil\frac{x-M}{S}\right\rceil
$$

圈。前面各圈的最大值都小于 $x$，所以没有漏掉更早停止的位置。随后只需在一圈中找最小的 $t$，使 $b_t\ge x-kS$，答案为 $kn+t$。逐询问计算这一圈的前缀和即可得到 $O(nq)$ 的做法；与逐步模拟相比，已经消除了阈值大小带来的开销。

将询问按起点分组，每组只计算一次一圈的前缀最大值，再二分第一个达标位置。设不同起点数为 $D$，总时间为 $O(nD+q\log q+q\log n)$，可处理小规模询问与固定起点的大数据。但 $D$ 较大时仍重复建表，需要让所有起点共用预处理。

将原数组复制一遍，设双倍数组的前缀和为 $P_i$，且 $P_0=0$。从 $s$ 开始的一圈对应区间 $[s,s+n-1]$，其中位置 $j$ 对应的累计值为 $P_j-P_{s-1}$。于是

$$
M=\max_{s\le j\le s+n-1}P_j-P_{s-1}.
$$

用线段树维护 $P$ 的区间最大值，便能在 $O(\log n)$ 时间求出 $M$。算出跳过的圈数 $k$ 后，剩下的问题是：在 $[s,s+n-1]$ 中，找最小的 $j$ 满足

$$
P_j\ge P_{s-1}+x-kS.
$$

$P$ 不一定单调，不能直接对它二分。在线段树上查找时，若当前节点与询问区间不相交，或节点最大值小于目标值，就舍弃整段；否则先查左儿子，左边没有答案再查右儿子。每次舍弃的区间都不存在达标位置，先左后右又保证找到的是最早位置。只有区间边界及答案所在的路径需要继续展开，单次查找为 $O(\log n)$。

最终输出 $kn+j-s+1$。预处理为 $O(n)$，总时间复杂度为 $O(n+q\log n)$，空间复杂度为 $O(n)$。当 $S>0$ 时，$S$ 至少为 $1$，且 $M\ge S$，所以有解时答案不超过 $nx\le2\times10^{17}$；前缀和、阈值和答案均使用 `long long`。

上述四步依次保证 $20/40/50/100$ 分：直接模拟覆盖 $1\sim4$；跳圈扫描覆盖 $1\sim8$；按起点复用覆盖 $1\sim10$；共享线段树覆盖全部数据。

## 参考代码

---

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 400010;
const long long INF = (1LL << 60);
int n,q;
long long a[N],pre[N],mx[N * 4];

void build(int p,int l,int r){
    if(l == r){
        mx[p] = pre[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2,l,mid);
    build(p * 2 + 1,mid + 1,r);
    mx[p] = max(mx[p * 2],mx[p * 2 + 1]);
}

long long query(int p,int l,int r,int x,int y){
    if(x <= l && r <= y) return mx[p];
    int mid = (l + r) / 2;
    long long ans = -INF;
    if(x <= mid) ans = max(ans,query(p * 2,l,mid,x,y));
    if(y > mid) ans = max(ans,query(p * 2 + 1,mid + 1,r,x,y));
    return ans;
}

int find_first(int p,int l,int r,int x,int y,long long v){
    if(r < x || l > y || mx[p] < v) return -1;
    if(l == r) return l;
    int mid = (l + r) / 2;
    int ans = find_first(p * 2,l,mid,x,y,v);
    if(ans != -1) return ans;
    return find_first(p * 2 + 1,mid + 1,r,x,y,v);
}

int main(){
    freopen("disk.in","r",stdin);
    freopen("disk.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i + n] = a[i];
    }
    for(int i = 1; i <= 2 * n; i++) pre[i] = pre[i - 1] + a[i];
    build(1,1,2 * n);
    while(q--){
        int s;
        long long x;
        cin >> s >> x;
        long long best = query(1,1,2 * n,s,s + n - 1) - pre[s - 1];
        long long turns = 0;
        if(best < x){
            if(pre[n] <= 0){
                cout << -1 << '\n';
                continue;
            }
            turns = (x - best + pre[n] - 1) / pre[n];
        }
        long long need = pre[s - 1] + x - turns * pre[n];
        int pos = find_first(1,1,2 * n,s,s + n - 1,need);
        cout << turns * n + pos - s + 1 << '\n';
    }
    return 0;
}
```


# T3 约数林（gcdforest）

---

从每个顶点出发遍历整棵树，沿途维护已经经过的点权 gcd 和边容量最小值，即可枚举所有路径。只统计编号较大的终点就不会重复，复杂度为 $O(n^2\log A)$，其中 $A=\max a_i$。主要困难是：同一段路径会被许多起点反复访问，而 gcd 和最小容量又会在扩展路径时一起变化。

## 先把 gcd 拆成约数的贡献

---

固定一个正整数 $d$，一条非空边路径上的所有点权都能被 $d$ 整除，当且仅当它的每条边的两个端点都能被 $d$ 整除。因此，保留这些边后得到一个森林；一对顶点在森林中连通，恰好表示它们原来的路径 gcd 是 $d$ 的倍数。

仅仅把每个约数对应的路径条数相加，会把 gcd 为 $g$ 的路径计算 $\tau(g)$ 次，并没有得到系数 $g$。我们需要给约数设置合适的权重。记 $\varphi(d)$ 为 $1\sim d$ 中与 $d$ 互质的整数个数，有

$$g=\sum_{d\mid g}\varphi(d).$$

这个等式可以把 $1\sim g$ 按它们与 $g$ 的最大公约数分类来证明：最大公约数等于 $g/d$ 的一类，约去 $g/d$ 后，恰好对应 $1\sim d$ 中与 $d$ 互质的 $\varphi(d)$ 个数。所有类别不重不漏地划分了 $g$ 个整数。

于是，一条 gcd 为 $g$、最小容量为 $c$ 的路径，可以在每个 $d\mid g$ 对应的森林中贡献 $\varphi(d)c$。现在只需解决：**对于固定的 $d$，求这个森林中所有连通点对的路径最小容量之和。**

## 按容量降序，统计首次连通的点对

---

先暂时忽略 gcd 限制，考虑一棵边带容量的树。如果一条路径上有容量 $9,7,3$ 的三条边，那么按容量从大到小加入边时，路径两端直到容量 $3$ 的边被加入才首次连通。这一刻的容量正好是路径上的最小容量。

对固定 $d$ 的森林也是一样。把边按容量降序加入并查集。加入一条容量为 $w$ 的边时，设它连接的两个连通块大小分别为 $s,t$。这时新增了恰好 $st$ 对连通顶点，每对的路径包含这条边，而其余边都已经加入、容量至少为 $w$，所以它们的路径最小容量都恰好为 $w$。本次对答案的贡献为

$$\varphi(d)\cdot s\cdot t\cdot w.$$

每对连通顶点只在首次连通时出现一次，因此没有重复或遗漏。容量相同的边可以按任意顺序处理：首次连通的顺序可能不同，但这些步骤的容量相同，贡献不变。

如果对每个 $d$ 都扫描全部边、筛出两端可被 $d$ 整除的边，就得到了 $O(nA\alpha(n)+n\log n)$ 的算法。全局先排序一次即可，不必为每个 $d$ 重新排序；当 $A\le60$ 时已经足够。

所有容量相同时，路径最小容量就是这个共同值。此时将边按端点 gcd 分桶，对每个 $d$ 枚举其倍数桶，以任意顺序合并有效边，统计连通点对数，按 $\varphi(d)$ 加权求和，再乘共同容量。设所有约数森林的边数总和为 $K$，复杂度为 $O(A\log A+K\alpha(n))$，可以处理测试点 $9\sim10$ 的大值域。一般数据还需要同时解决选边与容量顺序。

## 一次排序，把边送到需要它的森林

---

扫描所有边的主要浪费来自：绝大多数边不属于当前 $d$ 的森林。对于边 $(u,v)$，它会被使用，当且仅当

$$d\mid\gcd(a_u,a_v).$$

预处理每个 $1\le g\le A$ 的约数列表 `dv[g]`。把所有边按容量降序排列后，依次处理每条边，把它的编号加入 `dv[gcd(a[u],a[v])]` 中每个约数对应的桶 `b[d]`。由于追加顺序来自同一份降序边表，**每个桶天然已经按容量降序排列**，不需要再排序。

接下来逐个处理桶。首先遍历桶内的全部边，把出现过的端点初始化为单点并查集；重复初始化同一顶点没有影响，但必须在开始合并之前全部完成。再按桶内顺序合并，按上式累加贡献。没有出现在任何边上的孤立顶点不构成不同顶点对，无需初始化或计入答案。处理下一个约数时，只重置它涉及的端点，因此不会为了清空并查集又退回 $O(nA)$。

实现中，`phi[d]` 用筛法求出，`fa` 和 `sz` 分别维护代表元与连通块大小，按大小合并并进行路径压缩。整个过程不需要沿原树递归，树是一条长链也不会改变并查集的深度上界。

令

$$K=\sum_{(u,v)\in E}\tau(\gcd(a_u,a_v)).$$

筛约数列表需要 $O(A\log A)$ 时间与空间；排序需要 $O(n\log n)$ 时间；所有桶一共存放 $K$ 个边编号，初始化与并查集合并共需 $O(K\alpha(n))$ 时间。因此总时间为 $O(A\log A+n\log n+K\alpha(n))$，空间为 $O(A\log A+n+K)$。在 $A\le2\times10^5$ 时，一个数至多有 $160$ 个约数，所以 $K\le160(n-1)$。

每次乘法按顺序取模：先算 $st\bmod M$，再乘 $w$，最后乘 $\varphi(d)$，其中 $M=10^9+7$。这样每次使用 `long long` 的乘法都不会溢出。没有边时没有任何顶点对贡献，答案自然为 $0$。

逐源遍历覆盖测试点 $1\sim4$，保证 $20$ 分；对每个 $d$ 扫描全部边覆盖 $1\sim8$，保证 $40$ 分；先检测容量是否全等，满足时使用同容量算法，否则使用扫描算法，可覆盖 $1\sim10$，累计保证 $50$ 分；完整分桶算法覆盖全部数据，保证 $100$ 分。

## 参考代码

---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
const int mod = 1000000007;
struct node{
	int u,v,w;
}e[N];
int n,mx,a[N],fa[N],sz[N],phi[N];
vector<int> dv[N],b[N];

int gcd(int x,int y){
	while(y){
		int z = x % y;
		x = y;
		y = z;
	}
	return x;
}

int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool cmp(node x,node y){
	return x.w > y.w;
}

int main(){
	freopen("gcdforest.in","r",stdin);
	freopen("gcdforest.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		mx = max(mx,a[i]);
	}
	for(int i = 1; i < n; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	for(int i = 1; i <= mx; i++) phi[i] = i;
	for(int i = 1; i <= mx; i++){
		for(int j = i; j <= mx; j += i) dv[j].push_back(i);
		if(i == 1 || phi[i] != i) continue;
		for(int j = i; j <= mx; j += i){
			phi[j] = phi[j] / i * (i - 1);
		}
	}
	sort(e + 1,e + n,cmp);
	for(int i = 1; i < n; i++){
		int g = gcd(a[e[i].u],a[e[i].v]);
		for(int j = 0; j < (int)dv[g].size(); j++){
			b[dv[g][j]].push_back(i);
		}
	}
	long long ans = 0;
	for(int d = 1; d <= mx; d++){
		// 初始化全部相关端点后，再按容量降序合并。
		for(int i = 0; i < (int)b[d].size(); i++){
			int id = b[d][i];
			fa[e[id].u] = e[id].u;
			fa[e[id].v] = e[id].v;
			sz[e[id].u] = 1;
			sz[e[id].v] = 1;
		}
		for(int i = 0; i < (int)b[d].size(); i++){
			int id = b[d][i];
			int x = find(e[id].u),y = find(e[id].v);
			if(x == y) continue;
			if(sz[x] < sz[y]) swap(x,y);
			long long add = 1LL * sz[x] * sz[y] % mod;
			add = add * e[id].w % mod;
			ans = (ans + add * phi[d]) % mod;
			fa[y] = x;
			sz[x] += sz[y];
		}
	}
	cout << ans << '\n';
	return 0;
}
```


# T4 联保（joint）

---

要求保留的边记为 $F$。如果 $F$ 自身成环，答案就是 $-1$。否则先把 $F$ 中的边加入并查集、计入费用，再对其余边做 Kruskal，就能求出受限的最小生成树。这给出了逐问重新求解的方法；所有询问的边权顺序不变，排序可以只做一次。不过每问仍可能检查全部 $m$ 条边。

先求原图的任意一棵最小生成树 $T$，总权值记为 $W$。关键是：**处理一份要求时，只需要考虑 $T\cup F$。** 取满足要求的最优生成树 $S$，并使它使用的 $T\cup F$ 之外的边尽量少。如果仍有这样的边 $e$，删去 $e$ 将 $S$ 分成两部分。$T$ 上连接 $e$ 两端的路径必然跨过这个割，而且路径上每条边的权值都不超过 $w_e$，否则可以用 $e$ 改善 $T$。取其中一条跨割边 $t$，用 $t$ 替换 $e$，不会增加费用，也不会删去任何必选边，却减少了范围之外的边数，矛盾。

因此，先求一次 $T$，每问只扫描它的 $n-1$ 条边，即可把瓶颈从 $qm$ 降到 $qn$。接下来还要避免反复访问那些与本次要求无关的树边。

把 $F$ 的所有端点标为关键点。连接这些关键点的最小子树之外，所有树边都是 $T\cup F$ 的桥，必须保留。在最小子树内部，再保留关键点和分叉点，把它们之间没有其他保留点的路径压成一条边。

设一条被压缩的路径的最大边权为 $c$。它最多能删去一条边：若删去两条，中间一段及其挂接分支没有必选边端点，便会与其他点断开。若删一条，删除最大边最优；若一条也不删，则比前一种情况多花 $c$。所以可以先从 $W$ 中减去每条压缩路径的最大边权，再将这条路径表示成一条权值为 $c$ 的可选边。选中它表示整条路径保留，不选表示删除其中一条最大边。

此时只需在压缩图中先加入全部必选边，再对这些可选边做 Kruskal。压缩前后的连通关系相同，每条路径的两种选择也恰好对应上述费用，因此小图的最优解就是原问题的最优解。

特别地，如果一条必选边原本就在 $T$ 中，它的两个端点都是关键点，故它必然单独对应一条压缩边。基础费用先减去它的权值，强制加入时再加回来；对应的可选边两端已经连通，不会再选入，因而既不会漏掉这条边，也不会重复计费。

剩下的问题是怎样直接建立这个小图。将关键点按树的深度优先遍历序排序，加入每对相邻关键点的最近公共祖先，再排序、去重。这样就包含全部需要保留的分叉点：一个分叉点的两个相邻有效子树交界处，总有一对相邻关键点，其最近公共祖先恰好是该分叉点。若有 $s$ 个关键点，新增点至多 $s-1$ 个，因此总点数小于 $2s\le4k$。

按遍历序扫描这些点，用栈保存当前祖先链。遇到点 $x$ 时，弹出不是 $x$ 祖先的栈顶，剩余栈顶就是小图中 $x$ 的父亲；连边后把 $x$ 入栈。树上倍增同时维护祖先和对应路径的最大边权，即可求出这些压缩边的权值。每个点只入栈、出栈一次，每次最近公共祖先或路径最大值查询用 $O(\log n)$ 时间。并查集也只重置本次保留的点，不能每问清空整个长度为 $n$ 的数组。

最小生成树及倍增预处理用 $O(m\log m+n\log n)$ 时间。一份含 $k$ 条必选边的要求用 $O(k\log k+k\log n)$ 时间。总时间为 $O(m\log m+n\log n+K\log K+K\log n)$，空间为 $O(m+n\log n+K)$。费用之和需要使用 `long long`。链形树的遍历使用显式栈，避免深度达到 $n$ 时的调用栈限制。

各阶段都有对应的得分范围：枚举 $n-1$ 条边并检查连通性与必选条件，覆盖测试点 $1\sim3$，保证 $15$ 分；逐问排序并强制 Kruskal 覆盖 $1\sim6$，保证 $30$ 分；复用一次排序覆盖 $1\sim9$，保证 $45$ 分；只扫描一棵最小生成树覆盖 $1\sim12$，保证 $60$ 分。上述分数按公开范围计算，压缩后的一般算法覆盖全部数据。

## 参考代码

---

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
const int L = 19;
struct edge{
	int u,v,w;
};
edge e[N];
int n,m,q,fa[N],sz[N],dep[N],dfn[N],f[N][L],mx[N][L];
vector<pair<int,int> > g[N];
bool cmp(edge a,edge b){
	return a.w < b.w;
}
bool cmpdfn(int a,int b){
	return dfn[a] < dfn[b];
}
int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
bool merge(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return false;
	if(sz[x] < sz[y]) swap(x,y);
	fa[y] = x;
	sz[x] += sz[y];
	return true;
}
int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int j = L - 1; j >= 0; j--){
		if(dep[f[x][j]] >= dep[y]) x = f[x][j];
	}
	if(x == y) return x;
	for(int j = L - 1; j >= 0; j--){
		if(f[x][j] != f[y][j]){
			x = f[x][j];
			y = f[y][j];
		}
	}
	return f[x][0];
}
int query(int x,int y){
	int ans = 0;
	for(int j = L - 1; j >= 0; j--){
		if(dep[f[x][j]] >= dep[y]){
			ans = max(ans,mx[x][j]);
			x = f[x][j];
		}
	}
	return ans;
}
int main(){
	freopen("joint.in","r",stdin);
	freopen("joint.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> q;
	vector<edge> a;
	for(int i = 1; i <= m; i++){
		cin >> e[i].u >> e[i].v >> e[i].w;
		a.push_back(e[i]);
	}
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		sz[i] = 1;
	}
	sort(a.begin(),a.end(),cmp);
	long long sum = 0;
	for(int i = 0; i < m; i++){
		int x = a[i].u,y = a[i].v,w = a[i].w;
		if(merge(x,y)){
			sum += w;
			g[x].push_back(make_pair(y,w));
			g[y].push_back(make_pair(x,w));
		}
	}
	vector<int> st;
	st.push_back(1);
	dep[1] = 1;
	int timer = 0;
	while(!st.empty()){
		int x = st.back();
		st.pop_back();
		dfn[x] = ++timer;
		for(int i = 0; i < (int)g[x].size(); i++){
			int y = g[x][i].first,w = g[x][i].second;
			if(y == f[x][0]) continue;
			dep[y] = dep[x] + 1;
			f[y][0] = x;
			mx[y][0] = w;
			for(int j = 1; j < L; j++){
				f[y][j] = f[f[y][j - 1]][j - 1];
				mx[y][j] = max(mx[y][j - 1],mx[f[y][j - 1]][j - 1]);
			}
			st.push_back(y);
		}
	}
	while(q--){
		int k;
		cin >> k;
		vector<int> id(k),v;
		for(int i = 0; i < k; i++){
			cin >> id[i];
			v.push_back(e[id[i]].u);
			v.push_back(e[id[i]].v);
		}
		sort(v.begin(),v.end(),cmpdfn);
		v.erase(unique(v.begin(),v.end()),v.end());
		int s = v.size();
		for(int i = 1; i < s; i++) v.push_back(lca(v[i - 1],v[i]));
		sort(v.begin(),v.end(),cmpdfn);
		v.erase(unique(v.begin(),v.end()),v.end());
		for(int i = 0; i < (int)v.size(); i++){
			fa[v[i]] = v[i];
			sz[v[i]] = 1;
		}
		long long ans = sum;
		a.clear();
		st.clear();
		for(int i = 0; i < (int)v.size(); i++){
			int x = v[i];
			while(!st.empty() && lca(st.back(),x) != st.back()) st.pop_back();
			if(!st.empty()){
				int y = st.back(),w = query(x,y);
				edge b = {x,y,w};
				a.push_back(b);
				ans -= w;
			}
			st.push_back(x);
		}
		bool ok = true;
		for(int i = 0; i < k; i++){
			edge b = e[id[i]];
			if(!merge(b.u,b.v)) ok = false;
			ans += b.w;
		}
		if(!ok){
			cout << -1 << '\n';
			continue;
		}
		sort(a.begin(),a.end(),cmp);
		for(int i = 0; i < (int)a.size(); i++){
			if(merge(a[i].u,a[i].v)) ans += a[i].w;
		}
		cout << ans << '\n';
	}
	return 0;
}
```
