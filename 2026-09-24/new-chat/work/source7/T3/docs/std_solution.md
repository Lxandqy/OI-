# T3 文件判定

---

## 满分做法：逐项核对名称与包含关系

---

合法目录一定有四条“根目录到题目”的关系和四条“题目到代码文件”的关系，总共八条。因此如果 $n\ne8$，可以直接判断为不合法；$n=8$ 时还要继续检查具体内容。

用两个字符串数组保存每条关系的父项和子项。对每个出现过的父项，扫描所有子项名称：如果它从未作为子项出现，就是一个根候选。根必须存在，而且所有根候选必须是同一个名称。不能把第一行的父项直接当作根，因为输入顺序任意。

根名称分两段检查：先读一段非空英文字母，再读一段非空数字；字母和数字都不能缺少，进入数字部分后也不能再出现字母。例如 `BJ01` 合法，`123`、`ABC`、`A2B` 都不合法。

随后扫描根的直接孩子，要求恰好四个，并逐一检查：题目名称是非空纯字母串；题目恰好有一个孩子；孩子名称逐字符等于“题目名称 + `.cpp`”。大小写必须一致，只检查扩展名是不够的。

为什么不用继续检查第四层？四个题目及各自的代码文件已经占满八条关系。输入关系不重复，同名条目又不会位于不同位置；当上述检查全部通过时，所有关系都已用完，不可能再有多余孩子或游离条目。

每组最多十条关系，直接扫描即可，不需要额外建立复杂树结构。设名称最大长度为 $L$，每组时间复杂度为 $O(n^2L)$，空间复杂度为 $O(nL)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string a[11], b[11];
int n;

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool rootNameOK(const string &s) {
    int i = 0;
    while (i < (int)s.size() && isLetter(s[i])) {
        i++;
    }
    if (i == 0 || i == (int)s.size()) {
        return false;
    }
    while (i < (int)s.size()) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
        i++;
    }
    return true;
}

bool check() {
    if (n != 8) {
        return false;
    }
    string root = "";
    for (int i = 1; i <= n; i++) {
        bool hasParent = false;
        for (int j = 1; j <= n; j++) {
            if (a[i] == b[j]) {
                hasParent = true;
            }
        }
        if (!hasParent) {
            if (root != "" && root != a[i]) {
                return false;
            }
            root = a[i];
        }
    }
    if (!rootNameOK(root)) {
        return false;
    }
    int tasks = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] != root) {
            continue;
        }
        tasks++;
        string task = b[i];
        for (int j = 0; j < (int)task.size(); j++) {
            if (!isLetter(task[j])) {
                return false;
            }
        }
        int files = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j] == task) {
                files++;
                if (b[j] != task + ".cpp") {
                    return false;
                }
            }
        }
        if (files != 1) {
            return false;
        }
    }
    // 四条根边 + 四条代码文件边已经占满全部八条关系。
    return tasks == 4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i] >> b[i];
        }
        if (check()) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    return 0;
}
```
