# T3 文件判定

时间限制：1 秒　空间限制：256 MB

## 题目描述

一次练习赛有四道题。选手的提交目录必须满足以下规则，请判断给出的全部文件关系是否合法。

1. 只有一个根目录。根目录名称由一段非空英文字母和一段非空数字依次连接而成，例如 `BJ01`；`123`、`ABC`、`A2B` 都不合法。
2. 根目录中恰好有四个题目文件夹，每个题目名称是非空的纯英文字母串。
3. 每个题目文件夹恰好包含一个条目，名称必须为“题目名称 + `.cpp`”，并且该条目不能再有子条目。
4. 大小写敏感。不能出现多余文件或多余目录。只判断名称和包含关系，不区分文件与文件夹的真实类型。

例如，合法目录可以是：

```text
BJ01
  apple / apple.cpp
  Banana / Banana.cpp
  candy / candy.cpp
  task / task.cpp
```

输入中的每条关系 $A\ B$ 表示 $B$ 是 $A$ 的直接子条目。关系不一定按目录层次顺序给出。

## 输入格式

第一行正整数 $t$，表示数据组数。

每组数据先给出正整数 $n$，表示关系条数。接下来 $n$ 行，每行两个字符串 $A,B$。

同一名称表示同一个条目，保证同名条目不会出现在目录的不同位置；给出的关系不重复，并且 $A\ne B$。

## 输出格式

每组输出一行 `yes` 或 `no`。

## 输入输出样例

### 样例 1

输入：

```text
5
2
BJ01 task
task task.cpp
8
task task.cpp
bJ01 task
bJ01 apple
apple apple.cpp
bJ01 Banana
Banana Banana.cpp
bJ01 candy
candy candy.cpp
8
123 task
task task.cpp
123 plane
plane plane.cpp
123 banana
banana banana.cpp
123 candy
candy candy.cpp
8
BJ01 task
task task.cpp
BJ01 apple
apple banana.cpp
BJ01 banana
banana apple.cpp
BJ01 candy
candy candy.cpp
8
BJ01 task
task task.cpp
BJ01 apple
apple apple.cpp
BJ01 banana
banana banana.cpp
BJ01 candy
candy candy.cpp.cpp
```

输出：

```text
no
yes
no
no
no
```

五组依次为：题目数量不足；合法；根名称没有字母；文件与题目名称不对应；扩展名重复。

## 数据范围与计分

$1\le t\le100$，每组 $1\le n\le10$。每个名称长度为 $1\sim20$，只可能包含英文字母、数字以及 `- . ( )`。各行独立计分。

性质 1：根目录唯一且其名称符合规则。

性质 2：所有条目的名称均符合对应要求，只可能在根目录个数或第二级目录个数上出错。

性质 3：目录的最大层数恰好为三级。

每个测试点 10 分，共 10 个测试点，总分 100 分。

| 测试点 | 本组分值 | 额外限制 |
| --- | --- | --- |
| 1～2 | 20 | 同时满足性质 1、2、3 |
| 3～4 | 20 | 同时满足性质 1、3 |
| 5～6 | 20 | 满足性质 2 |
| 7～10 | 40 | 无额外性质 |

## 公开附件

同级 `attachment.zip` 中提供公开的大样例及对应输出；公开样例和附件均不计分。
