# T4 树与叶子

---

## 满分做法：原叶子计数与端点修正

---

删除一条边，只会使它的两个端点度数各减一，其他点的叶子身份完全不变。

对一个端点来说：原度数为 $1$，删除后变成 $0$，它原本就是叶子，仍然算叶子；原度数为 $2$，删除后变成 $1$，会新增一个叶子；原度数至少为 $3$，删除后仍不是叶子。

因此，只要知道一条边两侧各有多少个原叶子，再补上原度数为 $2$ 的端点即可。

任选点 $1$ 作为遍历根。令 $leaf[v]$ 表示 $v$ 的子树中，原树度数恰好为 $1$ 的点数；令 $L=leaf[1]$，即整棵树的原叶子数。对父子边 $(u,v)$，删除后两侧的叶子数分别为

$$L_1=leaf[v]+[deg(v)=2],$$

$$L_2=L-leaf[v]+[deg(u)=2].$$

方括号表示条件成立时取 $1$，否则取 $0$。其中一侧恰好是 $v$ 的子树，另一侧是它的补集，两个端点的新增叶子分别加在各自一侧。原度数为 $1$ 的端点即使变成孤点，也已经计入原叶子数，不能再重复加一。

计算 $leaf$ 时，先用迭代遍历得到一个父亲先于孩子出现的顺序，并记录每个点的父亲。初始化每个点的计数为“它的原度数是否等于 $1$”，再逆序扫描，把每个点的计数累加给父亲。

最后枚举所有非根节点 $v$，就枚举了全部父子边。按公式计算 $|L_1-L_2|$，维护最小值和相应边数。找到严格更小的值时，方案数重置为 $1$；遇到相同值时再加一。

这里统计的是无根树中度数为 $1$ 的原叶子，不是“有根树中没有孩子的点”；遍历根本身也可能是原叶子。迭代遍历还能避免长链上的递归栈问题。

每组时间复杂度为 $O(n)$，空间复杂度为 $O(n)$；多组的总时间复杂度为 $O(\sum n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int parentNode[100005], orderNode[100005], leaf[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            parentNode[i] = 0;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        // 先记录父亲在前的遍历顺序，避免长链递归爆栈。
        int count = 1;
        orderNode[1] = 1;
        for (int i = 1; i <= count; i++) {
            int u = orderNode[i];
            leaf[u] = 0;
            if (g[u].size() == 1) {
                leaf[u] = 1;
            }
            for (int j = 0; j < (int)g[u].size(); j++) {
                int v = g[u][j];
                if (v != parentNode[u]) {
                    parentNode[v] = u;
                    orderNode[++count] = v;
                }
            }
        }
        // leaf[u] 只统计原树中度为 1 的叶子。
        for (int i = n; i >= 2; i--) {
            int u = orderNode[i];
            leaf[parentNode[u]] += leaf[u];
        }
        int ans = n, ways = 0;
        for (int v = 2; v <= n; v++) {
            int u = parentNode[v];
            int left = leaf[v];
            int right = leaf[1] - leaf[v];
            if (g[v].size() == 2) {
                left++;
            }
            if (g[u].size() == 2) {
                right++;
            }
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
