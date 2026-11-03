// 花束：部分分3；共用递推并逐问求和；宽度<=10或前两档，点1-12保证60分；时间O(M+总宽度)，空间O(M)。
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
    f[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        f[i] = f[i - 1];
        if (i >= k) f[i] = (f[i] + f[i - k]) % MOD;
    }
    while (t--) {
        int a, b, ans = 0;
        cin >> a >> b;
        for (int i = a; i <= b; i++) ans = (ans + f[i]) % MOD;
        cout << ans << '\n';
    }
    return 0;
}
