# 采购 - 部分分题解

## 部分分总表

| 分值 | 特殊限制 | 做法 | 复杂度 |
|---:|---|---|---|
| $20$ | $n\le20$ | 枚举全部子集 | $O(n2^n)$ |
| $30$ | $m\le300$ | 二维 0/1 背包 | $O(nm)$ 时间，$O(nm)$ 空间 |
| $100$ | 无额外限制 | 一维倒序背包 | $O(nm)$ 时间，$O(m)$ 空间 |

## 小 $n$ 枚举

枚举每件商品选或不选，统计体积与收益，保留合法方案最大值。

## 小容量二维 DP

当 $m\le300$ 时，可以定义 `dp[i][j]` 表示只考虑前 $i$ 件商品、容量不超过 $j$ 的最大收益，直接进行二维转移。

最终交付程序组合两类做法，实际通过测试点 $1\sim5$，获得 $50$ 分。

## 为什么不能通过全部数据

一般数据不满足 $n\le20$ 或 $m\le300$。虽然二维 DP 在部分较大数据上也可能运行，但不属于公开保证范围。

## 从部分分到满分

观察到第 $i$ 层只依赖第 $i-1$ 层，把容量倒序枚举即可压缩成一维数组，稳定处理 $m\le3000$。

## 最终交付的部分分程序

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<int> w(n);
    vector<long long> v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
        v[i] -= k;
    }

    if (n <= 20) {
        long long ans = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            int sumW = 0;
            long long sumV = 0;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    sumW += w[i];
                    sumV += v[i];
                }
            }
            if (sumW <= m) {
                ans = max(ans, sumV);
            }
        }
        cout << ans << '\n';
        return 0;
    }

    if (m <= 300) {
        // 使用二维 0/1 背包，便于初学者理解“前 i 个物品”的含义。
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= w[i - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
                }
            }
        }
        cout << *max_element(dp[n].begin(), dp[n].end()) << '\n';
        return 0;
    }

    cout << 0 << '\n';
    return 0;
}
```
