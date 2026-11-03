#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("stripe.in", "r", stdin);
    freopen("stripe.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;
        int white = 0, ans = k;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'W') white++;
            if (i >= k && s[i - k] == 'W') white--;
            if (i >= k - 1) ans = min(ans, white);
        }
        cout << ans << '\n';
    }
    return 0;
}
