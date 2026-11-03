// 整倍调整：部分分2；两两统计需求余数；总n<=2000，点1-10保证50分；时间O(n^2)，空间O(n)。
#include <bits/stdc++.h>
using namespace std;
long long need[200005];

int main() {
    freopen("multiple.in", "r", stdin);
    freopen("multiple.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k, x;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            need[i] = (k - x % k) % k;
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (need[i] == 0) continue;
            int count = 0;
            for (int j = 1; j <= n; j++) count += (need[i] == need[j]);
            ans = max(ans, need[i] + (count - 1LL) * k + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
