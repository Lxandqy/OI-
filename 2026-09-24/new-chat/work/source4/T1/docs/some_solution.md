# 接龙 - 部分分题解

## 部分分总表

| 分值 | 特殊限制 | 做法 | 复杂度 |
|---:|---|---|---|
| $20$ | $n\le100$ | 枚举所有牌对寻找最大重复值 | $O(n^2)$ |
| $20$ | 所有牌相同 | 直接输出 $a_1n$ | $O(n)$ |
| $30$ | $a_i\le1000$ | 小值域计数 | $O(n+1000)$ |
| $100$ | 无额外限制 | 完整值域计数 | $O(n+10^5)$ |

## 小规模枚举

枚举任意两张牌，只要数字相同就更新最大的可用端点数字。得到 $M$ 后仍然输出 $M\times n$。

## 全相等与小值域

全相等时显然可以一次收走全部牌。小值域时开一个大小为 $1001$ 的计数数组即可。

最终交付程序综合三类特殊输入，实际通过测试点 $1\sim7$，获得 $70$ 分。

## 为什么不能通过全部数据

一般数据可能同时满足 $n>100$、数值超过 $1000$ 且不全相等，部分分程序没有统计完整值域。

## 从部分分到满分

把计数数组扩展到题目给定的 $10^5$ 值域即可，核心上界与构造证明保持不变。

## 最终交付的部分分程序

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int mx = 0;
    bool allSame = true;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        if (i > 0 && a[i] != a[0]) {
            allSame = false;
        }
    }

    int best = 0;
    if (n <= 100) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i] == a[j]) {
                    best = max(best, a[i]);
                }
            }
        }
    } else if (allSame) {
        best = a[0];
    } else if (mx <= 1000) {
        vector<int> cnt(1001, 0);
        for (int x : a) {
            cnt[x]++;
        }
        for (int x = 1; x <= 1000; x++) {
            if (cnt[x] >= 2) {
                best = x;
            }
        }
    } else {
        cout << 0 << '\n';
        return 0;
    }

    cout << 1LL * best * n << '\n';
    return 0;
}
```
