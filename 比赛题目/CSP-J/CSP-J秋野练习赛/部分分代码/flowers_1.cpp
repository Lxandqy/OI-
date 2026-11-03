// 花束：部分分1；枚举颜色序列；t<=10且b<=16，点1-4保证20分；时间O(2^B+tB)，空间O(M+t)，M=100000。
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int a[100005], b[100005], ways[100005], k, len;
void dfs(int pos, int white) {
    if (pos == len) {
        if (white % k == 0) ways[len] = (ways[len] + 1) % MOD;
        return;
    }
    if (white % k == 0) dfs(pos + 1, 0);
    dfs(pos + 1, white + 1);
}

int main() {
    freopen("flowers.in", "r", stdin);
    freopen("flowers.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t >> k;
    int bmax = 0;
    for (int i = 1; i <= t; i++) {
        cin >> a[i] >> b[i];
        bmax = max(bmax, b[i]);
    }
    for (len = 1; len <= bmax; len++) dfs(0, 0);
    for (int i = 1; i <= t; i++) {
        int ans = 0;
        for (int j = a[i]; j <= b[i]; j++) ans = (ans + ways[j]) % MOD;
        cout << ans << '\n';
    }
    return 0;
}
