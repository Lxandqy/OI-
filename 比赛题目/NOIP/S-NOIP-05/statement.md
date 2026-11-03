# 10.4友谊赛

第 05 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 花展 | 丝带 | 书架 | 菜单 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | bloom | ribbon | shelf | menu |
| 可执行文件名 | bloom | ribbon | shelf | menu |
| 输入文件名 | bloom.in | ribbon.in | shelf.in | menu.in |
| 输出文件名 | bloom.out | ribbon.out | shelf.out | menu.out |
| 每个测试点时限 | 1 秒 | 2 秒 | 2 秒 | 2 秒 |
| 内存限制 | 256 MiB | 256 MiB | 256 MiB | 256 MiB |
| 测试点数目 | 20 | 20 | 20 | 20 |
| 测试点是否等分 | 是（每点 5 分） | 是（每点 5 分） | 是（每点 5 分） | 是（每点 5 分） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | bloom.cpp | ribbon.cpp | shelf.cpp | menu.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 各测试点独立计分。含多组数据的测试点，须答对该点内的全部数据才能得分。

# 花展（bloom）

## 【题目描述】

小镇的花店要办一场小小的花展。纱路负责准备花束，千夜则在甘兔庵门口收集了大家方便前来的日期。

为了让更多人看到花展，她们决定开放两场。小镇的日历从第 $0$ 天记到第 $H$ 天，两场的日期分别为 $x$ 和 $x+d$，其中 $x$ 是整数，且 $0\le x\le H-d$。当 $d=0$ 时，两场在同一天举行。

一共有 $n$ 份预约。第 $i$ 份预约对应 $w_i$ 位客人，他们可以在第 $l_i$ 天到第 $r_i$ 天之间的任意一天前来，两个端点都包含在内。不同预约中的客人互不相同。

只要 $x$ 或 $x+d$ 中至少有一个落在 $[l_i,r_i]$ 内，这份预约中的 $w_i$ 位客人就都能参加。即使两场都合适，这份预约也只计算一次。

请你求出最多能让多少位客人参加，以及有多少个不同的整数 $x$ 能达到这个人数。

## 【输入格式】

从文件 `bloom.in` 读入数据。

第一行包含一个整数 $T$，表示数据组数。每组数据的格式如下：

第一行包含三个整数 $n,H,d$。

接下来 $n$ 行，每行包含三个整数 $l_i,r_i,w_i$，表示一份预约。

## 【输出格式】

输出到文件 `bloom.out`。

每组数据输出一行两个整数，依次表示最多参加人数、达到该人数的整数 $x$ 的个数。

## 【样例 1 输入】

```text
1
3 10 4
1 3 2
4 6 5
7 9 3
```

## 【样例 1 输出】

```text
8 2
```

## 【样例 1 解释】

当 $x=4$ 或 $x=5$ 时，第二、三份预约中的客人都能参加，共 $5+3=8$ 人。其他日期都达不到 $8$ 人，因此答案为 `8 2`。

## 【样例 2 输入】

```text
2
1 10 9
4 6 8
2 5 0
1 3 2
3 5 4
```

## 【样例 2 输出】

```text
0 2
6 1
```

## 【样例 2 解释】

第一组中，$x$ 只能取 $0$ 或 $1$，两种安排都不能满足这份预约。

第二组中，两场在同一天。只有 $x=3$ 时两份预约都能满足，共 $6$ 人，每份预约只计一次。

## 【附加样例】

样例 1、2 与题面一致。其余样例见下发目录 `bloom/`。

| 样例编号 | 数据范围与特点 |
| --- | --- |
| 3 | $T=3$，每组 $n\le3,H\le12$，包括两场都落在同一预约区间内的情形 |
| 4 | $T=1,n=1800,H=10^{18}$ |
| 5 | $T=3,\sum n=199904,H\le10^{18}$ |
| 6 | $T=1,n=199901,H=10^{18}-1$ |

## 【数据范围】

对于所有数据，$1\le T\le20$，$1\le n\le2\times10^5$，$0\le d\le H\le10^{18}$，$0\le l_i\le r_i\le H$，$1\le w_i\le10^9$。同一测试点中所有数据的 $n$ 之和不超过 $2\times10^5$。

| 测试点编号 | 每组数据的额外限制 |
| --- | --- |
| 1～4 | $n\le200,H\le200$ |
| 5～8 | $n\le3000$ |
| 9～20 | 无 |

# 丝带（ribbon）

## 【题目描述】

心爱准备给 Rabbit House 的礼盒系上丝带。理世找来一条很长的练习丝带，先让她试试不同颜色的搭配。

丝带被分成连续的 $n$ 格，从左到右编号为 $1$ 到 $n$。第 $i$ 格的初始颜色为 $a_i$，颜色用正整数表示。

接下来有 $q$ 次操作，按给定顺序执行：

- `1 l r c`：把第 $l$ 格到第 $r$ 格全部染成颜色 $c$。
- `2 k`：询问当前丝带中，有多少个长度至少为 $k$、且每一格颜色都相同的连续子段。

