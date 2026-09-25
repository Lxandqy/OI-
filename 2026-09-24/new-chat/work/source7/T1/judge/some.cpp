#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    int n = (int)s.size();
    long long ans = 0;
    do {
        long long count = 0;
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                bool ok = true;
                int i = l, j = r;
                while (i < j) {
                    if (s[i] != s[j]) {
                        ok = false;
                        break;
                    }
                    i++;
                    j--;
                }
                if (ok) {
                    count++;
                }
            }
        }
        ans = max(ans, count);
    } while (next_permutation(s.begin(), s.end()));
    cout << ans << '\n';
    return 0;
}
