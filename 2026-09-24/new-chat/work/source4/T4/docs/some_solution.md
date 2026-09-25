# 表达式（eval） - 部分分题解

## 部分分总表

| 测试点 | 特殊限制 | 可行做法 | 分值 |
|---:|---|---|---:|
| $1\sim2$ | $|S|\le10$ | 枚举括号或区间 DP | $10$ |
| $3\sim6$ | 所有数不超过 $9$ | 单字符解析并按加法段计算 | $20$ |
| $7\sim10$ | 只有加法 | 求所有数之和 | $20$ |
| $11\sim12$ | 只有乘法 | 求所有数之积 | $10$ |
| $13\sim14$ | $|S|\le1000$ | 使用大整数线性解析 | $10$ |
| $15\sim20$ | 一般数据 | 完整大整数线性解析 | $30$ |

原题前 $14$ 个测试点由若干互相独立的特殊性质构成。最终交付程序识别小长度、小数字、单一运算符或 $|S|\le1000$ 的输入，再使用正确的大整数计算，实际获得 $70$ 分。

## 为什么不能通过全部数据

最后六个测试点同时包含加法和乘法、长度超过 $1000$，并含大于 $9$ 的多位整数，不满足任何部分分分支。

## 从部分分到满分

完整算法本身仍是“加法段求和后相乘”，只需取消对子任务性质的限制，并对所有长度不超过 $5000$ 的表达式统一使用任意精度整数。

## 最终交付的部分分程序

```cpp
#include<bits/stdc++.h>
#include<boost/multiprecision/cpp_int.hpp>
using namespace std;

boost::multiprecision::cpp_int readNumber(const string &s, int l, int r) {
    boost::multiprecision::cpp_int x = 0;
    for (int i = l; i < r; i++) {
        x = x * 10 + (s[i] - '0');
    }
    return x;
}

boost::multiprecision::cpp_int solveExpression(const string &s) {
    using boost::multiprecision::cpp_int;
    cpp_int product = 1;
    cpp_int currentSum = 0;
    int n = s.size();
    int i = 0;

    while (i < n) {
        int j = i;
        while (j < n && isdigit((unsigned char)s[j])) {
            j++;
        }
        currentSum += readNumber(s, i, j);
        if (j == n) {
            break;
        }
        if (s[j] == '*') {
            product *= currentSum;
            currentSum = 0;
        }
        i = j + 1;
    }
    return product * currentSum;
}

int main() {
    freopen("eval.in", "r", stdin);
    freopen("eval.out", "w", stdout);

    string s;
    cin >> s;

    bool allPlus = true;
    bool allMultiply = true;
    bool allSmall = true;
    int i = 0;
    while (i < (int)s.size()) {
        int j = i;
        boost::multiprecision::cpp_int value = 0;
        while (j < (int)s.size() && isdigit((unsigned char)s[j])) {
            value = value * 10 + (s[j] - '0');
            j++;
        }
        if (value > 9) {
            allSmall = false;
        }
        if (j < (int)s.size()) {
            if (s[j] != '+') allPlus = false;
            if (s[j] != '*') allMultiply = false;
        }
        i = j + 1;
    }

    // 覆盖原题测试点 1~14 的小长度、小数字、单一运算符等子任务。
    if ((int)s.size() <= 1000 || allSmall || allPlus || allMultiply) {
        cout << solveExpression(s) << '\n';
    } else {
        cout << 0 << '\n';
    }
    return 0;
}
```
