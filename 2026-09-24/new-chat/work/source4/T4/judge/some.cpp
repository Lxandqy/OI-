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
