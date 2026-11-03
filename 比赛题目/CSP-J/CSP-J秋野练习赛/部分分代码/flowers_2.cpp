// 花束：部分分2；每问重做递推；t<=500且b<=500，点1-8保证40分；时间O(tB)，空间O(M)，M=100000。
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int f[100005];

int main() {
    freopen("flowers.in", "r", stdin);
    freopen("flowers.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, k;
    cin >> t >> k;
    while (t--) {
        int a, b;
        cin >> a >> b;
        f[0] = 1;
        int ans = 0;
        for (int i = 1; i <= b; i++) {
            f[i] = f[i - 1];
            if (i >= k) f[i] = (f[i] + f[i - k]) % MOD;
            if (i >= a) ans = (ans + f[i]) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
