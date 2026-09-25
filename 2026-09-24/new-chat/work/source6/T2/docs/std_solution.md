# T2 各乘一个

---

## 满分做法：前缀动态规划

---

令 $dp[i][j]$ 表示：只考虑 $a$ 的前 $i$ 项，恰好选出 $j$ 项，按顺序与 $b$ 的前 $j$ 项配对时，能够得到的最大分数。

处理位置 $i$ 时只有两种选择。不选 $a_i$，答案来自 $dp[i-1][j]$；选择 $a_i$，它必须作为第 $j$ 个选中的数，贡献为 $a_ib_j$，前面还需要恰好选出 $j-1$ 项。因此

$$dp[i][j]=\max\bigl(dp[i-1][j],\ dp[i-1][j-1]+a_ib_j\bigr).$$

两种情况包含了所有合法方案，而且第二种只从上一行转移，不会重复使用位置 $i$。

初始化 $dp[i][0]=0$。空前缀不能选出正数个元素，所以 $dp[0][j]=-\infty\ (j>0)$；不可达状态不参加加法。不能把所有状态初始化为 $0$，否则负分方案可能被不存在的空方案替代。

按 $i$ 从小到大计算，最后输出 $dp[n][x]$。数组 $a$ 和 $b$ 都不能排序，因为配对顺序是题目条件。乘法需要先转为 `long long`，例如 `1LL * a[i] * b[j]`。

时间复杂度为 $O(nx)$，空间复杂度为 $O(nx)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
long long dp[100005][11];
int a[100005], b[11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
        dp[0][j] = NEG;
    }
    // dp[i][j]：前 i 个元素中恰好选 j 个，与 b 的前 j 项配对。
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= x; j++) {
            dp[i][j] = dp[i - 1][j];
            if (dp[i - 1][j - 1] != NEG) {
                long long value = dp[i - 1][j - 1] + 1LL * a[i] * b[j];
                dp[i][j] = max(dp[i][j], value);
            }
        }
    }
    cout << dp[n][x] << '\n';
    return 0;
}
```
