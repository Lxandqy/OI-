// 喂猫：部分分2；每时刻扫描全部猫；总n,m<=2000，点1-8保证40分；时间O(nm)，空间O(n+m)。
#include <bits/stdc++.h>
using namespace std;
int l[200005], r[200005], f[1000005];

int main() {
    freopen("cats.in", "r", stdin);
    freopen("cats.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int j = 1; j <= m; j++) cin >> l[j] >> r[j];
        f[0] = 0;
        for (int i = 1; i <= n; i++) {
            int count = 0, first = i;
            for (int j = 1; j <= m; j++) {
                if (l[j] <= i && i <= r[j]) {
                    count++;
                    first = min(first, l[j]);
                }
            }
            f[i] = max(f[i - 1], f[first - 1] + count);
        }
        cout << f[n] << '\n';
    }
    return 0;
}
