# T2 交错四元组

---

## 部分分（累计 20 分，$n\le20$）：四重枚举

---

按下标递增枚举 $i<j<k<l$，然后检查

$$a_i<a_k<a_j<a_l.$$

满足条件就把答案加一。四个位置的顺序和四个数的大小顺序不同，尤其是中间两项要求 $a_k<a_j$。所有数值比较都必须严格，相等时不能计入。

时间复杂度为 $O(n^4)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2005];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                for (int l = k + 1; l <= n; l++) {
                    if (a[i] < a[k] && a[k] < a[j] && a[j] < a[l]) {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
```

## 部分分（累计 50 分，$n\le300$）：预处理右端点

---

固定第二个位置 $j$。对于第三个位置 $k$，最后一个位置只需满足 $l>k$ 且 $a_l>a_j$，因此可以提前统计它的数量。

从右向左计算 `greaterRight[k]`，表示 $k$ 右侧大于 $a_j$ 的元素个数：

$$greaterRight[k]=greaterRight[k+1]+[a_{k+1}>a_j].$$

方括号表示条件成立时取 $1$，否则取 $0$。

接着枚举 $i<j$ 和 $k>j$。只要 $a_i<a_k<a_j$，就将 `greaterRight[k]` 加入答案，不再逐个枚举 $l$。每个前三位置对应的合法右端点都被一次计入，因此与四重枚举得到的结果相同。

时间复杂度为 $O(n^3)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[2005], greaterRight[2005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int j = 2; j <= n - 2; j++) {
        greaterRight[n] = 0;
        for (int k = n - 1; k > j; k--) {
            greaterRight[k] = greaterRight[k + 1];
            if (a[k + 1] > a[j]) {
                greaterRight[k]++;
            }
        }
        for (int i = 1; i < j; i++) {
            for (int k = j + 1; k < n; k++) {
                if (a[i] < a[k] && a[k] < a[j]) {
                    ans += greaterRight[k];
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
```
