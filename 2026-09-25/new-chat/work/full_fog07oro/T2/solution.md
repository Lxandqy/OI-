# T2 环上三点分组

---

## 题意简化

---

输入一张 $n\le2\times10^5$ 的连通简单基环图，恰有 $n$ 条编号边。删去一些边后，每个连通块都要恰有三个点，块内可有环。输出升序删除边编号的字典序最小序列；无解输出 $-1$。边数不作为第一目标，所以可能多删一条低编号环边而得到更小序列。

## 问题拆分

---

1. 确定不在唯一环上的树边必须怎样切，得到每个环点尚未闭合的点数。
2. 在环上把这些点数分成总和为 3 的连通组，并确定要切的环边。
3. 对全部合法删除序列排序并取字典序最小者。

## 20 分做法：枚举删边集合

---

**步骤 1、2。** 用一个二进制计数器遍历全部 $2^n$ 个删边集合。对当前方案把未删边加入并查集，再统计每个连通块的点数；所有非空连通块恰为 3 时方案合法。每个集合需要 $O(n\alpha(n))$ 时间和 $O(n)$ 空间。这里无需先求环，因为直接检查最终图。

**步骤 3。** 合法方案的删除边编号天然按升序收集，与当前最好方案作 $O(n)$ 的字典序比较。总时间 $O(n\alpha(n)2^n)$，空间 $O(n)$；$n\le12$ 很轻松，完整范围的指数规模不可行。代码中的二进制计数器对任意 $n$ 都有定义，没有靠超过阈值直接输出错误值。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int n,u[N],v[N],bit[N],fa[N],sizeD[N],cnt[N],cur[N],best[N],cn,bn = -1;

int findRoot(int x){
	int root = x;
	while(fa[root] != root) root = fa[root];
	while(fa[x] != x){
		int y = fa[x];
		fa[x] = root;
		x = y;
	}
	return root;
}

