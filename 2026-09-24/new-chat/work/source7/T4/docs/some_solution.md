# T4 树与叶子

---

小规模两档按累计分计算；链与最优断边唯一两档各独立占 10 分。

## 部分分（累计 10 分，$n\le100$）：枚举断边

---

本档只有一组数据。逐条枚举要删除的边，分别从两个端点出发做 BFS，统计断边后两部分的叶子数量。

不必真的从邻接表删除边，只需在遍历时跳过这条边。计算一个点的新度数时，先取原度数；如果它是被删边的端点，就减一。新度数不超过 $1$ 时计为叶子，所以断边产生的孤立点也要统计。

得到两边叶子数后，计算差的绝对值。出现更小的差值时，将方案数重置为 $1$；差值相等时，方案数加一。

每组时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int edgeU[100005], edgeV[100005], que[100005];
bool seen[100005];
int n, bannedU, bannedV;

int countLeaves(int start) {
    for (int i = 1; i <= n; i++) {
        seen[i] = false;
    }
    int head = 0, tail = 1, result = 0;
    que[0] = start;
    seen[start] = true;
    while (head < tail) {
        int u = que[head++];
        int degree = (int)g[u].size();
        if (u == bannedU || u == bannedV) {
            degree--;
        }
        if (degree <= 1) {
            result++;
        }
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if ((u == bannedU && v == bannedV) ||
                (u == bannedV && v == bannedU)) {
                continue;
            }
            if (!seen[v]) {
                seen[v] = true;
                que[tail++] = v;
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
        }
        for (int i = 1; i < n; i++) {
            cin >> edgeU[i] >> edgeV[i];
            g[edgeU[i]].push_back(edgeV[i]);
            g[edgeV[i]].push_back(edgeU[i]);
        }
        int ans = n, ways = 0;
        for (int i = 1; i < n; i++) {
            bannedU = edgeU[i];
            bannedV = edgeV[i];
            int left = countLeaves(bannedU);
            int right = countLeaves(bannedV);
            int difference = abs(left - right);
            if (difference < ans) {
                ans = difference;
                ways = 1;
            } else if (difference == ans) {
                ways++;
            }
        }
        cout << ans << ' ' << ways << '\n';
    }
    return 0;
}
```

## 部分分（累计 20 分，$n\le1000$）：继续按定义统计

---

仍然可以使用上一节的断边枚举。每次 BFS 都要清空访问标记；处理新的一组树之前，清空邻接表，并重新初始化最小差值与方案数。

算法仍是逐条尝试全部边，再按删除后的度数数叶子；输入允许多组，并不改变每一组的处理方法。

每组时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

### 参考代码

代码与上一节“部分分（累计 10 分，$n\le100$）：枚举断边”相同，不重复列出。

## 部分分（独立 10 分）：树是一条链

---

一条链至少有两个点时，叶子数为 $2$；只有一个点时，叶子数为 $1$。因此只需按 $n$ 分类。

$n=2$ 时，删除唯一的边得到两个孤点，输出 `0 1`。$n=3$ 时，两条边都把链分成一个孤点和一条两点链，输出 `1 2`。

$n\ge4$ 时，删除两条端边会产生一个孤点，两侧叶子数为 $1$ 和 $2$。其余 $n-3$ 条边都让两侧至少有两个点，两侧叶子数均为 $2$，因此输出 $0$ 和 $n-3$。

时间复杂度为 $O(n)$，用于读入全部边；额外空间复杂度为 $O(1)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
        }
        if (n == 2) {
            cout << "0 1\n";
        } else if (n == 3) {
            cout << "1 2\n";
        } else {
            cout << 0 << ' ' << n - 3 << '\n';
        }
    }
    return 0;
}
```

## 部分分（独立 10 分）：最优断边唯一

---

这条性质直接确定第二个输出为 $1$，但不能确定最小叶子数差值，也不能确定最优边在哪里。

可以使用本题满分做法的子树叶子计数与端点修正，逐边求出差值，再取最小值。唯一性保证只省去并列方案的统计，寻找最小差值的过程仍然需要完成。

每组时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 参考代码

完整代码见本题满分题解中的“满分做法：原叶子计数与端点修正”。该程序也能处理本档，不重复列出。

## 部分分综合做法

---

先检查所有点的度数是否都不超过 $2$。输入已经保证是一棵树，所以满足这个条件时就是一条链，直接使用上面的分类公式。

其他树采用断边枚举与 BFS。这就同时处理了小规模的一般树和大规模的链，而不必让长链也执行平方级的重算。

每组链的时间复杂度为 $O(n)$，一般树为 $O(n^2)$；空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int edgeU[100005], edgeV[100005], que[100005];
bool seen[100005];
int n, bannedU, bannedV;

int countLeaves(int start) {
    for (int i = 1; i <= n; i++) {
        seen[i] = false;
    }
    int head = 0, tail = 1, result = 0;
    que[0] = start;
    seen[start] = true;
    while (head < tail) {
        int u = que[head++];
        int degree = (int)g[u].size();
        if (u == bannedU || u == bannedV) {
            degree--;
        }
        if (degree <= 1) {
            result++;
        }
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if ((u == bannedU && v == bannedV) ||
                (u == bannedV && v == bannedU)) {
                continue;
            }
            if (!seen[v]) {
                seen[v] = true;
                que[tail++] = v;
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
        }
        for (int i = 1; i < n; i++) {
            cin >> edgeU[i] >> edgeV[i];
            g[edgeU[i]].push_back(edgeV[i]);
            g[edgeV[i]].push_back(edgeU[i]);
        }
        bool chain = true;
        for (int i = 1; i <= n; i++) {
            if (g[i].size() > 2) {
                chain = false;
            }
        }
        if (chain) {
            if (n == 2) {
                cout << "0 1\n";
            } else if (n == 3) {
                cout << "1 2\n";
            } else {
                cout << 0 << ' ' << n - 3 << '\n';
            }
            continue;
        }
        int ans = n, ways = 0;
        for (int i = 1; i < n; i++) {
            bannedU = edgeU[i];
            bannedV = edgeV[i];
            int left = countLeaves(bannedU);
            int right = countLeaves(bannedV);
            int difference = abs(left - right);
            if (difference < ans) {
                ans = difference;
                ways = 1;
            } else if (difference == ans) {
                ways++;
            }
        }
        cout << ans << ' ' << ways << '\n';
    }
    return 0;
}
```
