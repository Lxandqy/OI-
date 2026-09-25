#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
long long a[100005], b[100005], c[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        // j 从 i 开始：允许选择同一个三元组两次。
        for (int j = i; j <= n; j++) {
            long long x = a[i] + a[j];
            long long y = b[i] + b[j];
            if (2 * min(x, y) <= max(x, y)) {
                ans = (ans + c[i] * c[j]) % MOD;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
