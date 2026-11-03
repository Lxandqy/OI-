// 染色条：部分分1；逐窗口计数；总n<=2000，点1-6保证30分；时间O(nk)，空间O(n)。
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
        int ans = k;
        for (int l = 0; l + k <= n; l++) {
            int count = 0;
            for (int j = l; j < l + k; j++) count += (s[j] == 'W');
            ans = min(ans, count);
            if (ans == 0) break;
        }
        cout << ans << '\n';
    }
    return 0;
}
