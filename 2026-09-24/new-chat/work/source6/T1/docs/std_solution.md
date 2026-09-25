# T1 最多求余

---

## 满分做法：计数后从小到大扫描

---

对 $k$ 取余的结果只可能在 $[0,k-1]$ 中。用 `cnt[r]` 记录余数 $r$ 的出现次数，读入每个数时执行 `cnt[a[i] % k]++`。

统计完成后，令 `ans=0`，按 $r=1,2,\ldots,k-1$ 的顺序检查各个余数。只有当 `cnt[r] > cnt[ans]` 时，才令 `ans=r`。

这样既能找到最大的出现次数，也能处理并列：由于从小到大扫描，次数相等时不更新，保留下来的就是最小余数。

注意余数 $0$ 也可能是答案；扫描上界取决于 $k$，而不是输入个数 $n$。例如 $n$ 很小、$k$ 很大时，获胜余数仍然可能大于 $n$。

时间复杂度为 $O(n+k)$，空间复杂度为 $O(k)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int cnt[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x % k]++;
    }
    int ans = 0;
    // 从小到大扫描；只有次数严格更多时才更新。
    for (int r = 1; r < k; r++) {
        if (cnt[r] > cnt[ans]) {
            ans = r;
        }
    }
    cout << ans << '\n';
    return 0;
}
```