bool smaller(){
	if(bn == -1) return true;
	int m = min(cn,bn);
	for(int i = 1; i <= m; i++){
		if(cur[i] != best[i]) return cur[i] < best[i];
	}
	return cn < bn;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) cin >> u[i] >> v[i];
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	while(true){
		for(int i = 1; i <= n; i++){
			fa[i] = i;
			sizeD[i] = 1;
			cnt[i] = 0;
		}
		cn = 0;
		for(int i = 1; i <= n; i++){
			if(bit[i]){
				cur[++cn] = i;
			}else{
				int a = findRoot(u[i]),b = findRoot(v[i]);
				if(a != b){
					if(sizeD[a] < sizeD[b]) swap(a,b);
					fa[b] = a;
					sizeD[a] += sizeD[b];
				}
			}
		}
		for(int i = 1; i <= n; i++) cnt[findRoot(i)]++;
		bool good = true;
		for(int i = 1; i <= n; i++){
			if(cnt[i] != 0 && cnt[i] != 3) good = false;
		}
		if(good && smaller()){
			bn = cn;
			for(int i = 1; i <= cn; i++) best[i] = cur[i];
		}
		int p = 1;
		while(p <= n && bit[p] == 1){
			bit[p] = 0;
			p++;
		}
		if(p > n) break;
		bit[p] = 1;
	}
	if(bn == -1){
		cout << -1 << '\n';
	}else{
		cout << bn << '\n';
		for(int i = 1; i <= bn; i++){
			if(i > 1) cout << ' ';
			cout << best[i];
		}
		cout << '\n';
	}
	return 0;
}
```

## 20 分做法：逐条尝试环上的起始切边

---

**步骤 1。** 与满分做法一样，剥去叶子并自底向上计算每个环点附带的未闭合块大小。大小达到 3 时树边必须切断；超过 3 则无解。每个点和边处理常数次，时间、空间均为 $O(n)$。

**步骤 2。** 设环长为 $c$。枚举一条环边作为起始切边，从它的下一环点顺时针累加附带点数；和为 3 就切下一条环边并清零，超过 3 则本次失败。扫描回起始切边时必须恰好清零。这样枚举了所有至少切一条环边的解，时间 $O(c^2)$、额外空间 $O(c)$。环恰有三个点且三个附带大小均为 1 时，另试“不切环边”的方案。

**步骤 3。** 每个合法方案与强制树边合并，按边编号排序后比较删除序列。最多 $c+1$ 个方案，每次排序 $O(n\log n)$，故保守总时间 $O(n+c^2+cn\log n)=O(n^2\log n)$，空间 $O(n)$。$n\le3000$ 可用；大环需要满分做法的三种余数边界。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int head[N],to[2 * N],nxt[2 * N],eid[2 * N],ecnt;
int deg[N],que[N],par[N],pe[N],sz[N];
int cyc[N],ce[N],forced[N],fcnt;
bool alive[N];
int answer[N],acnt,candidate[N],ccnt;

void add(int u,int v,int id){
	ecnt++;
	to[ecnt] = v;
	eid[ecnt] = id;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
	deg[u]++;
}

void consider(){
	sort(candidate + 1,candidate + ccnt + 1);
	if(acnt == -1 || lexicographical_compare(candidate + 1,candidate + ccnt + 1,answer + 1,answer + acnt + 1)){
		acnt = ccnt;
		for(int i = 1; i <= ccnt; i++) answer[i] = candidate[i];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,u,v;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> u >> v;
		add(u,v,i);
		add(v,u,i);
	}
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	for(int i = 1; i <= n; i++){
		alive[i] = true;
		sz[i] = 1;
	}
	int front = 1,back = 0;
	for(int i = 1; i <= n; i++){
		if(deg[i] == 1) que[++back] = i;
	}
	while(front <= back){
		int x = que[front++];
		alive[x] = false;
		for(int e = head[x]; e; e = nxt[e]){
			int y = to[e];
			if(!alive[y]) continue;
			par[x] = y;
			pe[x] = eid[e];
			deg[y]--;
			if(deg[y] == 1) que[++back] = y;
		}
	}
	for(int i = 1; i <= back; i++){
		int x = que[i],y = par[x];
		if(sz[x] > 3){
			cout << -1 << '\n';
			return 0;
		}
		if(sz[x] == 3){
			forced[++fcnt] = pe[x];
		}else{
			sz[y] += sz[x];
			if(sz[y] > 3){
				cout << -1 << '\n';
				return 0;
			}
		}
	}
	int start = 0;
	for(int i = 1; i <= n; i++){
		if(alive[i]){
			start = i;
			break;
		}
	}
	int x = start,last = 0,len = 0;
	do{
		cyc[++len] = x;
		int next = 0,edge = 0;
		for(int e = head[x]; e; e = nxt[e]){
			int y = to[e];
			if(alive[y] && y != last){
				next = y;
				edge = eid[e];
				break;
			}
		}
		ce[len] = edge;
		last = x;
		x = next;
	}while(x != start);
	acnt = -1;
	if(len == 3 && sz[cyc[1]] == 1 && sz[cyc[2]] == 1 && sz[cyc[3]] == 1){
		ccnt = 0;
		for(int i = 1; i <= fcnt; i++) candidate[++ccnt] = forced[i];
		consider();
	}
	for(int cut = 1; cut <= len; cut++){
		ccnt = 0;
		for(int j = 1; j <= fcnt; j++) candidate[++ccnt] = forced[j];
		int sum = 0;
		bool good = true;
		for(int step = 1; step <= len; step++){
			int j = (cut + step - 1) % len + 1;
			sum += sz[cyc[j]];
			if(sum > 3){
				good = false;
				break;
			}
			if(sum == 3){
				candidate[++ccnt] = ce[j];
				sum = 0;
			}
		}
		if(good && sum == 0) consider();
	}
	if(acnt == -1){
		cout << -1 << '\n';
	}else{
		cout << acnt << '\n';
		for(int i = 1; i <= acnt; i++){
			if(i > 1) cout << ' ';
			cout << answer[i];
		}
		cout << '\n';
	}
	return 0;
}
```

## 满分做法：剥叶子与三种环边界

---

**步骤 1。** 反复把度数为 1 的点从图上剥去，最后留下唯一的环。记录每个剥掉的点当时唯一还未剥掉的父点，再按剥除顺序自底向上处理。令 `sz[u]` 为向父点延伸、尚未闭合的块的点数，初始为 1。若 `sz[u]=3`，该块只能在父边处切断；若为 1 或 2，就把它加给父点；一旦超过 3 就无解。所有树边切法因此是强制的。队列剥除与累加各扫描边常数次，合计 $O(n)$ 时间、$O(n)$ 空间。

**步骤 2。** 按环的顺序列出环点，其 `sz` 值均在 1 到 3。记沿环的前缀点数为 $P_i$。任何两条相邻切边之间必须恰好有三个点，因此它们对应的 $P_i\bmod3$ 相同。环上可能的切边集合至多三种：对每个余数 $r=0,1,2$，把所有满足 $P_i\equiv r\pmod3$ 的边作为边界，然后逐组核查点数是否为 3。环长为 3、三个环点的 `sz` 都为 1 时，还有保留整个三点环、不切任何环边的方案。环长遍历和三次核查均为 $O(n)$。

