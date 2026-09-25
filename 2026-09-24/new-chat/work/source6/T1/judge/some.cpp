#include <bits/stdc++.h>
using namespace std;

int cnt[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int ans = 0, best = 0;
    // 本程序适用于最高出现次数唯一的情况，不处理并列最优。
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        int r = x % k;
        cnt[r]++;
        if (cnt[r] > best) {
            best = cnt[r];
            ans = r;
        }
    }
    cout << ans << '\n';
    return 0;
}
