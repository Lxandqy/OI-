# T4 切割

---

## 部分分（累计 20 分，$n,k\le10$）：枚举切法

---

一个 $L$ 位数有 $L-1$ 个相邻数位间隙，每个间隙只有“切”或“不切”两种选择，因此共有 $2^{L-1}$ 种切法。

先单独处理一个数。用二进制掩码表示选中了哪些切点，从左到右扫描数位，得到各段的数值之和及切割次数。只保存和对 $k$ 的余数，用 `best[r]` 记录这个数切开后总和余数为 $r$ 时，最少需要切几次。

再合并不同原数。令 `dp[r]` 表示已经处理过的原数，其全部数段之和模 $k$ 为 $r$ 时的最少切割次数。把新数的余数 $t$ 加入后，有

$$nextDp[(r+t)\bmod k]=\min\bigl(nextDp[(r+t)\bmod k],\ dp[r]+best[t]\bigr).$$

初始只有 `dp[0]=0` 可达。每次用独立的 `nextDp` 合并，避免重复使用当前原数。每个原数的切法相互独立，合并时同时累加余数和切割数即可。全部处理后查看 `dp[0]`，不可达时输出 $-1$。

设第 $t$ 个数有 $L_t$ 位，时间复杂度为 $O(\sum_t L_t2^{L_t-1}+nk^2)$，额外空间复杂度为 $O(k+\max L_t)$。

### 参考代码

完整代码见下一节“部分分（累计 60 分）：短数字的切法枚举”，两档使用同一程序。

## 部分分（累计 60 分）：短数字的切法枚举

---

本档保证 $n,k\le100$、$a_i\le10^5$。每个原数最多 $6$ 位，只有 $5$ 个间隙，最多枚举 $32$ 种切法，因此仍可使用上一节的切法枚举与余数合并。

计算每一段时，可以始终维护 `value = (value * 10 + digit) % k`，不必保存完整段值。到达被选中的切点或当前原数的末尾时，把 `value` 加入段值总和，再将它清零。只有内部切点增加切割次数，原数末尾不增加。

掩码为 $0$ 就表示完全不切；数段以零开头也要正常保留。例如 `100` 可以切成 `1` 和 `00`，后者贡献 $0$。

时间复杂度仍为 $O(\sum_t L_t2^{L_t-1}+nk^2)$，额外空间复杂度为 $O(k+\max L_t)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
int best[405], dp[405], nextDp[405];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int r = 1; r < k; r++) {
        dp[r] = INF;
    }
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int length = (int)s.size();
        for (int r = 0; r < k; r++) {
            best[r] = INF;
            nextDp[r] = INF;
        }
        // 每个相邻数位间隙选切或不切，统计该数字的全部切法。
        for (int mask = 0; mask < (1 << (length - 1)); mask++) {
            int sum = 0, value = 0, cuts = 0;
            for (int j = 0; j < length; j++) {
                value = (value * 10 + s[j] - '0') % k;
                if (j == length - 1 || (mask & (1 << j)) != 0) {
                    sum = (sum + value) % k;
                    value = 0;
                    if (j != length - 1) {
                        cuts++;
                    }
                }
            }
            best[sum] = min(best[sum], cuts);
        }
        for (int r = 0; r < k; r++) {
            if (dp[r] == INF) {
                continue;
            }
            for (int t = 0; t < k; t++) {
                if (best[t] != INF) {
                    int next = (r + t) % k;
                    nextDp[next] = min(nextDp[next], dp[r] + best[t]);
                }
            }
        }
        for (int r = 0; r < k; r++) {
            dp[r] = nextDp[r];
        }
    }
    if (dp[0] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[0] << '\n';
    }
    return 0;
}
```