**步骤 3。** 每种合法环切法与强制树边合并，按边编号排序后比较序列。最多四种方案，排序总计 $O(n\log n)$，辅助数组 $O(n)$。所有树边选择被步骤 1 强制，所有环边界被步骤 2 穷尽，所以比较得到的就是全局字典序最小答案；不需要特殊判题。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int head[N],to[2 * N],nxt[2 * N],eid[2 * N],ecnt;
int deg[N],que[N],par[N],pe[N],sz[N];
int cyc[N],ce[N],residue[N],forced[N],fcnt;
bool alive[N],mark[N];
int answer[N],acnt,candidate[N],ccnt;

void add(int u,int v,int id){
	ecnt++;
	to[ecnt] = v;
	eid[ecnt] = id;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
	deg[u]++;
}

void consider(){
	sort(candidate + 1,candidate + ccnt + 1);
	if(acnt == -1 || lexicographical_compare(candidate + 1,candidate + ccnt + 1,answer + 1,answer + acnt + 1)){
		acnt = ccnt;
		for(int i = 1; i <= ccnt; i++) answer[i] = candidate[i];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,u,v;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> u >> v;
		add(u,v,i);
		add(v,u,i);
	}
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	for(int i = 1; i <= n; i++){
		alive[i] = true;
		sz[i] = 1;
	}
	int front = 1,back = 0;
	for(int i = 1; i <= n; i++){
		if(deg[i] == 1) que[++back] = i;
	}
	while(front <= back){
		int x = que[front++];
		alive[x] = false;
		for(int e = head[x]; e; e = nxt[e]){
			int y = to[e];
			if(!alive[y]) continue;
			par[x] = y;
			pe[x] = eid[e];
			deg[y]--;
			if(deg[y] == 1) que[++back] = y;
		}
	}
	for(int i = 1; i <= back; i++){
		int x = que[i],y = par[x];
		if(sz[x] > 3){
			cout << -1 << '\n';
			return 0;
		}
		if(sz[x] == 3){
			forced[++fcnt] = pe[x];
		}else{
			sz[y] += sz[x];
			if(sz[y] > 3){
				cout << -1 << '\n';
				return 0;
			}
		}
	}
	int start = 0;
	for(int i = 1; i <= n; i++){
		if(alive[i]){
			start = i;
			break;
		}
	}
	int x = start,last = 0,len = 0;
	do{
		cyc[++len] = x;
		int next = 0,edge = 0;
		for(int e = head[x]; e; e = nxt[e]){
			int y = to[e];
			if(alive[y] && y != last){
				next = y;
				edge = eid[e];
				break;
			}
		}
		ce[len] = edge;
		last = x;
		x = next;
	}while(x != start);
	acnt = -1;
	if(len == 3 && sz[cyc[1]] == 1 && sz[cyc[2]] == 1 && sz[cyc[3]] == 1){
		ccnt = 0;
		for(int i = 1; i <= fcnt; i++) candidate[++ccnt] = forced[i];
		consider();
	}
	int prefix = 0;
	for(int i = 1; i <= len; i++){
		prefix += sz[cyc[i]];
		residue[i] = prefix % 3;
	}
	for(int r = 0; r < 3; r++){
		int first = 0;
		for(int i = 1; i <= len; i++){
			mark[i] = residue[i] == r;
			if(mark[i] && first == 0) first = i;
		}
		if(first == 0) continue;
		bool good = true;
		int sum = 0,i = first;
		do{
			i = i % len + 1;
			sum += sz[cyc[i]];
			if(mark[i]){
				if(sum != 3) good = false;
				sum = 0;
			}
		}while(i != first);
		if(!good) continue;
		ccnt = 0;
		for(int j = 1; j <= fcnt; j++) candidate[++ccnt] = forced[j];
		for(int j = 1; j <= len; j++){
			if(mark[j]) candidate[++ccnt] = ce[j];
		}
		consider();
	}
	if(acnt == -1){
		cout << -1 << '\n';
	}else{
		cout << acnt << '\n';
		for(int i = 1; i <= acnt; i++){
			if(i > 1) cout << ' ';
			cout << answer[i];
		}
		cout << '\n';
	}
	return 0;
}
```

## 知识点总结

---

基环图先剥叶子，把挂树压成环点权值。目标块大小固定为 3 时，树边由剩余块大小强制决定；环上的切边只剩三种前缀和余数，另检查三点环整体保留的情况。
