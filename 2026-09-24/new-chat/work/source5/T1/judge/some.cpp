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

    // 该预处理范围覆盖年份不超过 4000 的累计 60% 数据。
    if (y > 4000) {
        cout << "0 0 0\n";
        return 0;
    }

    do {
        nextDay(y, m, d);
    } while (!palindromeDate(y, m, d));
    cout << y << ' ' << m << ' ' << d << '\n';
    return 0;
}
