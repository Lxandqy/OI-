# 题解 / std 差异

## CSP-J / CSP-J模拟赛第一套 / star
最接近代码块相似度：90.44%

```diff
--- std
+++ solution-block
@@ -9,15 +9,15 @@
 	cin >> n >> k >> m >> q;
 	for(int i = 1; i <= n; i++) cin >> a[i];
 	long long ans = 0;
-	int l = 1,bad = 0;   // bad������ [l,r] �ж���ҹ���ĸ���
+	int l = 1,bad = 0;   // bad：区间 [l,r] 中多云夜晚的个数
 	for(int r = 1; r <= n; r++){
 		if(a[r] > q) bad++;
-		// ����ҹ������ m ��ʱ����˵�����
+		// 多云夜晚超过 m 个时，左端点右移
 		while(bad > m){
 			if(a[l] > q) bad--;
 			l++;
 		}
-		// �� r ��β�ĺϷ����䣬��˵��ȡ l ~ r-k+1
+		// 以 r 结尾的合法区间，左端点可取 l ~ r-k+1
 		if(r - k + 1 >= l) ans += r - k + 1 - l + 1;
 	}
 	cout << ans << endl;
```

## CSP-J / CSP-J模拟赛第一套 / slime
最接近代码块相似度：87.10%

```diff
--- std
+++ solution-block
@@ -8,19 +8,19 @@
 	cin >> T;
 	while(T--){
 		cin >> n >> a >> b;
-		// s Ϊ n ������ƽ������s * s <= n < (s + 1) * (s + 1)
+		// s 为 n 的整数平方根：s * s <= n < (s + 1) * (s + 1)
 		long long s = (long long)sqrt((double)n);
 		while(s * s > n) s--;
 		while((s + 1) * (s + 1) <= n) s++;
 		long long ans = -1;
-		// ������ y ֻʷ��ķ��ÿֻ��СΪ x����Ҫ x * y >= n������ a(x-1) + b(y-1)
-		// ���һ��x <= s + 1��ö�� x��y ȡ��С�� ceil(n / x)
+		// 最终有 y 只史莱姆、每只大小为 x，需要 x * y >= n，花费 a(x-1) + b(y-1)
+		// 情况一：x <= s + 1，枚举 x，y 取最小的 ceil(n / x)
 		for(long long x = 1; x <= s + 1; x++){
 			long long y = (n + x - 1) / x;
 			long long cost = a * (x - 1) + b * (y - 1);
 			if(ans == -1 || cost < ans) ans = cost;
 		}
-		// �������x > s + 1����ʱ y <= s + 1��ö�� y��x ȡ��С�� ceil(n / y)
+		// 情况二：x > s + 1，此时 y <= s + 1，枚举 y，x 取最小的 ceil(n / y)
 		for(long long y = 1; y <= s + 1; y++){
 			long long x = (n + y - 1) / y;
 			long long cost = a * (x - 1) + b * (y - 1);
```

## CSP-J / CSP-J模拟赛第一套 / melody
最接近代码块相似度：86.70%

```diff
--- std
+++ solution-block
@@ -4,7 +4,7 @@
 const int K = 25;
 int n,k;
 int a[N];
-// f[i][j]�������� i �����������������ε����һ�����������ɾ�� j ������ʱ�������ε���󳤶�
+// f[i][j]：保留第 i 个音符、它是上升段的最后一个，段内最多删除 j 个音符时，上升段的最大长度
 int f[N][K];
 int main(){
 	freopen("melody.in","r",stdin);
@@ -15,7 +15,7 @@
 	for(int i = 1; i <= n; i++){
 		for(int j = 0; j <= k; j++){
 			f[i][j] = 1;
-			// �������� i ��ǰһ�������������� p���м�ɾ�� g = i - p - 1 ��
+			// 上升段中 i 的前一个保留的音符是 p，中间删掉 g = i - p - 1 个
 			for(int g = 0; g <= j; g++){
 				int p = i - 1 - g;
 				if(p < 1) break;
```

## CSP-J / CSP-J模拟赛第一套 / chorus
最接近代码块相似度：89.18%

