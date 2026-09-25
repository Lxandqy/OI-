# T1 最多求余

---

## 部分分（累计 20 分）：所有余数相同

---

所有数对 $k$ 取余后都相同，因此答案就是 $a_1\bmod k$。保存第一个数的余数，读完其余输入后输出即可。

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k, a;
    cin >> n >> k;
    cin >> a;
    int ans = a % k;
    for (int i = 2; i <= n; i++) {
        cin >> a;
    }
    cout << ans << '\n';
    return 0;
}
```

## 部分分（累计 60 分）：出现次数两两不同

---

用 `cnt[r]` 记录余数 $r$ 已经出现的次数。每读入一个数，就增加对应计数；如果新次数严格超过当前记录的最大次数，就更新答案。

本档保证实际出现的各余数频数两两不同，所以最终出现最多的余数是唯一的。当它最后一次出现时，其计数一定超过其他余数的最终计数，答案就会被更新为它。

这里没有处理并列：如果两种余数最终次数相同，较大的余数可能更早达到该次数，从而被保留下来。

时间复杂度为 $O(n)$，空间复杂度为 $O(k)$。

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
    int ans = 0, best = 0;
    // 本程序适用于最高出现次数唯一的情况，不处理并列最优。
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        int r = x % k;
        cnt[r]++;
        if (cnt[r] > best) {
            best = cnt[r];
            ans = r;
        }
    }
    cout << ans << '\n';
    return 0;
}
```
