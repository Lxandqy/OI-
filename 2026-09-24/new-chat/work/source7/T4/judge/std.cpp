#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int parentNode[100005], orderNode[100005], leaf[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            parentNode[i] = 0;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        // 先记录父亲在前的遍历顺序，避免长链递归爆栈。
        int count = 1;
        orderNode[1] = 1;
        for (int i = 1; i <= count; i++) {
            int u = orderNode[i];
            leaf[u] = 0;
            if (g[u].size() == 1) {
                leaf[u] = 1;
            }
            for (int j = 0; j < (int)g[u].size(); j++) {
                int v = g[u][j];
                if (v != parentNode[u]) {
                    parentNode[v] = u;
                    orderNode[++count] = v;
                }
            }
        }
        // leaf[u] 只统计原树中度为 1 的叶子。
        for (int i = n; i >= 2; i--) {
            int u = orderNode[i];
            leaf[parentNode[u]] += leaf[u];
        }
        int ans = n, ways = 0;
        for (int v = 2; v <= n; v++) {
            int u = parentNode[v];
            int left = leaf[v];
            int right = leaf[1] - leaf[v];
            if (g[v].size() == 2) {
                left++;
            }
            if (g[u].size() == 2) {
                right++;
            }
            int difference = abs(left - right);
            if (difference < ans) {
                ans = difference;
                ways = 1;
            } else if (difference == ans) {
                ways++;
            }
        }
        cout << ans << ' ' << ways << '\n';
    }
    return 0;
}
