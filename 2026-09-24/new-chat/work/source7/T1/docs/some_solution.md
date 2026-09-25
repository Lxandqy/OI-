# T1 回文串

---

## 部分分（30 分，$|s|\le3$）：枚举排列与子串

---

字符最多只有三个，可以直接尝试所有重排结果。

先把字符串排序，再用 `next_permutation` 依次生成不同排列。对每个排列，枚举非空区间 $[l,r]$，用两个指针从区间两端向中间检查字符是否相同。如果始终相同，这个区间就是一个回文子串。

统计每个排列的回文子串数，取最大值。单个字符也要统计；两个内容相同但位置不同的子串分别计数，不能去重。

设字符串长度为 $L$，不同排列数为 $P$，时间复杂度上界为 $O(PL^3)$，空间复杂度为 $O(L)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    int n = (int)s.size();
    long long ans = 0;
    do {
        long long count = 0;
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                bool ok = true;
                int i = l, j = r;
                while (i < j) {
                    if (s[i] != s[j]) {
                        ok = false;
                        break;
                    }
                    i++;
                    j--;
                }
                if (ok) {
                    count++;
                }
            }
        }
        ans = max(ans, count);
    } while (next_permutation(s.begin(), s.end()));
    cout << ans << '\n';
    return 0;
}
```
