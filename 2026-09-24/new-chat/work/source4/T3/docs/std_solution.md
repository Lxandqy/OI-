# 彩彩的三彩项链 - 满分题解

## 关键观察

点击颜色形成长度为 $3$ 的循环。把 `r,g,b` 编码为 $0,1,2$，原颜色为 $x$、目标颜色为 $y$ 时，最少点击次数为

$$(y-x+3)\bmod3。$$

项链的限制只与相邻珠子的目标颜色有关。枚举第一颗珠子的最终颜色后，就可以做线性 DP。

## 满分算法

对第一颗珠子的最终颜色 `first` 枚举 $0,1,2$。定义 `dp[c]` 为处理到当前位置且当前位置最终颜色为 $c$ 的最小点击次数。转移时只允许前后颜色不同。处理完以后，再要求最后一颗颜色与 `first` 不同。

## 正确性说明

固定第一颗目标颜色以后，任意合法方案都可以按照位置顺序分解为相邻颜色不同的转移；DP 枚举了当前目标颜色的三种可能，并对每个状态保留最小代价。最后补上首尾不同条件，就精确得到该第一颜色下的最优值。枚举三种第一颜色后取最小即为全局最优。

## 复杂度分析

每个位置只有常数个状态和转移，时间复杂度 $O(n)$，空间复杂度 $O(1)$。

## 边界与易错点

- 必须检查第 $n$ 颗和第 $1$ 颗；
- 改色是单向循环，不是任意换色一次；
- 同一颗珠子最多需要点击两次；
- $n$ 可达 $10^6$，不需要开二维 DP。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long solve(const string &s) {
    int n = s.size();
    const long long inf = (1LL << 60);
    long long answer = inf;

    auto id = [](char c) {
        if (c == 'r') return 0;
        if (c == 'g') return 1;
        return 2;
    };

    for (int first = 0; first < 3; first++) {
        long long dp[3] = {inf, inf, inf};
        dp[first] = (first - id(s[0]) + 3) % 3;

        for (int i = 1; i < n; i++) {
            long long ndp[3] = {inf, inf, inf};
            int original = id(s[i]);
            for (int last = 0; last < 3; last++) {
                for (int now = 0; now < 3; now++) {
                    if (last != now) {
                        ndp[now] = min(ndp[now], dp[last] + (now - original + 3) % 3);
                    }
                }
            }
            for (int c = 0; c < 3; c++) {
                dp[c] = ndp[c];
            }
        }

        for (int last = 0; last < 3; last++) {
            if (last != first) {
                answer = min(answer, dp[last]);
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;
    cout << solve(s) << '\n';
    return 0;
}
```
