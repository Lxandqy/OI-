# NOIP 模拟赛总题解

# T1 宴会名册（invite）

---

枚举被邀请者集合后，只需按财富顺序检查每人的排名。关键是最终人数已经固定为 $k$：若朋友 $i$ 是第 $j$ 位被邀请者，那么比他穷的恰有 $j-1$ 人，比他富的恰有 $k-j$ 人，与其他人的具体身份无关。因此选他当且仅当

$$

j-1\le b_i,\qquad k-j\le a_i.

$$

令 $f_{i,j}$ 表示处理完前 $i$ 位朋友、已邀请 $j$ 人的方案数。中间方案始终按最终人数 $k$ 检查已经入选的人。按是否邀请朋友 $i$ 分类：

$$

f_{i,j}=f_{i-1,j}+
\begin{cases}
f_{i-1,j-1},& j\ge1,\ j-1\le b_i,\ k-j\le a_i,\\
0,&\text{其他情况。}
\end{cases}

$$

两类方案互斥且覆盖全部选择；选中第 $i$ 人时，他的最终排名已经确定，以后无需重新检查。初始化 $f_{0,0}=1$，其余为 $0$，按 $i$ 递增计算，答案为 $f_{n,k}$，全部运算取模。

时间复杂度 $O(nk)$，空间复杂度 $O(nk)$。参考代码采用完整二维表；单行相加小于两倍模数，使用 `int` 即可。

**部分分。**
$n\le20$ 时枚举所有人员集合并检查，$O(n2^n)$。
$n\le40$ 时折半枚举：左半从穷到富枚举，已选 $t$ 人时再选一人，就按最终排名 $t+1$ 检查；右半从富到穷枚举，已选 $t$ 人时再选一人，就按最终排名 $k-t$ 检查。分别统计两半选各个人数的合法方案数 $L_t,R_t$，答案为 $\sum_t L_tR_{k-t}$。两半各人的最终排名已确定，组合时无需再检查，时间 $O(2^{\lceil n/2\rceil})$，空间 $O(n)$。
$k\le2$ 时直接枚举单人或人对，$O(n^2)$。
所有 $a_i=b_i=n-1$ 时，每个 $k$ 人集合都合法，答案为 $\binom nk$；可逐项相乘并用快速幂求逆，$O(k\log 998244353)$。

