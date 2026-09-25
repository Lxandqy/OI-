#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
int best[405], dp[405], nextDp[405];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int r = 1; r < k; r++) {
        dp[r] = INF;
    }
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int length = (int)s.size();
        for (int r = 0; r < k; r++) {
            best[r] = INF;
            nextDp[r] = INF;
        }
        // 每个相邻数位间隙选切或不切，统计该数字的全部切法。
        for (int mask = 0; mask < (1 << (length - 1)); mask++) {
            int sum = 0, value = 0, cuts = 0;
            for (int j = 0; j < length; j++) {
                value = (value * 10 + s[j] - '0') % k;
                if (j == length - 1 || (mask & (1 << j)) != 0) {
                    sum = (sum + value) % k;
                    value = 0;
                    if (j != length - 1) {
                        cuts++;
                    }
                }
            }
            best[sum] = min(best[sum], cuts);
        }
        for (int r = 0; r < k; r++) {
            if (dp[r] == INF) {
                continue;
            }
            for (int t = 0; t < k; t++) {
                if (best[t] != INF) {
                    int next = (r + t) % k;
                    nextDp[next] = min(nextDp[next], dp[r] + best[t]);
                }
            }
        }
        for (int r = 0; r < k; r++) {
            dp[r] = nextDp[r];
        }
    }
    if (dp[0] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[0] << '\n';
    }
    return 0;
}