一个连续子段由两个端点 $L,R$ 确定，包含第 $L$ 格到第 $R$ 格，长度为 $R-L+1$。只要端点不同，就视为不同子段。询问不会剪断丝带，也不会改变它的颜色。

## 【输入格式】

从文件 `ribbon.in` 读入数据。

第一行包含两个整数 $n,q$。

第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$。

接下来 $q$ 行，每行描述一次操作，格式如题目描述所示。

## 【输出格式】

输出到文件 `ribbon.out`。

对于每次类型为 `2` 的操作，输出一行一个整数，表示符合条件的子段个数。

## 【样例 1 输入】

```text
6 7
1 1 2 2 2 1
2 1
2 2
1 3 5 1
2 2
1 2 4 3
2 2
2 3
```

## 【样例 1 输出】

```text
10
4
15
4
1
```

## 【样例 1 解释】

初始的三个极长同色段长度为 $2,3,1$，前两次询问分别得到 $10$ 和 $4$。第一次染色后整段同色，长度至少为 $2$ 的子段共有 $5+4+3+2+1=15$ 个。

第二次染色后，颜色依次为 $1,3,3,3,1,1$。长度至少为 $2$ 的单色子段有 $3+1=4$ 个，长度至少为 $3$ 的只有 $[2,4]$。

## 【样例 2 输入】

```text
1 4
7
2 1
1 1 1 9
2 1
2 1
```

## 【样例 2 输出】

```text
1
1
1
```

## 【附加样例】

样例 1、2 与题面一致。其余样例见下发目录 `ribbon/`。

| 样例编号 | 数据范围与特点 |
| --- | --- |
| 3 | $n=300,q=400$ |
| 4 | $n=q=2\times10^5$，满足特殊性质 A |
| 5 | $n=q=2\times10^5$，多次对较长区间染色 |
| 6 | $n=q=2\times10^5$，多次对较短区间染色 |

## 【数据范围】

对于所有数据，$1\le n,q\le2\times10^5$，$1\le a_i,c\le10^9$。对于染色操作，$1\le l\le r\le n$；对于询问操作，$1\le k\le n$。

特殊性质 A：所有操作均为询问。

| 测试点编号 | 规模限制 | 特殊性质 |
| --- | --- | --- |
| 1～4 | $n,q\le200$ | 无 |
| 5～8 | $n,q\le3000$ | 无 |
| 9～10 | $n,q\le2\times10^5$ | A |
| 11～20 | $n,q\le2\times10^5$ | 无 |

# 书架（shelf）

## 【题目描述】

智乃想整理 Rabbit House 窗边的书架。心爱把书一本本摆到长桌上，才发现旅行手册、画集和点心食谱全混在了一起。

桌上一共有 $n$ 本书，从左到右的位置编号为 $1$ 到 $n$。每本书属于 $1$ 到 $k$ 中的一类，第 $i$ 本书的类别为 $a_i$，每一类都至少有一本书。

整理后，相同类别的书必须放在连续的一段位置上。不同类别之间的先后顺序可以任意选择，但**同一类书之间的相对顺序必须保持不变**。

一本书原来在第 $p$ 个位置，整理后在第 $q$ 个位置，它的移动距离就是 $|p-q|$。一次整理的代价定义为所有书的移动距离的最大值。这里只比较整理前后的位置，不计搬动过程中的路线。

请你求出最小的整理代价，以及达到这个代价的类别排列有多少种。两个方案只要有两个类别的先后顺序不同，就视为不同方案。方案数对 $10^9+7$ 取模。

## 【输入格式】

从文件 `shelf.in` 读入数据。

第一行包含一个整数 $T$，表示数据组数。每组数据的格式如下：

第一行包含两个整数 $n,k$。

第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$。

## 【输出格式】

输出到文件 `shelf.out`。

每组数据输出一行两个整数，依次表示最小整理代价、最优方案数对 $10^9+7$ 取模后的结果。

## 【样例 1 输入】

```text
1
5 3
1 2 3 1 1
```

## 【样例 1 输出】

```text
2 4
```

## 【样例 1 解释】

最优的类别排列有 $(1,2,3)$、$(2,1,3)$、$(2,3,1)$ 和 $(3,2,1)$，代价都为 $2$。

下面画出类别排列为 $(1,2,3)$ 时的整理过程。同一类别用相同颜色表示，字母区分同类的不同书籍。

![书架样例的移动过程][shelf-move]

图 1　五本书的移动距离依次为 $0,2,2,2,2$，整理代价为 $2$。

## 【样例 2 输入】

```text
2
5 3
1 1 2 3 3
4 2
2 1 2 1
```

## 【样例 2 输出】

```text
0 1
1 1
```

## 【样例 2 解释】

第一组保持原样即可。第二组将类别 $2$ 放在类别 $1$ 前面，整理后的类别序列为 $2,2,1,1$，只有中间两本书移动了一个位置。

