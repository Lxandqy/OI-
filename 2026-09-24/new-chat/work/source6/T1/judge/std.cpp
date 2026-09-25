#include <bits/stdc++.h>
using namespace std;

int cnt[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x % k]++;
    }
    int ans = 0;
    // 从小到大扫描；只有次数严格更多时才更新。
    for (int r = 1; r < k; r++) {
        if (cnt[r] > cnt[ans]) {
            ans = r;
        }
    }
    cout << ans << '\n';
    return 0;
}
