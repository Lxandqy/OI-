#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 45, maxm = (1 << 20) + 10;
const ll inf = 1ll << 62;
int n, cnt1, cnt2;
ll L, R, k, a[maxn], b[maxn];
struct Node {
    ll w, v;
} x[maxm], y[maxm];
multiset<ll> s;

bool cmp(Node a, Node b) { return a.w < b.w; }

void dfs(int i, int r, ll w, ll v, Node* p, int& cnt) {
    if (w > R) return;
    if (i > r) {
        p[++cnt] = {w, v};
        return;
    }
    dfs(i + 1, r, w, v, p, cnt);
    dfs(i + 1, r, w + a[i], v + b[i], p, cnt);
}

void solve() {
    cin >> n >> L >> R >> k;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    cnt1 = cnt2 = 0;
    s.clear();
    // 两部分都要枚举空集，整份方案是否合法由总重量判断。
    dfs(1, n / 2, 0, 0, x, cnt1);
    dfs(n / 2 + 1, n, 0, 0, y, cnt2);
    sort(x + 1, x + cnt1 + 1, cmp);
    sort(y + 1, y + cnt2 + 1, cmp);
    int l = 1, r = 1;
    ll ans = inf;
    for (int i = cnt1; i >= 1; i--) {
        // x 的重量递减，y 的合法重量区间整体向右移动。
        while (r <= cnt2 && y[r].w <= R - x[i].w) s.insert(y[r++].v);
        while (l < r && y[l].w < L - x[i].w) {
            // 相同总价可能来自不同子集，每次只删掉当前这一份。
            s.erase(s.find(y[l++].v));
        }
        auto it = s.lower_bound(k - x[i].v);
        if (it != s.end()) ans = min(ans, abs(x[i].v + *it - k));
        if (it != s.begin()) {
            it--;
            ans = min(ans, abs(x[i].v + *it - k));
        }
    }
    cout << (ans == inf ? -1 : ans) << '\n';
}

int main() {
    freopen("snack.in", "r", stdin);
    freopen("snack.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
