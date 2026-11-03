#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int f[100005], pre[100005];

int main() {
    freopen("flowers.in", "r", stdin);
    freopen("flowers.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, k;
    cin >> t >> k;
    f[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        f[i] = f[i - 1];
        if (i >= k) f[i] = (f[i] + f[i - k]) % MOD;
        pre[i] = (pre[i - 1] + f[i]) % MOD;
    }
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << (pre[b] - pre[a - 1] + MOD) % MOD << '\n';
    }
    return 0;
}