```diff
--- std
+++ solution-block
@@ -4,7 +4,7 @@
 const long long INF = 4e18;
 int n,L;
 long long a[N];
-// cost[i][t]����λ�� i ��ʼ������Ϊ t ��һ��ȫ���ĳ�ͬһ��������С���ۣ�t �� L ~ 2L-1 ֮�䣩
+// cost[i][t]：从位置 i 开始、长度为 t 的一段全部改成同一个数的最小代价（t 在 L ~ 2L-1 之间）
 long long cost[N][20];
 long long b[25];
 long long f[N];
@@ -14,14 +14,14 @@
 	cin >> n >> L;
 	for(int i = 1; i <= n; i++){
 		cin >> a[i];
-		a[i + n] = a[i];   // ����һ�ݣ�������
+		a[i + n] = a[i];   // 复制一份，处理环
 	}
 	int maxT = 2 * L - 1;
-	int maxS = min(maxT - 1,n - 1);   // ���ϵ�һ�ε����ֻ���� 1 ~ maxS+1
+	int maxS = min(maxT - 1,n - 1);   // 环上第一段的起点只需试 1 ~ maxS+1
 	for(int i = 1; i <= maxS + n; i++){
 		int m = 0;
 		for(int t = 1; t <= maxT && i + t - 1 <= 2 * n; t++){
-			// �� a[i+t-1] ������������ b[1..m]
+			// 把 a[i+t-1] 插入有序数组 b[1..m]
 			long long x = a[i + t - 1];
 			int p = ++m;
 			while(p > 1 && b[p - 1] > x){
@@ -30,7 +30,7 @@
 			}
 			b[p] = x;
 			if(t >= L){
-				long long mid = b[(t + 1) / 2],s = 0;   // �ĳ���λ��������С
+				long long mid = b[(t + 1) / 2],s = 0;   // 改成中位数代价最小
 				for(int j = 1; j <= t; j++) s += abs(b[j] - mid);
 				cost[i][t] = s;
 			}
@@ -38,7 +38,7 @@
 	}
 	long long ans = INF;
 	for(int s = 0; s <= maxS; s++){
-		// ��λ�� s+1 ��ѻ�������f[j]��ǰ j �����ֺöε���С����
+		// 从位置 s+1 起把环剪开，f[j]：前 j 个数分好段的最小代价
 		f[0] = 0;
 		for(int j = 1; j <= n; j++){
 			f[j] = INF;
```

## NOIP / NOIP模拟赛-第二套-CC版 / lamp
最接近代码块相似度：93.90%

```diff
--- std
+++ solution-block
@@ -25,7 +25,7 @@
 	if(bb < 0 || bb > a) return 0;
 	return fac[a] * inv[bb] % MOD * inv[a - bb] % MOD;
 }
-// ��״���飺���Ҷ˵�����ͳ���Ѽ�����߶θ���
+// 树状数组：按右端点排名统计已加入的线段个数
 void add(int p){
 	for(; p <= n; p += p & -p) t[p]++;
 }
@@ -53,8 +53,8 @@
 	sort(b + 1,b + n + 1);
 	sort(id + 1,id + n + 1,cmp);
 	long long ans = 0;
-	// �� (l, ���) ��������δ�����ÿ�������鵽�������������߶� s �ϣ�
-	// ���� k-1 ���� s ֮ǰ���Ҷ˵㲻С�� l_s + L ���߶���ѡ
+	// 按 (l, 编号) 排序后依次处理：每个方案归到其中排在最后的线段 s 上，
+	// 其余 k-1 条从 s 之前、右端点不小于 l_s + L 的线段中选
 	for(int q = 1; q <= n; q++){
 		int s = id[q];
 		if(r[s] - l[s] >= L){
```

## NOIP / NOIP模拟赛-第二套-CC版 / liar
最接近代码块相似度：87.14%

