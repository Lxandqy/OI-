// 整倍调整：部分分1；按时刻模拟；k<=30且总n<=100，点1-5保证25分；时间O(n^2 k)，空间O(n)。
#include <bits/stdc++.h>
using namespace std;
long long a[200005];
bool done[200005];

int main() {
    freopen("multiple.in", "r", stdin);
    freopen("multiple.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;
        int left = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            done[i] = (a[i] % k == 0);
            if (!done[i]) left++;
        }
        long long x = 0;
        while (left > 0) {
            for (int i = 1; i <= n; i++) {
                if (!done[i] && (a[i] + x) % k == 0) {
                    done[i] = true;
                    left--;
                    break;
                }
            }
            x++;
        }
        cout << x << '\n';
    }
    return 0;
}
