# T2 各乘一个

---

以下四组条件各独立占 20 分，不能把标题中的分值理解为累计分。

## 部分分（独立 20 分，$n\le20$）：枚举下标组合

---

一个方案由递增下标 $i_1<i_2<\cdots<i_x$ 唯一确定。选出第 $j$ 个位置后，它就与 $b_j$ 配对，不需要再枚举系数的排列。

用 DFS 维护下一个可选位置 `start`、已经选择的数量 `chosen` 和当前分数 `sum`。选择位置 $i$ 后，递归到 $i+1$，并把 $a_i b_{chosen+1}$ 加入分数。恰好选满 $x$ 项时更新答案。

还需要选择 $x-chosen$ 项时，下一位置最多取到 $n-(x-chosen)+1$，否则后面剩余的位置不够。初始答案应为负无穷，因为恰好选满后的最大分数也可能是负数。

时间复杂度上界为 $O\!\left(x\binom{n}{x}\right)$；存储输入及递归栈的空间复杂度为 $O(n+x)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long NEG = -(1LL << 60);
int n, x, a[100005], b[11];
long long ans = NEG;
void dfs(int start, int chosen, long long sum) {
    if (chosen == x) {
        ans = max(ans, sum);
        return;
    }
    for (int i = start; i <= n - (x - chosen) + 1; i++) {
        dfs(i + 1, chosen + 1, sum + 1LL * a[i] * b[chosen + 1]);
    }
}
int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
    }
    dfs(1, 0, 0);
    cout << ans << '\n';
    return 0;
}
```

## 部分分（独立 20 分，$x=1$）：比较单项乘积

---

只需要选一个位置，答案就是所有 $a_i b_1$ 的最大值。扫描数组，逐个计算乘积并更新答案。

应当比较乘积，而不是直接取最大的 $a_i$。当 $b_1<0$ 时，较小的 $a_i$ 反而可能得到较大的分数。

时间复杂度为 $O(n)$；下面的代码保存输入数组，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long NEG = -(1LL << 60);
int n, x, a[100005], b[11];
long long ans = NEG;
int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, 1LL * a[i] * b[1]);
    }
    cout << ans << '\n';
    return 0;
}
```

## 部分分（独立 20 分，$x=2$）：维护前缀最优

---

固定第二个位置 $j$，分数为

$$a_i b_1+a_j b_2,\qquad i<j.$$

第二项已经确定，左边只需要找到最大的 $a_i b_1$。从左到右枚举 $j$，用 `left` 维护位置 $1\sim j-1$ 中最大的 $a_i b_1$，再用 `left + a[j] * b[2]` 更新答案。

必须先计算以 $j$ 为第二个位置的方案，再把 $a_jb_1$ 加入前缀最优，避免把同一个位置使用两次。

时间复杂度为 $O(n)$；保存输入数组时，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long NEG = -(1LL << 60);
int n, x, a[100005], b[11];
long long ans = NEG;
int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
    }
    long long left = 1LL * a[1] * b[1];
    for (int j = 2; j <= n; j++) {
        ans = max(ans, left + 1LL * a[j] * b[2]);
        left = max(left, 1LL * a[j] * b[1]);
    }
    cout << ans << '\n';
    return 0;
}
```

## 部分分（独立 20 分，$x=3$）：固定中间位置

---

固定第二个位置 $j$ 后，左边的第一个位置和右边的第三个位置互不影响，可以分别取最优。

预处理 `leftBest[i]`，表示前 $i$ 项中最大的 $a_tb_1$；再预处理 `rightBest[i]`，表示从位置 $i$ 开始的后缀中最大的 $a_tb_3$。

枚举 $j=2,\ldots,n-1$，该中间位置对应的最大分数为

$$\text{leftBest}[j-1]+a_jb_2+\text{rightBest}[j+1].$$

左右分别使用 $j-1$ 和 $j+1$，保证三个位置严格递增。比较所有中间位置的结果即可。

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long NEG = -(1LL << 60);
int n, x, a[100005], b[11];
long long ans = NEG;
long long leftBest[100005], rightBest[100005];
int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
    }
    leftBest[0] = NEG;
    rightBest[n + 1] = NEG;
    for (int i = 1; i <= n; i++) {
        leftBest[i] = max(leftBest[i - 1], 1LL * a[i] * b[1]);
    }
    for (int i = n; i >= 1; i--) {
        rightBest[i] = max(rightBest[i + 1], 1LL * a[i] * b[3]);
    }
    for (int j = 2; j < n; j++) {
        long long value = leftBest[j - 1] + 1LL * a[j] * b[2];
        value += rightBest[j + 1];
        ans = max(ans, value);
    }
    cout << ans << '\n';
    return 0;
}
```

## 部分分综合做法

---

将上述做法合并：$x=1$ 时取单项最大值，$x=2$ 时使用前缀最优，$x=3$ 时使用前后缀最优；其他情况使用 DFS 枚举下标组合。

这份程序可以处理 $n\le20$ 的小数据，也可以处理 $x\le3$ 的大数组。四组条件各独立占 $20$ 分，合计覆盖 $80$ 分。

$x\le3$ 时，时间复杂度为 $O(n)$；其他情况的时间复杂度上界为 $O\!\left(n+x\binom{n}{x}\right)$。空间复杂度为 $O(n+x)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
int n, x, a[100005], b[11];
long long leftBest[100005], rightBest[100005], ans = NEG;

// 其余情况枚举所选下标；没有故意输出错误值的范围判断。
void dfs(int start, int chosen, long long sum) {
    if (chosen == x) {
        ans = max(ans, sum);
        return;
    }
    for (int i = start; i <= n - (x - chosen) + 1; i++) {
        dfs(i + 1, chosen + 1, sum + 1LL * a[i] * b[chosen + 1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
    }
    leftBest[0] = NEG;
    for (int i = 1; i <= n; i++) {
        leftBest[i] = max(leftBest[i - 1], 1LL * a[i] * b[1]);
    }
    if (x == 1) {
        ans = leftBest[n];
    } else if (x == 2) {
        for (int j = 2; j <= n; j++) {
            ans = max(ans, leftBest[j - 1] + 1LL * a[j] * b[2]);
        }
    } else if (x == 3) {
        rightBest[n + 1] = NEG;
        for (int i = n; i >= 1; i--) {
            rightBest[i] = max(rightBest[i + 1], 1LL * a[i] * b[3]);
        }
        for (int j = 2; j < n; j++) {
            ans = max(ans, leftBest[j - 1] + 1LL * a[j] * b[2] + rightBest[j + 1]);
        }
    } else {
        dfs(1, 0, 0);
    }
    cout << ans << '\n';
    return 0;
}
```