```diff
--- std
+++ solution-block
@@ -2,10 +2,10 @@
 using namespace std;
 const int N = 1e6 + 10;
 int c,n,m,K;
-int head[N],nxt[2 * N],to[2 * N],w[2 * N],tot;   // �ڽӱ���w Ϊ 1 ��ʾ�������ݲ�ͬ��0 ��ʾ��ͬ
-int col[N],q[N];         // col[x]��x ��Ⱦɫ��-1 ��ʾδ���ʣ���q Ϊ BFS ����
-int num[N];              // num[d]����������֮��Ϊ d ����ͨ�����
-bitset<N> dp;            // dp[s]����� s ��˵�����ܷ�ճ�
+int head[N],nxt[2 * N],to[2 * N],w[2 * N],tot;   // 邻接表：w 为 1 表示两人身份不同，0 表示相同
+int col[N],q[N];         // col[x]：x 的染色（-1 表示未访问）；q 为 BFS 队列
+int num[N];              // num[d]：两侧人数之差为 d 的连通块个数
+bitset<N> dp;            // dp[s]：多出 s 个说谎者能否凑出
 void addEdge(int u,int v,int t){
 	nxt[++tot] = head[u];
 	to[tot] = v;
@@ -22,13 +22,13 @@
 	for(int k = 1; k <= m; k++){
 		int i,j,t;
 		cin >> i >> j >> t;
-		// t = 1��i ˵ j ��˵���ߣ��������ݲ�ͬ��t = 0������������ͬ
+		// t = 1：i 说 j 是说谎者，两人身份不同；t = 0：两人身份相同
 		addEdge(i,j,t);
 		addEdge(j,i,t);
 	}
 	for(int i = 1; i <= n; i++) col[i] = -1;
 	long long base = 0;
-	// ��ÿ����ͨ�� BFS Ⱦɫ��ͳ��������ɫ����������ɫ��ͻ˵������ì��
+	// 对每个连通块 BFS 染色，统计两种颜色的人数；颜色冲突说明陈述矛盾
 	for(int s = 1; s <= n; s++){
 		if(col[s] != -1) continue;
 		int h = 0,tl = 0,cnt0 = 0,cnt1 = 0;
@@ -50,7 +50,7 @@
 				}
 			}
 		}
-		// ÿ����ͨ��ֻ�������ѡһ����ȡ�����ٵ�һ�࣬����� d ����Ϊ������Ʒ
+		// 每个连通块只能整体二选一：先取人数少的一侧，多出的 d 个作为背包物品
 		base += min(cnt0,cnt1);
 		num[abs(cnt0 - cnt1)]++;
 	}
@@ -58,7 +58,7 @@
 		cout << -1 << endl;
 		return 0;
 	}
-	// ��ͬ�� d ����Լ sqrt(2n) �֣���ÿ�� d �ĸ����������Ʋ�֣��� bitset �� 0/1 ����
+	// 不同的 d 至多约 sqrt(2n) 种，对每种 d 的个数做二进制拆分，用 bitset 做 0/1 背包
 	dp[0] = 1;
 	for(int d = 1; d <= n; d++){
 		int left = num[d];
```

## NOIP / NOIP模拟赛-第二套-CC版 / bridge
最接近代码块相似度：90.55%

