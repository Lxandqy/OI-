# 采购 - 满分题解

## 题意转化

每选择一件商品，目标函数增加

$$val_i-k。$$

因此把每件商品的新价值定义为 $v_i=val_i-k$，题目就是容量为 $m$ 的 0/1 背包。允许不选任何商品，所以答案至少为 $0$。

## 满分算法

定义 `dp[j]` 为总体积不超过 $j$ 时的最大收益。对每件商品按容量从大到小转移：

$$dp[j]=\max(dp[j],dp[j-w_i]+val_i-k)。$$

## 正确性说明

目标函数可以按商品拆分为每件被选商品的独立贡献 $val_i-k$。每件商品至多选择一次，体积和不超过 $m$，完全符合 0/1 背包模型。倒序枚举容量保证同一件商品不会被重复使用。

## 复杂度分析

时间复杂度 $O(nm)$，空间复杂度 $O(m)$。

## 边界与易错点

- 可以不选择商品，不能把答案初始化为负无穷；
- `val_i-k` 可能为负；
- 容量必须倒序枚举；
- 目标值建议使用 `long long`。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<long long> dp(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        int w;
        long long value;
        cin >> w >> value;
        long long gain = value - k;
        for (int j = m; j >= w; j--) {
            dp[j] = max(dp[j], dp[j - w] + gain);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';
    return 0;
}
```
