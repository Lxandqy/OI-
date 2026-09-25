# T3 文件判定

---

以下三组特殊性质各独立占 20 分。

## 部分分（独立 20 分）：同时满足性质 1、2、3

---

根目录唯一且名称正确，所有名称都正确，目录只有三级。在这些保证下，每个题目对应一条“根目录到题目”的关系和一条“题目到代码文件”的关系，只需判断题目是否恰好有四个。

因此读完所有关系后，检查关系数 $n$ 是否等于 $8$ 即可。这个判断依赖本档的特殊保证；一般数据中，$8$ 条关系也可能有错误命名或错误层次。

设名称最大长度为 $L$，每组时间复杂度为 $O(nL)$，额外空间复杂度为 $O(L)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            string a, b;
            cin >> a >> b;
        }
        // 只适用于性质1、2、3同时成立的子任务。
        if (n == 8) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    return 0;
}
```

## 部分分（独立 20 分）：同时满足性质 1、3

---

本档保证根目录唯一且名称正确，并且只有三级，但题目名称、文件名称和数量仍可能有误。

先根据包含关系找到根，再检查它是否恰好有四个直接孩子。每个题目名称必须全是英文字母；每个题目恰好有一个孩子，并且孩子名称必须等于“题目名称 + `.cpp`”。同时要求总关系数为 $8$，排除多余条目。

这些检查覆盖了除根命名以外的所有规则，而根命名由题目保证，因此不需要再检查根名的字母、数字格式。

设名称最大长度为 $L$，每组时间复杂度为 $O(n^2L)$，空间复杂度为 $O(nL)$。

### 参考代码

完整代码见下文“部分分综合做法”。

## 部分分（独立 20 分）：满足性质 2

---

本档所有名称都符合要求，只可能在根目录个数或第二层目录个数上出错。因此先寻找根，要求根唯一，再确认它恰好包含四个题目。

下面的综合程序还会检查每题唯一的代码文件。对本档而言，这些名称和文件关系已经有保证，多做检查不会改变结果；而根数或题目数错误的输入仍会被拒绝。

设名称最大长度为 $L$，使用综合程序时，每组时间复杂度为 $O(n^2L)$，空间复杂度为 $O(nL)$。

### 参考代码

与上一档使用同一程序，完整代码见下文“部分分综合做法”。

## 部分分综合做法

---

三组特殊性质都保证根名称合法。因此可以共用一份程序：完整检查关系数、根的唯一性、题目数量、题目名和代码文件名，只省略根名称的格式检查。

找根时，检查一个出现在父项位置的名称是否曾作为子项出现。没有父亲的名称才是根候选；同一个根会出现在多条关系中，只能按名称算作一个候选。

题目顺序和输入行顺序没有关系，必须扫描全部关系。检查四个题目及各自的代码后，恰好使用全部八条关系，不能再有额外层次或文件。

设名称最大长度为 $L$，每组时间复杂度为 $O(n^2L)$，空间复杂度为 $O(nL)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string a[11], b[11];
int n;

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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
    // 部分分保证根名称合法；这里仅判断根是否存在。
    if (root == "") {
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