## 【附加样例】

样例 1、2 与题面一致。其余样例见下发目录 `shelf/`。

| 样例编号 | 数据范围与特点 |
| --- | --- |
| 3 | $T=1,n=35,k=7$ |
| 4 | $T=1,n=1500,k=14$ |
| 5 | $T=3,\sum n=199811,k\le20$ |
| 6 | $T=1,n=199801,k=20$ |

## 【数据范围】

对于所有数据，$1\le T\le20$，$1\le k\le20$，$k\le n\le2\times10^5$，$1\le a_i\le k$，每一类至少出现一次。

同一测试点中，所有数据的 $n$ 之和不超过 $2\times10^5$，所有数据的 $2^k$ 之和不超过 $2^{21}$。

| 测试点编号 | 每组数据的额外限制 |
| --- | --- |
| 1～4 | $n\le40,k\le8$ |
| 5～8 | $n\le1500,k\le14$ |
| 9～20 | 无 |

# 菜单（menu）

## 【题目描述】

秋日的甜点预约陆续送到了 Rabbit House。心爱负责烘焙，智乃把每天要做的口味记在一张菜单上，准备提前贴在店门口。

一共有 $n$ 份订单，接下来的 $n$ 天每天恰好完成一份。第 $i$ 份订单的口味编号为 $c_i$，只能在第 $l_i$ 天到第 $r_i$ 天之间完成，两个端点都包含在内。每份订单都要完成一次，且只能完成一次。

将每天完成的订单口味依次写下，就得到一个长度为 $n$ 的菜单。同一种口味可以有多份订单，它们允许完成的日期不一定相同。**菜单只记录口味，不记录订单编号。**

智乃已经写好了一张菜单 $b_1,b_2,\ldots,b_n$，保证可以按照它完成全部订单。她想把所有能够实现的不同菜单按字典序从小到大排列，看看紧接在这张菜单后面的是哪一张。

请你求出这张菜单。也就是说，在所有字典序严格大于 $b$ 的合法菜单中，输出字典序最小的一张；如果不存在，输出 $-1$。

两个长度相同的序列比较字典序时，找到第一个不同的位置，该位置数字较小的序列字典序较小。例如，$(1,2,1)$ 的字典序小于 $(2,1,1)$。仅仅交换两份同口味的订单，不会得到不同的菜单。

## 【输入格式】

从文件 `menu.in` 读入数据。

第一行包含一个整数 $T$，表示数据组数。每组数据的格式如下：

第一行包含一个整数 $n$。

接下来 $n$ 行，每行包含三个整数 $l_i,r_i,c_i$，描述第 $i$ 份订单。

最后一行包含 $n$ 个整数 $b_1,b_2,\ldots,b_n$，表示已经写好的菜单。

## 【输出格式】

输出到文件 `menu.out`。

每组数据输出一行。如果存在符合要求的菜单，输出其 $n$ 个口味编号；否则输出 $-1$。

## 【样例输入】

```text
2
3
1 3 1
1 2 2
2 3 1
1 2 1
2
1 1 1
2 2 2
1 2
```

## 【样例输出】

```text
2 1 1
-1
```

## 【样例解释】

第一组中，两种不同的合法菜单按字典序排列为 $(1,2,1)$、$(2,1,1)$，所以答案为 $(2,1,1)$。例如，依次完成第 $2,1,3$ 份订单，就能得到这张菜单。

第二组中，两份订单的完成日期都已经确定，只有菜单 $(1,2)$，因此输出 $-1$。

## 【附加样例】

样例 1 与题面一致。其余样例见下发目录 `menu/`，对应答案见同名 `.ans` 文件。

| 样例编号 | 数据范围与特点 |
| --- | --- |
| 2 | $T=5$，每组 $n\le9$，包括 $n=1$、口味重复和日期固定的情形 |
| 3 | $T=4$，每组 $n\le2000$ |
| 4 | $T=2$，两组的 $n$ 分别为 $5,199990$，满足特殊性质 A |
| 5 | $T=1,n=2\times10^5$，答案从第 $1$ 天起与原菜单不同 |
| 6 | $T=2$，两组均有 $n=10^5$，包含重复口味和不同的日期限制 |

## 【数据范围】

对于所有测试点，保证 $1\le T\le10$，$1\le n\le2\times10^5$，$1\le l_i\le r_i\le n$，$1\le c_i,b_i\le n$。同一输入文件中，所有测试组的 $n$ 之和不超过 $2\times10^5$。

保证每组输入中的菜单 $b$ 都能由一种符合日期限制的订单安排得到。

| 测试点编号 | $n$ 的上限 | 特殊性质 |
| --- | --- | --- |
| 1～4 | $9$ | 无 |
| 5～8 | $2000$ | 无 |
| 9～10 | $2\times10^5$ | A |
| 11～20 | $2\times10^5$ | 无 |

特殊性质 A：所有订单均满足 $r_i=n$。

[shelf-move]: data:image/png;base64,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
