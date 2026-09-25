# 绿野仙踪（green） - 满分题解

## 关键观察

随着 $r$ 增大，每个花圃覆盖范围只会扩大，场地中的可行道路只会减少。因此“半径 $r$ 是否可行”具有单调性，可以二分最大可行 $r$。

对固定 $r$，每个花圃对应一个经过边界裁剪的矩形。使用二维差分，可以在 $O(k+nm)$ 时间内求出所有被至少一个花圃覆盖的方格。

## 满分算法

1. 二分 $r$；
2. 对每个中心向二维差分数组加入覆盖矩形；
3. 前缀还原阻塞方格，并统计并集面积；
4. 若起点或终点被阻塞则不可行；
5. 在未阻塞方格中进行四方向 BFS，判断终点是否可达；
6. 对最大可行 $r$ 再计算一次覆盖面积。

内部把 $r=0$ 作为“没有花圃”的二分下界，因此无正整数方案时面积为 $0$。

## 正确性说明

二维差分精确标记了所有花圃矩形的并集；BFS 精确判断四联通路径。由于覆盖集合随 $r$ 单调扩大，可行性单调不增，二分得到最大的可行 $r$。同一中心的覆盖范围随 $r$ 增大，因此最大可行 $r$ 也使并集面积最大。

## 复杂度分析

每次检查为 $O(nm+k)$，二分次数为 $O(\log\max(n,m))$。总时间复杂度

$$O((nm+k)\log\max(n,m)),$$

空间复杂度 $O(nm+k)$。

## 边界与易错点

- 花圃越界部分需要裁剪；
- 重叠位置只能计算一次；
- 起点和终点不能被覆盖；
- 路径使用上下左右四个方向；
- 可能不存在任何正整数 $r$，此时输出 $0$。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Solver {
    int n, m, k;
    int sx, sy, ex, ey;
    vector<pair<int,int>> center;

    bool check(int r, long long *area = nullptr) {
        if (r == 0) {
            if (area) *area = 0;
            return true;
        }

        int w = m + 1;
        vector<int> diff((n + 1) * (m + 1), 0);
        auto addRect = [&](int x1, int y1, int x2, int y2) {
            diff[x1 * w + y1]++;
            diff[(x2 + 1) * w + y1]--;
            diff[x1 * w + (y2 + 1)]--;
            diff[(x2 + 1) * w + (y2 + 1)]++;
        };

        for (const auto &p : center) {
            int x = p.first;
            int y = p.second;
            int x1 = max(0, x - r + 1);
            int x2 = min(n - 1, x + r - 1);
            int y1 = max(0, y - r + 1);
            int y2 = min(m - 1, y + r - 1);
            addRect(x1, y1, x2, y2);
        }

        vector<unsigned char> blocked(n * m, 0);
        long long cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int id = i * w + j;
                if (i > 0) diff[id] += diff[(i - 1) * w + j];
                if (j > 0) diff[id] += diff[i * w + j - 1];
                if (i > 0 && j > 0) diff[id] -= diff[(i - 1) * w + j - 1];
                if (diff[id] > 0) {
                    blocked[i * m + j] = 1;
                    cnt++;
                }
            }
        }
        if (area) *area = cnt;

        int start = sx * m + sy;
        int target = ex * m + ey;
        if (blocked[start] || blocked[target]) {
            return false;
        }

        vector<unsigned char> vis(n * m, 0);
        vector<int> q(n * m);
        int head = 0, tail = 0;
        q[tail++] = start;
        vis[start] = 1;
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};

        while (head < tail) {
            int id = q[head++];
            if (id == target) {
                return true;
            }
            int x = id / m;
            int y = id % m;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                int nid = nx * m + ny;
                if (!blocked[nid] && !vis[nid]) {
                    vis[nid] = 1;
                    q[tail++] = nid;
                }
            }
        }
        return false;
    }

    long long solve() {
        int lo = 0;
        int hi = max(n, m) + 2;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (check(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        long long area = 0;
        check(lo, &area);
        return area;
    }
};

int main() {
    freopen("green.in", "r", stdin);
    freopen("green.out", "w", stdout);

    Solver solver;
    cin >> solver.n >> solver.m >> solver.k;
    cin >> solver.sx >> solver.sy;
    cin >> solver.ex >> solver.ey;
    solver.center.resize(solver.k);
    for (auto &p : solver.center) {
        cin >> p.first >> p.second;
    }
    cout << solver.solve() << '\n';
    return 0;
}
```
