// 喂猫：部分分1；枚举投喂时刻集合；总n<=14且总m<=20，点1-4保证20分；时间O(2^n m)，空间O(n+m)。
#include <bits/stdc++.h>
using namespace std;
int n, m, ans, l[200005], r[200005], pre[1000005];
void dfs(int i) {
    if (i > n) {
        int score = 0;
        for (int j = 1; j <= m; j++) {
            int v = pre[r[j]] - pre[l[j] - 1];
            if (v > 1) return;
            score += v;
        }
        ans = max(ans, score);
        return;
    }
    pre[i] = pre[i - 1];
    dfs(i + 1);
    pre[i] = pre[i - 1] + 1;
    dfs(i + 1);
}

int main() {
    freopen("cats.in", "r", stdin);
    freopen("cats.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int j = 1; j <= m; j++) cin >> l[j] >> r[j];
        ans = 0;
        pre[0] = 0;
        dfs(1);
        cout << ans << '\n';
    }
    return 0;
}
