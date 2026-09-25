#include <bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 60);
int n, x, a[100005], b[11];
long long leftBest[100005], rightBest[100005], ans = NEG;

// 其余情况枚举所选下标；没有故意输出错误值的范围判断。
void dfs(int start, int chosen, long long sum) {
    if (chosen == x) {
        ans = max(ans, sum);
        return;
    }
    for (int i = start; i <= n - (x - chosen) + 1; i++) {
        dfs(i + 1, chosen + 1, sum + 1LL * a[i] * b[chosen + 1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= x; j++) {
        cin >> b[j];
    }
    leftBest[0] = NEG;
    for (int i = 1; i <= n; i++) {
        leftBest[i] = max(leftBest[i - 1], 1LL * a[i] * b[1]);
    }
    if (x == 1) {
        ans = leftBest[n];
    } else if (x == 2) {
        for (int j = 2; j <= n; j++) {
            ans = max(ans, leftBest[j - 1] + 1LL * a[j] * b[2]);
        }
    } else if (x == 3) {
        rightBest[n + 1] = NEG;
        for (int i = n; i >= 1; i--) {
            rightBest[i] = max(rightBest[i + 1], 1LL * a[i] * b[3]);
        }
        for (int j = 2; j < n; j++) {
            ans = max(ans, leftBest[j - 1] + 1LL * a[j] * b[2] + rightBest[j + 1]);
        }
    } else {
        dfs(1, 0, 0);
    }
    cout << ans << '\n';
    return 0;
}
