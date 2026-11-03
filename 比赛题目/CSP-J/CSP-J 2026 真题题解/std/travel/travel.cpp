#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    string c1, s1, c2, s2;
    cin >> c1 >> s1 >> c2 >> s2;
    char x = s1[2], y = s2[2];
    bool b1 = (c1 == c2);
    bool b2 = b1 && s1.substr(0, 2) == s2.substr(0, 2);
    bool b3 = b2 && ((x <= 'C') == (y <= 'C'));
    if (x > y) swap(x, y);
    bool near = (x == 'A' && y == 'B')
             || (x == 'B' && y == 'C')
             || (x == 'D' && y == 'F');
    bool b4 = b3 && near;
    cout << b1 << b2 << b3 << b4 << '\n';
    return 0;
}
