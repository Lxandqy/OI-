# 平方和 - 部分分题解

## 部分分总表

| 分值 | 特殊限制 | 做法 | 复杂度 |
|---:|---|---|---|
| $20$ | $n\le2000$ | 枚举所有点对 | $O(n^2)$ |
| $30$ | $k\le10^5$ | 用数组按平方余数分组 | $O(n+k)$ |
| $100$ | 无额外限制 | 用哈希表保存出现过的余数 | 期望 $O(n)$ |

## 小规模枚举

枚举 $i<j$，直接判断平方和是否能被 $k$ 整除。

## 小模数

当 $k\le10^5$ 时，可以开长度为 $k$ 的数组，为每种平方余数保存最大的两个数字。

最终交付程序组合这两种做法，实际通过测试点 $1\sim5$，获得 $50$ 分。

## 为什么不能通过全部数据

一般数据中 $n$ 很大且 $k$ 可达 $10^9$：无法枚举点对，也不能开长度为 $k$ 的数组。

## 从部分分到满分

只为实际出现过的平方余数建立哈希表，就把空间从 $O(k)$ 降为 $O(n)$。

## 最终交付的部分分程序

```cpp
#include<bits/stdc++.h>
using namespace std;

long long brute(const vector<long long> &a, long long k) {
    long long ans = -1;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long value = a[i] * a[i] + a[j] * a[j];
            if (value % k == 0) {
                ans = max(ans, value);
            }
        }
    }
    return ans;
}

long long smallK(const vector<long long> &a, int k) {
    vector<pair<long long,long long>> best(k, {0, 0});
    for (long long x : a) {
        int r = (long long)((__int128)x * x % k);
        if (x > best[r].first) {
            best[r].second = best[r].first;
            best[r].first = x;
        } else if (x > best[r].second) {
            best[r].second = x;
        }
    }
    long long ans = -1;
    for (int r = 0; r < k; r++) {
        int s = (k - r) % k;
        if (r == s) {
            if (best[r].second > 0) {
                ans = max(ans, best[r].first * best[r].first + best[r].second * best[r].second);
            }
        } else if (best[r].first > 0 && best[s].first > 0) {
            ans = max(ans, best[r].first * best[r].first + best[s].first * best[s].first);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long &x : a) {
        cin >> x;
    }

    if (n <= 2000) {
        cout << brute(a, k) << '\n';
    } else if (k <= 100000) {
        cout << smallK(a, (int)k) << '\n';
    } else {
        cout << -1 << '\n';
    }
    return 0;
}
```