```diff
--- std
+++ solution-block
@@ -3,15 +3,15 @@
 const int N = 3e5 + 10;
 int c,n,m;
 int eu[N],ev[N];
-int head[N],nxt[2 * N],eid[2 * N],gcnt;     // ԭͼ�ڽӱ�����ʽǰ���ǣ�����ߵı��
-int thead[N],tnxt[2 * N],tto[2 * N],tcnt;   // ����������������
+int head[N],nxt[2 * N],eid[2 * N],gcnt;     // 原图邻接表（链式前向星），存边的编号
+int thead[N],tnxt[2 * N],tto[2 * N],tcnt;   // 桥树（缩点后的树）
 int dfn[N],low[N],tim;
 bool isBridge[N];
 int comp[N],compCnt;
 long long sz[N];
 int dis[N],pre[N],dep[N],bel[N],q[N];
 long long brSum[N];
-long long sq;   // sumAtDepth ˳������ġ�����֧�͵�ƽ���͡�
+long long sq;   // sumAtDepth 顺便求出的“各分支和的平方和”
 void addEdge(int u,int e){
 	nxt[++gcnt] = head[u];
 	eid[gcnt] = e;
@@ -22,12 +22,12 @@
 	tto[tcnt] = v;
 	thead[u] = tcnt;
 }
-// �� e ����һ���˵�
+// 边 e 的另一个端点
 int other(int e,int u){
 	if(eu[e] == u) return ev[e];
 	return eu[e];
 }
-// Tarjan ���ţ�inE ���ߵ� u ʱ�����ıߵı�ţ�ֻ������һ���ߣ��������ȷ�����ر�
+// Tarjan 求桥：inE 是走到 u 时经过的边的编号，只跳过这一条边，因此能正确处理重边
 void tarjan(int u,int inE){
 	dfn[u] = low[u] = ++tim;
 	for(int i = head[u]; i != 0; i = nxt[i]){
@@ -43,7 +43,7 @@
 		}
 	}
 }
-// �������ϴ� s ���� BFS������벢��¼ǰ����������Զ��
+// 在桥树上从 s 出发 BFS，求距离并记录前驱，返回最远点
 int bfs(int s){
 	for(int i = 1; i <= compCnt; i++) dis[i] = -1;
 	int h = 0,t = 0;
@@ -65,8 +65,8 @@
 	}
 	return far;
 }
-// �� s ������������ block�������� s ����ǡΪ d �ķ�����С֮�ͣ�
-// brSum[x] �ۼ����� s ���ھӷ�֧ x �Ĳ��֣�ȫ�ֱ��� sq ��¼����֧�͵�ƽ����
+// 从 s 出发（不经过 block），求与 s 距离恰为 d 的分量大小之和；
+// brSum[x] 累加属于 s 的邻居分支 x 的部分，全局变量 sq 记录各分支和的平方和
 long long sumAtDepth(int s,int block,int d){
 	for(int i = 1; i <= compCnt; i++) dep[i] = -1;
 	int h = 0,t = 0;
@@ -112,7 +112,7 @@
 		addEdge(ev[i],i);
 	}
 	tarjan(1,0);
-	// �������ŵ���ͨ����Ǳ�˫��ͨ����
+	// 不经过桥的连通块就是边双连通分量
 	for(int i = 1; i <= n; i++){
 		if(comp[i]) continue;
 		compCnt++;
@@ -144,7 +144,7 @@
 		cout << 0 << ' ' << 1LL * n * (n - 1) / 2 << endl;
 		return 0;
 	}
-	// ����ֱ�� D���ӵı����ӵ��������������Ͼ���Ϊ D ʱ����ȥ�������
+	// 桥树直径 D：加的边连接的两个分量在树上距离为 D 时，消去的桥最多
 	int a = bfs(1);
 	int b = bfs(a);
 	int D = dis[b];
@@ -152,12 +152,12 @@
 	for(int x = b; x != 0; x = pre[x]) path.push_back(x);
 	long long ways;
 	if(D % 2 == 0){
-		// ֱ�������ǵ� mid�����˵㵽 mid �ľ��붼�� D/2������ mid �Ĳ�ͬ��֧��
+		// 直径中心是点 mid：两端点到 mid 的距离都是 D/2，且在 mid 的不同分支中
 		int mid = path[D / 2];
 		long long S = sumAtDepth(mid,0,D / 2);
 		ways = (S * S - sq) / 2;
 	}else{
-		// ֱ�������Ǳ� (x,y)�����˵�ֱ������������࣬�� x��y �ľ��붼�� (D-1)/2
+		// 直径中心是边 (x,y)：两端点分别在这条边两侧，到 x、y 的距离都是 (D-1)/2
 		int x = path[(D - 1) / 2],y = path[(D + 1) / 2];
 		long long Wx = sumAtDepth(x,y,(D - 1) / 2);
 		long long Wy = sumAtDepth(y,x,(D - 1) / 2);
```

## NOIP / NOIP模拟赛-第二套-CC版 / park
最接近代码块相似度：89.64%

```diff
--- std
+++ solution-block
@@ -2,15 +2,15 @@
 using namespace std;
 const int N = 1e5 + 10;
 const int K = 205;
-const long long NEG = -1e18;   // ��ʾ�����ܵ�״̬
+const long long NEG = -1e18;   // 表示不可能的状态
 int c,n,k;
 long long a[N];
 vector<int> g[N];
 int sz[N];
-// f[u][j][0]��u ��������ǡ���γ� j ��������u ������ʱ���������
-// f[u][j][1]��u ���ţ�u ���ڵľ����Ѿ����� j��ʱ���������
+// f[u][j][0]：u 的子树中恰好形成 j 个景区、u 不开放时的最大收益
+// f[u][j][1]：u 开放（u 所在的景区已经计入 j）时的最大收益
 long long f[N][K][2];
-long long t0[K],t1[K];         // �ϲ�һ������ʱ����ʱ���
+long long t0[K],t1[K];         // 合并一个儿子时的临时结果
 void dfs(int u,int fa){
 	sz[u] = 1;
 	f[u][0][0] = 0;
@@ -21,7 +21,7 @@
 		int v = g[u][i];
 		if(v == fa) continue;
 		dfs(v,u);
-		// ֻö�ٵ����Ѻϲ��ĵ������� k �н�С���Ǹ�
+		// 只枚举到“已合并的点数”和 k 中较小的那个
 		int lu = min(sz[u],k),lv = min(sz[v],k),lim = min(sz[u] + sz[v],k);
 		for(int j = 0; j <= lim; j++){
 			t0[j] = NEG;
@@ -30,16 +30,16 @@
 		for(int x = 0; x <= lu; x++){
 			for(int y = 0; y <= lv; y++){
 				long long best = max(f[v][y][0],f[v][y][1]);
-				// u �����ţ�v һ��ľ������Զ���
+				// u 不开放：v 一侧的景区各自独立
 				if(f[u][x][0] != NEG && best != NEG && x + y <= lim){
 					t0[x + y] = max(t0[x + y],f[u][x][0] + best);
 				}
 				if(f[u][x][1] == NEG) continue;
-				// u ���š�v �����ţ����������
+				// u 开放、v 不开放：景区数相加
 				if(f[v][y][0] != NEG && x + y <= lim){
 					t1[x + y] = max(t1[x + y],f[u][x][1] + f[v][y][0]);
 				}
-				// u��v �����ţ�v ���ڵľ����� u ���ڵľ�������һ��
+				// u、v 都开放：v 所在的景区与 u 所在的景区连成一个
 				if(f[v][y][1] != NEG && x + y - 1 <= lim){
 					t1[x + y - 1] = max(t1[x + y - 1],f[u][x][1] + f[v][y][1]);
 				}
```

