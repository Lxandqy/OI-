# T4 树与叶子

---

## 题意简化

---

输入 $T\le10$ 棵无根树，每棵 $2\le n\le10^5$。删掉任意一条边后得到两部分，按删边后的度数分别数叶子：度不超过 $1$ 的点都是叶子，孤点也算。求两部分叶子数差的最小绝对值及达到它的边数，每棵树输出一行。

## 问题拆分

---

1. 统计原树叶子总数，并为每条边求一侧原叶子数。
2. 根据删边两端的原度数，修正两侧新增的叶子。
3. 对每条边计算新叶子数差，维护最小值与方案数。

## 部分分（小规模及链形，共 30 分）：逐边断开

---

1. 读入邻接表与原度数，$O(n)$ 时间、空间。
2. 对每条边临时禁止通行，从两端分别 BFS，按删边后的度数统计各部分叶子；每条边 $O(n)$。
3. 若原树最大度不超过 $2$，它是一条链。$n=2$ 时答案为 $(0,1)$；$n=3$ 时为 $(1,2)$；$n\ge4$ 时断开内部边得到两侧各两个叶子，答案为 $(0,n-3)$。判链及公式计算共 $O(n)$。
4. 非链时比较两侧叶子数差，更新最小值与方案数；共 $n-1$ 条边，每条 $O(1)$。

一般树时间 $O(n^2)$、空间 $O(n)$，$n\le1000$ 可行；链形时间 $O(n)$，可覆盖独立的长链测试点。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int edgeU[100005], edgeV[100005], que[100005];
bool seen[100005];
int n, bannedU, bannedV;

int countLeaves(int start){
	for(int i = 1; i <= n; i++){
		seen[i] = false;
	}
	int head = 0, tail = 1, result = 0;
	que[0] = start;
	seen[start] = true;
	while(head < tail){
		int u = que[head++];
		int degree = (int)g[u].size();
		if(u == bannedU || u == bannedV){
			degree--;
		}
		if(degree <= 1){
			result++;
		}
		for(int j = 0; j < (int)g[u].size(); j++){
			int v = g[u][j];
			if((u == bannedU && v == bannedV) ||
				(u == bannedV && v == bannedU)){
				continue;
			}
			if(!seen[v]){
				seen[v] = true;
				que[tail++] = v;
			}
		}
	}
	return result;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			g[i].clear();
		}
		for(int i = 1; i < n; i++){
			cin >> edgeU[i] >> edgeV[i];
			g[edgeU[i]].push_back(edgeV[i]);
			g[edgeV[i]].push_back(edgeU[i]);
		}
		bool chain = true;
		for(int i = 1; i <= n; i++){
			if(g[i].size() > 2){
				chain = false;
			}
		}
		if(chain){
			if(n == 2){
				cout << "0 1\n";
			} else if(n == 3){
				cout << "1 2\n";
			}else{
				cout << 0 << ' ' << n - 3 << '\n';
			}
			continue;
		}
		int ans = n, ways = 0;
		for(int i = 1; i < n; i++){
			bannedU = edgeU[i];
			bannedV = edgeV[i];
			int left = countLeaves(bannedU);
			int right = countLeaves(bannedV);
			int difference = abs(left - right);
			if(difference < ans){
				ans = difference;
				ways = 1;
			} else if(difference == ans){
				ways++;
			}
		}
		cout << ans << ' ' << ways << '\n';
	}
	return 0;
}
```

## 满分做法：从叶向内汇总原叶子

---

公开分档对应：1 点 $n\le100$ 与 2 点 $n\le1000$ 用上面的逐边 BFS；3 点是长链，可用该代码中的链特判，前三点共 30 分。4 点虽保证最优边唯一，但仍需检查候选边，故用本节线性算法；5～10 点一般数据也用本节算法。

1. 读入树并统计原度数，得到原叶子总数；$O(n)$ 时间、空间。
2. 从当前度为 $1$ 的节点入队，向唯一未剥离邻点传递累计原叶子权重；每条边处理一次，$O(n)$。处理边时已知一侧原叶子数，另一侧为总数减去它。
3. 若删边端点原度为 $2$，它在本侧新增为叶子；原度为 $1$ 的点原本已计入，成为孤点仍计一次。对每条边 $O(1)$ 算差与计数。

总时间 $O(n)$、空间 $O(n)$。队列剥离避免长链递归深度，且每条边恰好在一侧被剥离时计一次。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
vector<int> g[N];
int degreeNow[N],degreeOld[N],leaf[N],que[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++){
			g[i].clear();
			degreeNow[i] = 0;
			leaf[i] = 0;
		}
		for(int i = 1; i < n; i++){
			int u,v;
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
			degreeNow[u]++;
			degreeNow[v]++;
		}
		int total = 0,head = 0,tail = 0;
		for(int i = 1; i <= n; i++){
			degreeOld[i] = degreeNow[i];
			if(degreeNow[i] == 1){
				leaf[i] = 1;
				total++;
				que[tail++] = i;
			}
		}
		int ans = n,ways = 0;
		while(head < tail){
			int u = que[head++];
			if(degreeNow[u] != 1) continue;
			int v = 0;
			for(int j = 0; j < (int)g[u].size(); j++){
				int x = g[u][j];
				if(degreeNow[x] > 0){
					v = x;
					break;
				}
			}
			if(v == 0) continue;
			int left = leaf[u] + (degreeOld[u] == 2);
			int right = total - leaf[u] + (degreeOld[v] == 2);
			int delta = abs(left - right);
			if(delta < ans){
				ans = delta;
				ways = 1;
			}else if(delta == ans){
				ways++;
			}
			leaf[v] += leaf[u];
			degreeNow[u] = 0;
			degreeNow[v]--;
			if(degreeNow[v] == 1) que[tail++] = v;
		}
		cout << ans << ' ' << ways << '\n';
	}
	return 0;
}
```

## 知识点总结

---

断边后的结构量可先用原树上的可加权重计数，再只修正断边两端；从叶向内剥离能线性取得每条边一侧的权重。
