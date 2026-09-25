# 整除序列 - 满分题解

## 关键观察

因为序列严格递增，若相邻两项满足后一项是前一项的倍数，则更早的项也一定整除后一项。因此只需要维护相邻转移。

把区间中的每个整数看作一个点。若 $x<y$ 且 $x\mid y$，就可以从 $x$ 转移到 $y$。所有边都从小数指向大数，构成 DAG。

## 满分算法

定义：

- `len[x]`：以 $x$ 结尾的最长合法序列长度；
- `ways[x]`：达到该长度的方案数。

按照 $x=L,L+1,\ldots,R$ 处理，并枚举 $x$ 的所有倍数 $2x,3x,\ldots$ 进行最长路计数转移。方案数使用 `cpp_int` 保存。

## 正确性说明

所有合法序列的最后一步一定从某个能整除末项的较小数转移而来；算法枚举了每个 $x$ 在区间内的全部更大倍数，因此覆盖所有合法转移。按数值递增处理保证转移来源已经完成，标准 DAG 最长路计数即可得到每个终点的最长长度与方案数。最后汇总全局最大长度的终点。

## 复杂度分析

时间复杂度为

$$O\left(\sum_{x=L}^{R}\frac{R}{x}\right),$$

最坏约为 $O(R\log R)$；空间复杂度 $O(R)$，另加大整数存储。

## 边界与易错点

- 长度为 $1$ 的每个单元素序列都是一种方案；
- 方案数可能很大，不能使用普通整数假设；
- 只有严格更大的倍数才能转移；
- 多组询问需要重新初始化状态。

## 参考代码

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
        vector<int> len(R + 1, 1);
        vector<cpp_int> ways(R + 1, 1);

        for (int x = L; x <= R; x++) {
            for (int y = x + x; y <= R; y += x) {
                int candidate = len[x] + 1;
                if (candidate > len[y]) {
                    len[y] = candidate;
                    ways[y] = ways[x];
                } else if (candidate == len[y]) {
                    ways[y] += ways[x];
                }
            }
        }

        int bestLen = 0;
        cpp_int answer = 0;
        for (int x = L; x <= R; x++) {
            if (len[x] > bestLen) {
                bestLen = len[x];
                answer = ways[x];
            } else if (len[x] == bestLen) {
                answer += ways[x];
            }
        }
        cout << bestLen << ' ' << answer << '\n';
    }
    return 0;
}
```
