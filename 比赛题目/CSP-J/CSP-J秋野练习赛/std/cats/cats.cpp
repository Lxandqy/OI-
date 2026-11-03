#include <bits/stdc++.h>
using namespace std;
int diff[1000005], last[1000005], f[1000005];

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
        for (int i = 0; i <= n + 1; i++) {
            f[i] = 0;
            last[i] = 0;
            diff[i] = 0;
        }
        for (int i = 1; i <= m; i++) {
            int l, r;
            cin >> l >> r;
            diff[l]++;
            diff[r + 1]--;
            last[l] = max(last[l], r);
        }
        int p = 1, count = 0;
        for (int i = 1; i <= n; i++) {
            count += diff[i];
            while (p <= i && last[p] < i) p++;
            f[i] = f[i - 1];
            if (count > 0) f[i] = max(f[i], f[p - 1] + count);
        }
        cout << f[n] << '\n';
    }
    return 0;
}
