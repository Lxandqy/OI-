#include <bits/stdc++.h>
using namespace std;
long long need[200005];

int main() {
    freopen("multiple.in", "r", stdin);
    freopen("multiple.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k, x;
        cin >> n >> k;
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            long long r = (k - x % k) % k;
            if (r != 0) need[++cnt] = r;
        }
        sort(need + 1, need + cnt + 1);
        long long ans = 0;
        for (int l = 1; l <= cnt; ) {
            int r = l;
            while (r <= cnt && need[r] == need[l]) r++;
            long long times = r - l;
            ans = max(ans, need[l] + (times - 1) * k + 1);
            l = r;
        }
        cout << ans << '\n';
    }
    return 0;
}
