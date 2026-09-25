# T4 切割

---

## 满分做法：数位位置与余数动态规划

---

不必枚举一个数的全部切法，可以改为逐段决定“下一段在哪里结束”。

将所有原数的数位顺次存入字符串，同时记录 `rightEnd[pos]`：位置 `pos` 所属原数的最后一个数位在哪里。这样便于统一枚举，但任何一段都不能跨过这个右端点。

令 $dp[i][r]$ 表示：前 $i$ 个数位已经分段完毕，各段数值之和模 $k$ 为 $r$ 时，最少需要的切割次数。初始 $dp[0][0]=0$，其余状态不可达。

从状态 $dp[i][r]$ 出发，下一段从 $i+1$ 开始。枚举右端 $j$，范围为

$$i+1\le j\le rightEnd[i+1].$$

向右延长时，逐位维护这一段的余数 `value`。如果 $j$ 尚未到原数末尾，就需要在 $j$ 后面切一次，令 $cost=1$；如果 $j$ 恰好在原数末尾，这里本来就分属两个原数，不必切，令 $cost=0$。

于是转移为

$$dp[j][(r+value)\bmod k]=\min\bigl(dp[j][(r+value)\bmod k],\ dp[i][r]+cost\bigr).$$

任意合法切法都能按顺序拆成这样的逐段选择；每个内部切点恰好在前一段结束时计费一次。因此，所有数位处理完成后，余数为 $0$ 的最小代价就是答案。完全不切也可能最优；该状态不可达时才输出 $-1$。

设第 $t$ 个数的长度为 $L_t$，总长度为 $L=\sum_tL_t$。时间复杂度为 $O(k\sum_tL_t^2)$，空间复杂度为 $O(Lk)$。$10^{18}$ 有 $19$ 位；只维护余数可以避免分段数值相加时溢出。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
int dp[8005][405], rightEnd[8005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    string s = " ";
    for (int i = 1; i <= n; i++) {
        string t;
        cin >> t;
        int start = (int)s.size();
        s += t;
        int finish = (int)s.size() - 1;
        for (int j = start; j <= finish; j++) {
            rightEnd[j] = finish;
        }
    }
    int length = (int)s.size() - 1;
    for (int i = 0; i <= length; i++) {
        for (int r = 0; r < k; r++) {
            dp[i][r] = INF;
        }
    }
    dp[0][0] = 0;
    // dp[i][r]：前 i 位已分段完成，数字和模 k 为 r 的最少切割数。
    for (int i = 0; i < length; i++) {
        int value = 0;
        for (int j = i + 1; j <= rightEnd[i + 1]; j++) {
            value = (value * 10 + s[j] - '0') % k;
            int cost = 0;
            if (j < rightEnd[i + 1]) {
                cost = 1;
            }
            for (int r = 0; r < k; r++) {
                if (dp[i][r] == INF) {
                    continue;
                }
                int next = (r + value) % k;
                dp[j][next] = min(dp[j][next], dp[i][r] + cost);
            }
        }
    }
    if (dp[length][0] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[length][0] << '\n';
    }
    return 0;
}
```
