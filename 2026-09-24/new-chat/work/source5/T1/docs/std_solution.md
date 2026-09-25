# 上下五千年 - 满分题解

## 题意整理

从输入日期的后一天开始，依次寻找第一个合法且“年月日无前导零连接串”为回文串的日期。

## 满分算法

实现公历日期加一：

1. 日期增加 $1$；
2. 超过当月天数时进入下个月；
3. 月份超过 $12$ 时进入下一年；
4. 将 `year`、`month`、`day` 用 `to_string` 连接，判断是否回文。

找到第一个回文日期后输出。

## 正确性说明

算法从输入日期的严格后继开始，按照时间先后顺序逐日检查。所有检查日期均合法；第一个通过回文判断的日期显然是严格晚于输入的最早回文时间。

## 复杂度分析

设答案与输入相差 $D$ 天，时间复杂度为 $O(D)$，空间复杂度为 $O(1)$。在给定年份范围内，实际需要检查的日期数量很小。

## 边界与易错点

- 若输入本身是回文时间，仍然必须寻找下一个；
- 月和日不能补成两位；
- 世纪年必须能被 $400$ 整除才是闰年；
- 输出年份可能略大于 $7000$，因为限制只约束输入日期。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool leap(int y) {
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int days(int y, int m) {
    static int d[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) {
        return d[m] + leap(y);
    }
    return d[m];
}

void nextDay(int &y, int &m, int &d) {
    d++;
    if (d > days(y, m)) {
        d = 1;
        m++;
    }
    if (m > 12) {
        m = 1;
        y++;
    }
}

bool palindromeDate(int y, int m, int d) {
    string s = to_string(y) + to_string(m) + to_string(d);
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int y, m, d;
    cin >> y >> m >> d;
    do {
        nextDay(y, m, d);
    } while (!palindromeDate(y, m, d));

    cout << y << ' ' << m << ' ' << d << '\n';
    return 0;
}
```