## NOIP / 第一套 NOIP 模拟卷 / xor4
最接近代码块相似度：94.22%

```diff
--- std
+++ solution-block
@@ -25,14 +25,14 @@
 			if(j % 2 == 1) w = x ^ p[(j + 1) / 2];
 			f[i][j] = -inf;
 
-			// �Ӷδ� i ��ʼ��ǰ��Ҫ�ܷ��¸ý׶�֮ǰ�Ĳ�����
+			// 子段从 i 开始，前面要能放下该阶段之前的操作。
 			int first = 1;
 			if(j > 0) first = j / 2 + 1;
 			if(i >= first) f[i][j] = w;
 
 			long long pre = f[i - 1][j];
 			if(j >= 1) pre = max(pre,f[i - 1][j - 1]);
-			// ���������ο������ڣ��м�Ŀ�϶����������
+			// 两个操作段可以相邻，中间的空隙可以跳过。
 			if(j >= 3 && j % 2 == 1) pre = max(pre,f[i - 1][j - 2]);
 			if(pre != -inf) f[i][j] = max(f[i][j],pre + w);
 
```

## NOIP / 第一套 NOIP 模拟卷 / triplet
最接近代码块相似度：98.54%

```diff
--- std
+++ solution-block
@@ -10,7 +10,7 @@
 int n,deg[N],sz[N],tag[N],cnt[3];
 bool cut[N],ok;
 
-// r = -1 ʱ��ɾ���ߣ�����ɾȥǰ׺��ģ 3 Ϊ r �Ļ��ߡ�
+// r = -1 时不删环边，否则删去前缀和模 3 为 r 的环边。
 void update(int r){
 	vector<int> now;
 	for(int i = 1; i <= n; i++){
```

## NOIP / 第一套 NOIP 模拟卷 / logic
最接近代码块相似度：94.06%

```diff
--- std
+++ solution-block
@@ -5,7 +5,7 @@
 int n,k,r,a[N][N],rhs[N];
 long long b[N];
 
-// b[i] �ǵ�һ�� 1 �ڵ� i �еĲ�ֻ�������
+// b[i] 是第一个 1 在第 i 列的差分基向量。
 void add(long long x){
 	for(int i = 1; i <= n; i++){
 		if(((x >> (i - 1)) & 1) == 0) continue;
@@ -39,7 +39,7 @@
 		return 0;
 	}
 
-	// ���������������е���Ԫ��ʹÿ����Ԫ��ֻ��һ�� 1��
+	// 消掉其他基向量中的主元，使每个主元列只有一个 1。
 	for(int i = n; i >= 1; i--){
 		if(b[i] == 0) continue;
 		for(int j = 1; j < i; j++){
@@ -55,13 +55,13 @@
 		for(int i = 1; i <= n; i++){
 			if(b[i] != 0) a[q][i] = (b[i] >> (j - 1)) & 1;
 		}
-		// �Ҷ��ɵ�һ�鸳ֵȷ����
+		// 右端由第一组赋值确定。
 		for(int i = 1; i <= n; i++){
 			if(a[q][i] == 1 && ((first >> (i - 1)) & 1)) rhs[q] ^= 1;
 		}
 	}
 
-	// �Թ�����ķ���������Ԫ��������ĿҪ������˳��
+	// 对构造出的方程组再消元，满足题目要求的输出顺序。
 	int row = 0;
 	for(int j = 1; j <= n; j++){
 		int p = row + 1;
```
