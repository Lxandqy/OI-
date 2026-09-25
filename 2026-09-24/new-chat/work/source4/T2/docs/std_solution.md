# 平方和 - 满分题解

## 关键观察

只需关心平方对 $k$ 的余数。若

$$a_i^2\bmod k=r,$$

那么另一项必须满足平方余数为

$$(k-r)\bmod k。$$

对于每一种平方余数，只保留数值最大的两个元素：不同余数组合只需要各自最大值；相同余数组合需要同组中的前两大值，以保证选择不同位置。

## 满分算法

使用哈希表记录每个平方余数对应的最大值和次大值。扫描所有余数组，查找互补余数并更新答案。

## 正确性说明

任意合法点对的两个平方余数之和模 $k$ 为 $0$。对于两个不同余数组，替换成各组最大值不会破坏余数条件且只会增大平方和；对于同一余数组，最优解显然由该组最大的两个位置构成。因此只保留前两大值不会遗漏答案。

## 复杂度分析

哈希表期望时间复杂度 $O(n)$，空间复杂度 $O(n)$。

## 边界与易错点

- 两个数字必须来自不同位置，因此同余数组要保存两个元素；
- 相同数值可以来自不同位置；
- 平方和最大可达 $2\times10^{18}$，必须使用 `long long`；
- 计算平方余数时使用 `__int128` 更稳妥。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + seed);
    }
};

void insertValue(pair<long long,long long> &p, long long x) {
    if (x > p.first) {
        p.second = p.first;
        p.first = x;
    } else if (x > p.second) {
        p.second = x;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    unordered_map<long long,pair<long long,long long>,CustomHash> best;
    best.reserve(n * 2 + 10);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        long long r = (long long)((__int128)x * x % k);
        auto &p = best[r];
        insertValue(p, x);
    }

    long long ans = -1;
    for (const auto &it : best) {
        long long r = it.first;
        long long s = (k - r) % k;
        auto jt = best.find(s);
        if (jt == best.end()) {
            continue;
        }
        if (r == s) {
            if (it.second.second > 0) {
                ans = max(ans, it.second.first * it.second.first + it.second.second * it.second.second);
            }
        } else {
            ans = max(ans, it.second.first * it.second.first + jt->second.first * jt->second.first);
        }
    }

    cout << ans << '\n';
    return 0;
}
```