参考代码（C++14）：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5005,mod = 998244353;
int n,k,a,b,f[N][N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	f[0][0] = 1;
	for(int i = 1; i <= n; i++){
		cin >> a >> b;
		for(int j = 0; j <= min(i,k); j++){
			f[i][j] = f[i - 1][j];
			if(j >= 1 && j - 1 <= b && k - j <= a){
				f[i][j] += f[i - 1][j - 1];
				if(f[i][j] >= mod) f[i][j] -= mod;
			}
		}
	}
	cout << f[n][k] << '\n';
	return 0;
}
```

# T2 河道预算（river）

---

先二分最小跳跃距离 $d$。提高 $d$ 只会减少合法方案，因此可行性具有单调性。费用各不相同时，优先保留最靠左的石头可能误删昂贵石头，不能沿用按块数计费的贪心。

令 $C=\sum c_i$。移除费用等于 $C$ 减去保留石头的费用之和，因此判定可以改为求合法保留链的最大权值。加入起点 $x_0=0$ 与终点 $x_{n+1}=L$，令它们的费用均为 $0$。

令 $f_i$ 表示以石头 $i$ 结尾、从起点到达它的合法保留链的最大权值，$f_0=0$，不可达状态记为 $-1$。若 $j$ 是前一块保留的石头，则

$$

f_i=c_i+\max_{0\le j<i,\ x_j\le x_i-d}f_j.

$$

只有可达前驱参与转移。所有合法链都可以删去最后一块石头得到一个这样的前驱，反之任意这样的前驱都能接上 $i$，故转移完整。

$x_i$ 递增时，可用前驱总是一个只会扩大的前缀。用指针 $p$ 依次加入新满足距离条件的前驱，用 `best` 维护已经加入的最大 $f_j$。每个前驱只加入一次，一次判定 $O(n)$。只有到终点的状态 $f_{n+1}$ 才能用于判定；可行当且仅当 $C-f_{n+1}\le B$。

在 $[1,L]$ 内二分，时间复杂度 $O(n\log L)$，空间复杂度 $O(n)$。费用总和及 DP 使用 `long long`；$n=0$ 时答案为 $L$。

**部分分。**
$n\le18$ 时枚举保留集合，检查移除费用和相邻间距。
$n\le1500$ 时直接枚举上式全部前驱，$O(n^2\log L)$。
所有 $c_i=1$ 时退化为最多移走 $\lfloor B\rfloor$ 块石头；二分后从左向右尽早保留石头，末端不足距离时再移走最后一块内部石头，$O(n\log L)$。

参考代码（C++14）：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int n,len,x[N];
long long budget,sum,c[N],f[N];

bool check(int d){
	int p = 0;
	long long best = -1;
	f[0] = 0;
	for(int i = 1; i <= n + 1; i++){
		while(p < i && x[i] - x[p] >= d){
			best = max(best,f[p]);
			p++;
		}
		f[i] = -1;
		if(best >= 0) f[i] = best + c[i];
	}
	return sum - f[n + 1] <= budget;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> len >> n >> budget;
	for(int i = 1; i <= n; i++){
		cin >> x[i] >> c[i];
		sum += c[i];
	}
	x[n + 1] = len;
	int l = 1,r = len,ans = 1;
	while(l <= r){
		int mid = l + (r - l) / 2;
		if(check(mid)){
			ans = mid;
			l = mid + 1;
		}else{
			r = mid - 1;
		}
	}
	cout << ans << '\n';
	return 0;
}
```

# T3 三路同归（trio）

---

固定一个三点集合，将树以 $1$ 为根。一条父子边下方若包含 $q$ 个被选点，则这条边被覆盖当且仅当 $q=1$ 或 $q=2$：此时边两侧都有被选点；若 $q=0$ 或 $3$，三点都在同一侧，无需使用这条边。

据此定义 $f_{u,j}$ 与 $cnt_{u,j}$：在当前已合并的 $u$ 子树中选 $j$ 个点时，最大贡献及达到该贡献的集合数。$j=1,2$ 的贡献包括把这些点连接到 $u$ 的道路；$j=3$ 的贡献只包括三点的最小连通子树，不能附带通向 $u$ 的多余道路。$j=0$ 的贡献为 $0$。

只有 $u$ 自己时，$f_{u,0}=f_{u,1}=0$、$cnt_{u,0}=cnt_{u,1}=1$；状态 $2,3$ 不可达。合并儿子 $v$ 时，枚举原先选 $j$ 个、儿子内选 $q$ 个，要求 $j+q\le3$，候选值为

$$

f_{u,j}+f_{v,q}+[q=1\text{ 或 }q=2]\,w_v.

$$

对应集合数为 $cnt_{u,j}cnt_{v,q}$。值更大则替换，值相同则累加。每个集合按它在两个不相交点集中的交集唯一分解，乘法及并列累加不会重复。

特别地，儿子内已经选齐三点时不加父子边，否则会把无用尾巴算进覆盖长度。合并完毕，$cnt_{1,3}$ 即为答案。由于 $p_i<i$，按 $n,n-1,\ldots,2$ 将当前节点合并到父亲，儿子的后代一定已经处理完。

每条边只枚举常数种状态，时间和空间复杂度均为 $O(n)$。最大覆盖长度至多 $(n-1)10^9$，集合数至多 $\binom n3$，都使用 `long long`；本题不取模。

**部分分。**
$n\le45$ 时枚举三点并沿父指针计算三对距离，覆盖长度为三对距离之和的一半。
$n\le400$ 时从每个点出发遍历树，$O(n^2)$ 预处理两两距离，再枚举三点，时间 $O(n^3)$、空间 $O(n^2)$。
$p_i=i-1$ 时树为一条链，最优集合必须包含两个端点，第三点任取内部点，答案为 $n-2$。
$p_i=1$ 时树为菊花，$n\ge4$ 时选道路长度最大的三片叶子，按第三大长度的并列数量计算组合数；$n=3$ 时只有一个三点集合。

