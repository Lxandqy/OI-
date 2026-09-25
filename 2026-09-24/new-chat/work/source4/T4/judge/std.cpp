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
