#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<int> w(n);
    vector<long long> v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
        v[i] -= k;
    }

    if (n <= 20) {
        long long ans = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            int sumW = 0;
            long long sumV = 0;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    sumW += w[i];
                    sumV += v[i];
                }
            }
            if (sumW <= m) {
                ans = max(ans, sumV);
            }
        }
        cout << ans << '\n';
        return 0;
    }

    if (m <= 300) {
        // 使用二维 0/1 背包，便于初学者理解“前 i 个物品”的含义。
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= w[i - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
                }
            }
        }
        cout << *max_element(dp[n].begin(), dp[n].end()) << '\n';
        return 0;
    }

    cout << 0 << '\n';
    return 0;
}