参考代码（C++14）：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
const long long inf = (1LL << 60);
int n,p[N];
long long w[N],f[N][4],cnt[N][4];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 2; i <= n; i++) cin >> p[i] >> w[i];
	for(int i = 1; i <= n; i++){
		f[i][0] = 0;
		f[i][1] = 0;
		cnt[i][0] = 1;
		cnt[i][1] = 1;
		f[i][2] = -inf;
		f[i][3] = -inf;
	}
	// p[i] < i，倒序时儿子的所有后代已经合并完成。
	for(int i = n; i >= 2; i--){
		int u = p[i];
		long long g[4],ways[4] = {0,0,0,0};
		for(int j = 0; j <= 3; j++) g[j] = -inf;
		for(int j = 0; j <= 3; j++){
			if(cnt[u][j] == 0) continue;
			for(int k = 0; j + k <= 3; k++){
				if(cnt[i][k] == 0) continue;
				long long val = f[u][j] + f[i][k];
				if(k == 1 || k == 2) val += w[i];
				long long num = cnt[u][j] * cnt[i][k];
				if(val > g[j + k]){
					g[j + k] = val;
					ways[j + k] = num;
				}else if(val == g[j + k]){
					ways[j + k] += num;
				}
			}
		}
		for(int j = 0; j <= 3; j++){
			f[u][j] = g[j];
			cnt[u][j] = ways[j];
		}
	}
	cout << cnt[1][3] << '\n';
	return 0;
}
```

# T4 道路预选（roads）

---

直接枚举四条边，先强制选择它们；若没有成环，再用 Kruskal 补成生成树，检查总权值是否等于全图的最小生成树权值。边排序一次后，需要 $O(m^5\alpha(n))$ 时间。不同预选重复处理了相同的轻边，可以先将这部分固定下来。

**按权收缩，得到各层的无环条件。**
处理权值 $w$ 前，并查集维护全部权值小于 $w$ 的边构成的连通块。把权为 $w$ 的边的端点换成并查集代表，得到多重图 $H_w$。

任何最小生成树的轻边也必须连通上述每个块。否则，块内有一条轻边连接树的两个轻边连通部分；将它加入树后，环上必有权值至少为 $w$ 的边，用轻边替换该边就能降低费用，产生矛盾。因此收缩后的树仍无环，$H_w$ 中的自环不可能被选中，将其删除。

预选集合可被某棵最小生成树包含，当且仅当它没有被删除的边，且在每个 $H_w$ 内均不成环。必要性如上；充分性是每层的无环边集都可补成该层各连通块的生成树。补完一层后，连通块划分只由全部不超过 $w$ 的边决定，与具体补法无关，因此可以顺次完成 Kruskal。同权边必须先全部查询端点，再统一合并。

**先排除平行边，再扣三角形和四元环。**
设剩余有效边总数为 $U$。在每个 $H_w$ 中，将同端点的平行边合成一类，记重数为 $c$。合法集合每类至多选一条。令 $f_j$ 为从已处理的类中选择 $j$ 条边的方案数，初始化 $f_0=1$，其余为 $0$。加入一类时，按 $j=4,3,2,1$ 更新

$$

f_j\leftarrow f_j+c f_{j-1}.

$$

两项分别对应不选该类、从该类选一条。倒序保证同一类不会重复使用。处理全部类后，$f_4$ 恰好统计没有平行边对的四边集合。

现在每层均为带重数的简单图。四条边若成环，只可能出现三角形或四元环。对三边重数为 $a,b,c$ 的同层三角形，先选环上的具体边，再从其他类任选第四条，需扣除 $abc(U-a-b-c)$。第四条可以来自其他权值组，因此使用全局的 $U$。两个不同三角形至少需要五条不同简单边，不会重复扣除同一四边集合。

对同层四元环，再扣除四边重数的乘积。它的四条边不含三角形，不同四元环也不是同一个四边集合。因此各项互斥且覆盖全部不合法情况。记

$$

T=\sum_{\text{三角形}}abc,\qquad
W=\sum_{\text{三角形}}abc(a+b+c),\qquad
C=\sum_{\text{四元环}}abcd,

$$

则答案为 $f_4-UT+W-C$。这些量在处理各权值组时累计，最后组合。

**把四元环变成两条同端点路径。**
直接枚举四个顶点后有三种成环方式。要减少这四重枚举，可以固定环的最高点 $v$ 及其对点 $w$：一个环恰由两条路径 $v\to u_1\to w$、$v\to u_2\to w$ 组成，只需将终点相同的路径配对。

在每层简单图中，按 $(\text{度数},\text{编号})$ 从小到大定义全序。枚举最高点 $v$，再枚举其较小邻居 $u$，以及 $u$ 的邻居中比 $v$ 小的点 $w$。若这两条边的重数为 $c,d$，路径重数为 $p=cd$。

对当前 $v$，令 $s_w$ 为此前枚举到的所有 $v\to u'\to w$ 路径重数之和。先令 $C\leftarrow C+s_wp$，再令 $s_w\leftarrow s_w+p$。合并平行边后，同一中间点只产生一条到 $w$ 的路径，因此配对时 $u'\ne u$。每个环有唯一最高点和对点，两条路径只在较晚的一条出现时配对一次，故不重不漏。

三角形可在同一循环统计。预先标记 $v$ 的邻居及边重数；若 $vw$ 存在且 $u<w$（按上述全序比较），则三边构成一个三角形，更新 $T,W$。最高点唯一，另两点只按一种顺序枚举，故也恰好统计一次。处理完 $v$ 后只清除本次用过的 $s_w$ 和邻居标记；处理完一个权值组后只清除本组出现的点及邻接表。

**枚举量的上界。**
设某层有 $s$ 条简单边，将边由较小点指向较大点。每点出度为 $O(\sqrt{s})$：度数不超过 $\sqrt{2s}$ 的点直接满足；度数更大的点只能指向同样高度的点，而高度点至多 $\sqrt{2s}$ 个。点 $u$ 的整张邻接表为每个较大邻居扫描一次，因此总扫描量为

$$

\sum_u\deg(u)\operatorname{outdeg}(u)=O(s\sqrt{s}).

$$

各层简单边总数不超过 $m$，总时间 $O(m\log m+m\sqrt m)$，空间 $O(n+m)$。各计数和路径乘积及时取模，两个模内数相乘使用 `long long`；最终减法规范到 $[0,998244353)$。少于四条有效边时，$f_4=0$，公式自然给出零。

**部分分。**
$m\le30$ 时使用开头的强制 Kruskal。$m\le120$ 时先按权收缩，再枚举四条边，在各权值组内用至多八个端点的小并查集判环，时间 $O(m^4+m\log m)$。

每种费用至多出现三次时，不可能形成四元环，计算 $f_4,T,W$ 即可。也可分别枚举每层至多三条边的所有子集，统计选 $0$ 至 $4$ 条且无环的方案数，再用四阶卷积合并各层。两种方法每层都只需常数工作，总时间 $O(m\log m)$；与前一档结合，可覆盖前 $44$ 分。

$n\le90$ 时，直接枚举每层的三顶点和四顶点，累计三角形以及四个顶点的三种四元环。设各层活跃顶点数为 $v_i$，成本为 $O(m\log m+\sum_i v_i^4)$，矩阵空间 $O(n^2)$。每层非孤立连通块的点数至多其成功合并次数的两倍，故 $\sum_i v_i\le2(n-1)$，无需对每个权值枚举原图全部顶点。小边数档的活跃点也少，每权至多三边的档每层至多六个点，因此该阶段可覆盖前 $64$ 分；一般范围再用同端点路径配对消除四顶点枚举。

参考代码（C++14）：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200000 + 10;
const int mod = 998244353;
struct edge{
	int u,v,w;
};
int n,m,fa[N],sz[N],deg[N],mark[N],sum[N];
bool active[N],seen[N];
vector<pair<int,int> > g[N];

int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x,y);
	fa[y] = x;
	sz[x] += sz[y];
}

bool cmp_weight(edge x,edge y){
	return x.w < y.w;
}

bool cmp_pair(edge x,edge y){
	if(x.u != y.u) return x.u < y.u;
	return x.v < y.v;
}

bool lower_rank(int x,int y){
	if(deg[x] != deg[y]) return deg[x] < deg[y];
	return x < y;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	vector<edge> a(m);
	for(int i = 0; i < m; i++) cin >> a[i].u >> a[i].v >> a[i].w;
	sort(a.begin(),a.end(),cmp_weight);
	for(int i = 1; i <= n; i++){
		fa[i] = i;
		sz[i] = 1;
	}
	long long total = 0,f[5] = {1,0,0,0,0};
	long long triangles = 0,weighted = 0,cycles = 0;
	for(int l = 0; l < m; ){
		int r = l;
		while(r < m && a[r].w == a[l].w) r++;
		vector<edge> current;
		vector<int> vertices;
		for(int i = l; i < r; i++){
			int x = find(a[i].u),y = find(a[i].v);
			if(x == y) continue;
			if(x > y) swap(x,y);
			current.push_back({x,y,0});
			total++;
		}
		sort(current.begin(),current.end(),cmp_pair);
		for(int i = 0; i < (int)current.size(); ){
			int j = i + 1;
			while(j < (int)current.size() && current[j].u == current[i].u
				&& current[j].v == current[i].v) j++;
			int x = current[i].u,y = current[i].v,c = j - i;
			for(int k = 4; k >= 1; k--) f[k] = (f[k] + f[k - 1] * c) % mod;
			g[x].push_back(make_pair(y,c));
			g[y].push_back(make_pair(x,c));
			deg[x]++;
			deg[y]++;
			if(!active[x]){
				active[x] = true;
				vertices.push_back(x);
			}
			if(!active[y]){
				active[y] = true;
				vertices.push_back(y);
			}
			i = j;
		}
		for(int i = 0; i < (int)vertices.size(); i++){
			int v = vertices[i];
			vector<int> touched;
			for(int j = 0; j < (int)g[v].size(); j++){
				mark[g[v][j].first] = g[v][j].second;
			}
			for(int j = 0; j < (int)g[v].size(); j++){
				int u = g[v][j].first,c = g[v][j].second;
				if(!lower_rank(u,v)) continue;
				for(int k = 0; k < (int)g[u].size(); k++){
					int w = g[u][k].first,d = g[u][k].second;
					if(!lower_rank(w,v)) continue;
					long long path = 1LL * c * d % mod;
					if(mark[w] && lower_rank(u,w)){
						long long value = path * mark[w] % mod;
						triangles = (triangles + value) % mod;
						weighted = (weighted + value * (c + d + mark[w])) % mod;
					}
					cycles = (cycles + sum[w] * path) % mod;
					sum[w] = (sum[w] + path) % mod;
					if(!seen[w]){
						seen[w] = true;
						touched.push_back(w);
					}
				}
			}
			for(int j = 0; j < (int)touched.size(); j++){
				sum[touched[j]] = 0;
				seen[touched[j]] = false;
			}
			for(int j = 0; j < (int)g[v].size(); j++) mark[g[v][j].first] = 0;
		}
		for(int i = 0; i < (int)vertices.size(); i++){
			int x = vertices[i];
			g[x].clear();
			deg[x] = 0;
			active[x] = false;
		}
		for(int i = l; i < r; i++) join(a[i].u,a[i].v);
		l = r;
	}
	long long answer = (f[4] - total * triangles % mod + weighted - cycles) % mod;
	cout << (answer + mod) % mod << '\n';
	return 0;
}
```
