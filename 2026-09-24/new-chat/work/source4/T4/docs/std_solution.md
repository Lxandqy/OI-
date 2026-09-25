# 表达式（eval） - 满分题解

## 关键观察

把表达式按照乘号 `*` 分成若干段，每一段内部全部由加号连接。由于所有数都是正数，利用分配律，把每一段的和作为一个乘法因子，能让跨越加号两侧的正数尽可能相乘。

例如

```text
2*3+4*5+6
```

最大值为

$2\times(3+4)\times(5+6)$。

因此答案就是：**每个最大加法段先求和，再把所有段的和相乘。**

## 正确性说明

考虑表达式中的任意一个乘号。通过在它两侧不断应用分配律，乘号能够与相邻加法段中的所有正项相乘；正数条件保证增加这些乘法组合不会使结果变小。最终可得到所有由乘号分隔的最大加法段之和的乘积。反过来，这个式子可以通过合法添加括号实现，因此既是上界也是可达值。

## 满分算法

线性解析每个正整数：遇到 `+` 就继续累加当前段，遇到 `*` 就把当前段和乘入答案并清零。使用 `boost::multiprecision::cpp_int` 保存任意精度整数。

## 复杂度分析

忽略大整数位运算代价，扫描复杂度为 $O(|S|)$，空间复杂度与答案位数同阶。

## 边界与易错点

- 不能使用 `long long` 保存输入数字或答案；
- 连续解析多位整数时不能按单个字符处理；
- 最后一段需要在循环结束后乘入；
- 原样例解释中的 `9876` 是笔误，应为 `9867`。

## 参考代码

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
    cout << solveExpression(s) << '\n';
    return 0;
}
```
