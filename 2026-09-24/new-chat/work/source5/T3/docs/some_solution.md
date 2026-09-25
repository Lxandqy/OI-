# 整除序列 - 部分分题解

## 部分分总表

| 分值 | 特殊限制 | 做法 | 复杂度 |
|---:|---|---|---|
| $20$ | $R-L\le20$ | 枚举区间中所有数对进行 DP | $O((R-L+1)^2)$ |
| $30$ | $R\le2000$ | 枚举所有 $x<y$，判断 $x\mid y$ | $O((R-L+1)^2)$ |
| $100$ | 无额外限制 | 只枚举每个数的倍数 | $O(R\log R)$ |

## 二次方 DP

区间按数值天然有序。枚举所有 $i<j$，若 $(L+j)\bmod(L+i)=0$，就进行最长路和方案数转移。

最终交付程序在区间长度不超过 $21$ 或 $R\le2000$ 时使用该方法，实际通过测试点 $1\sim5$，获得 $50$ 分。

## 为什么不能通过全部数据

区间长度接近 $10^5$ 时，二次方枚举需要约 $10^{10}$ 次判断。

## 从部分分到满分

对于固定的 $x$，无需检查所有更大的 $y$，只需枚举 $2x,3x,\ldots$。这样转移数量降为调和级数规模。

## 最终交付的部分分程序

```cpp
#include<bits/stdc++.h>
#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int L, R;
        cin >> L >> R;
        int n = R - L + 1;
        if (!(n <= 21 || R <= 2000)) {
            cout << "0 0\n";
            continue;
        }

        vector<int> len(n, 1);
        vector<cpp_int> ways(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x = L + i;
                int y = L + j;
                if (y % x == 0) {
                    int candidate = len[i] + 1;
                    if (candidate > len[j]) {
                        len[j] = candidate;
                        ways[j] = ways[i];
                    } else if (candidate == len[j]) {
                        ways[j] += ways[i];
                    }
                }
            }
        }

        int bestLen = 0;
        cpp_int answer = 0;
        for (int i = 0; i < n; i++) {
            if (len[i] > bestLen) {
                bestLen = len[i];
                answer = ways[i];
            } else if (len[i] == bestLen) {
                answer += ways[i];
            }
        }
        cout << bestLen << ' ' << answer << '\n';
    }
    return 0;
}
```
