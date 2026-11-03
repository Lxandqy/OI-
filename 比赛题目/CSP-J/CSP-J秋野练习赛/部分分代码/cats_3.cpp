// 喂猫：部分分3；逐区间展开；区间长度<=5或前两档，点1-12保证60分；时间O(n+区间总长)，空间O(n+m)。
#include <bits/stdc++.h>
using namespace std;
int l[200005], r[200005], f[1000005], num[1000005], first[1000005];

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
        for (int i = 0; i <= n; i++) {
            f[i] = 0;
            num[i] = 0;
            first[i] = i;
        }
        for (int j = 1; j <= m; j++) {
            for (int i = l[j]; i <= r[j]; i++) {
                num[i]++;
                first[i] = min(first[i], l[j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            f[i] = max(f[i - 1], f[first[i] - 1] + num[i]);
        }
        cout << f[n] << '\n';
    }
    return 0;
}
