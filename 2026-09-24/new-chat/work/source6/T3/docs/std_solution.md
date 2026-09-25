# T3 三元组

---

## 满分做法：拆分条件后排序计数

---

记 $A=a_i+a_j$、$B=b_i+b_j$，则条件可以拆成

$$2A\le B\quad\text{或}\quad2B\le A.$$

因为 $A,B>0$，两种情况不可能同时成立：如果同时成立，就会有 $4A\le2B\le A$，与 $A>0$ 矛盾。因此可以分别统计两种情况，然后相加。

先考虑 $2A\le B$。令 $x_i=2a_i-b_i$，条件就变成

$$x_i+x_j\le0.$$

把每个 $x_i$ 与它的权值 $c_i$ 一起按 $x_i$ 升序排序。设 $pre[t]$ 为排序后前 $t$ 个权值之和，对模数取模。

从左到右枚举位置 $l$，用 $r$ 表示最大的合法右端点。当 $x_l+x_r>0$ 时，就把 $r$ 向左移动。随着 $l$ 增大，$x_l$ 不会变小，所以 $r$ 只会左移。

若 $r\ge l$，与位置 $l$ 配对且排序后位置不小于 $l$ 的合法元素恰好是 $[l,r]$，本次贡献为

$$c_l\bigl(pre[r]-pre[l-1]\bigr).$$

区间包含 $j=l$，所以保留了自身配对；其余无序对只由排序后较靠左的位置统计一次。若 $r<l$，后面不再有合法对，可以结束。

再用 $x_i=2b_i-a_i$ 统计另一种情况，两次结果相加取模即可。前缀和相减时先加模数；键值、键值之和与乘积均使用 `long long`。

时间复杂度为 $O(n\log n)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
struct Node {
    long long key, weight;
};
Node p[100005];
long long a[100005], b[100005], c[100005], prefix[100005];
int n;

bool cmp(const Node &u, const Node &v) {
    return u.key < v.key;
}

long long calc() {
    sort(p + 1, p + n + 1, cmp);
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = (prefix[i - 1] + p[i].weight) % MOD;
    }
    long long result = 0;
    int r = n;
    for (int l = 1; l <= n; l++) {
        while (r >= l && p[l].key + p[r].key > 0) {
            r--;
        }
        if (r < l) {
            break;
        }
        // 区间 [l,r] 包含自身，恰好统计一次无序点对。
        long long sum = (prefix[r] - prefix[l - 1] + MOD) % MOD;
        result = (result + p[l].weight * sum) % MOD;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        p[i].key = 2 * a[i] - b[i];
        p[i].weight = c[i];
    }
    long long ans = calc();
    for (int i = 1; i <= n; i++) {
        p[i].key = 2 * b[i] - a[i];
        p[i].weight = c[i];
    }
    ans = (ans + calc()) % MOD;
    cout << ans << '\n';
    return 0;
}
```
