# T3 三元组

---

## 部分分（累计 20 分）：小规模直接枚举

---

本档 $n\le1000$，并且取模前的总价值小于 $10^9+7$。直接枚举 $i=1,\ldots,n$ 和 $j=i,\ldots,n$，计算 $A=a_i+a_j$、$B=b_i+b_j$。

如果 $2\min(A,B)\le\max(A,B)$，就把 $c_ic_j$ 加入答案。$j$ 从 $i$ 开始，既保留了自身配对，也不会把 $(i,j)$ 和 $(j,i)$ 重复计算。

总价值已保证小于模数，因此无需取模；但坐标相加、乘二及权值相乘仍要使用 `long long`。

时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
long long a[100005], b[100005], c[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        // j 从 i 开始：允许选择同一个三元组两次。
        for (int j = i; j <= n; j++) {
            long long x = a[i] + a[j];
            long long y = b[i] + b[j];
            if (2 * min(x, y) <= max(x, y)) {
                ans += c[i] * c[j];
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
```

## 部分分（累计 40 分，$n\le1000$）：枚举并取模

---

枚举方式与上一档相同，但总价值不再有较小上界。每得到一个合法贡献，就对答案取模：

$$ans=(ans+c_ic_j)\bmod(10^9+7).$$

加法和乘法可以逐步取模，不必先保存完整总和。单个乘积仍使用 `long long`，避免在取模前溢出。

时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
long long a[100005], b[100005], c[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        // j 从 i 开始：允许选择同一个三元组两次。
        for (int j = i; j <= n; j++) {
            long long x = a[i] + a[j];
            long long y = b[i] + b[j];
            if (2 * min(x, y) <= max(x, y)) {
                ans = (ans + c[i] * c[j]) % MOD;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
```
