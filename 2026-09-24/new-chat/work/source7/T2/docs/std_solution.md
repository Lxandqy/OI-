# T2 交错四元组

---

## 满分做法：固定中间两项，统计两侧数量

---

固定中间两个位置 $j,k$，并先检查 $a_k<a_j$。此时，左端 $i$ 只需满足 $i<j$ 且 $a_i<a_k$；右端 $l$ 只需满足 $l>k$ 且 $a_l>a_j$。

两边的选择互不影响。如果左侧有 $L$ 个合法位置，右侧有 $R$ 个合法位置，这一对中间位置就贡献 $L\times R$ 个四元组。

用 `leftLess[j][k]` 记录左侧的合法位置数。固定 $k$，从小到大枚举 $j$，可以得到

$$leftLess[j][k]=leftLess[j-1][k]+[a_{j-1}<a_k].$$

右侧不必再开二维数组。固定 $j$ 后，从右向左枚举 $k$，用 `rightGreater` 维护严格在 $k$ 右侧且大于 $a_j$ 的元素数。

每次先判断 $a_k<a_j$：成立时累加 `leftLess[j][k] * rightGreater`。随后，如果 $a_k>a_j$，就把当前位置加入 `rightGreater`，供下一个更小的 $k$ 使用。先统计、后加入，可以始终保证右端位置严格大于 $k$。

每个合法四元组都有唯一的中间位置对 $(j,k)$；固定它们后，两侧合法位置的所有组合都满足要求，所以不会重复或遗漏。答案可能超过 32 位范围，应使用 `long long`。

时间复杂度为 $O(n^2)$，空间复杂度为 $O(n^2)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[2005], leftLess[2005][2005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // leftLess[j][k]：下标小于 j、数值小于 a[k] 的元素数。
    for (int k = 1; k <= n; k++) {
        for (int j = 2; j < k; j++) {
            leftLess[j][k] = leftLess[j - 1][k];
            if (a[j - 1] < a[k]) {
                leftLess[j][k]++;
            }
        }
    }
    long long ans = 0;
    for (int j = 2; j <= n - 2; j++) {
        long long rightGreater = 0;
        for (int k = n; k > j; k--) {
            if (a[k] < a[j]) {
                ans += leftLess[j][k] * rightGreater;
            }
            // 更新放在计数之后，保证第四个位置严格大于 k。
            if (a[k] > a[j]) {
                rightGreater++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
```
