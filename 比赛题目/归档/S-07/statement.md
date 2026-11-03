# 提高组模拟赛

第 07 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 旅行 | 表达式 | 序列 | 散步 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | travel | expression | seq | wander |
| 可执行文件名 | travel | expression | seq | wander |
| 输入文件名 | travel.in | expression.in | seq.in | wander.in |
| 输出文件名 | travel.out | expression.out | seq.out | wander.out |
| 每个测试点时限 | 1 秒 | 1 秒 | 1 秒 | 1 秒 |
| 内存限制 | 256 MiB | 256 MiB | 256 MiB | 256 MiB |
| 测试点数目 | 10 | 10 | 10 | 16 |
| 测试点是否等分 | 是（每点 10 分） | 是（每点 10 分） | 是（每点 10 分） | 否（各点分值不同） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | travel.cpp | expression.cpp | seq.cpp | wander.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 各测试点独立计分。所有题目采用全文比较评测。


## 旅行（travel）




### 题目描述

有 $N+1$ 个城市，分别编号为 $0, 1, 2, 3, \cdots, N$。

城市之间有一些道路，道路是可以双向移动的，每条道路会连接两个不同的城市。

但是，这些城市之间的道路连接关系看上去有些奇怪：

- 对于任意两个不同的城市 $x, y$，只有当 $x \oplus y$ 的**二进制位**上有且**仅有一个** $1$，那么 $x$ 和 $y$ 这两个城市之间才会存在一条道路。

小 S 一开始在 $A$ 号城市，她想要去 $B$ 号城市。请问小 S 至少要经过多少条道路才能够到达 $B$ 号城市？

$x \oplus y$ 表示 $x$ 和 $y$ 两个整数的**按位异或和（Bitwise XOR）**。即对于参与运算的两个整数二进制上的每一位单独进行运算，相同则为 $0$，不同则为 $1$。

### 输入格式


仅一行，包含三个正整数 $N, A, B$。

### 输出格式


一个整数，表示从城市 $A$ 到城市 $B$ 需要经过最少多少条道路。



### 样例 1 输入


```
8 3 5
```

### 样例 1 输出


```
2
```

### 样例 1 解释


对于样例1，可行的方案之一是：$3\ (011) \rightarrow 7\ (111) \rightarrow 5\ (101)$。



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `travel2.in`、`travel2.ans` |

### 数据范围


对于 $30\%$ 的数据，保证 $N \le 10$ 。

对于 $50\%$ 的数据，保证 $N \le 1000$ 。

对于 $100\%$ 的数据，保证 $2 \le N \le 10^9, \ 1 \le A, B \le N, \ A \ne B$

## 表达式（expression）




### 题目描述

小 S 最近开发了一款奇特的应用软件，它允许你按顺序输入 $N$ 个非负整数，然后软件会随机往这 $N$ 个整数的 $N-1$ 个间隙当中插入 $+, -, \oplus$ （加、减、按位异或）三种符号中的一种，从而形成一个表达式，最后计算出这个表达式的值，作为软件的输出结果。

已知这三种符号中，按位异或 $\oplus$ 的计算优先级最高，加减 $+-$ 的优先级相等。计算表达式的结果时会先从左往右计算所有 $\oplus$ 运算，然后再从左往右计算所有 $+-$ 运算。

现在小 S 往这个软件里输入了 $N$ 个非负整数 $A_1, A_2, \cdots, A_N$，她想知道将其输入到软件内后，对于**所有可能形成的表达式**，其值的总和是多少？

### 输入格式


第一行包含一个正整数 $N$，表示整数的个数。

第二行包含 $N$ 个非负整数 $A_1, A_2, \cdots, A_N$，表示输入的每个数。

### 输出格式


一个整数，表示**所有可能的表达式的值**之和，由于答案可能很大，输出对 $998244353$ 取模后的结果即可。


### 样例 1 输入


```
3
1 2 3
```

### 样例 1 输出


```
12
```

### 样例 1 解释


对于样例一：所有可能的表达式及结果分别为：
$$
\begin{aligned}
1+2+3 &= 6 \\
1+2-3 &= 0 \\
1+2\oplus 3 &= 2 \\
1-2+3 &= 2 \\
1-2-3 &= -4 \\
1-2\oplus 3 &= 0 \\
1\oplus 2+3 &= 6 \\
1\oplus 2-3 &= 0 \\
1\oplus 2\oplus 3 &= 0
\end{aligned}
$$
总和为 $6+2+2-4+6 = 12$。


### 样例 2 输入


```
2
7 3
```

### 样例 2 输出


```
18
```





### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `expression3.in`、`expression3.ans` |
| 4 | `expression4.in`、`expression4.ans` |

### 数据范围


对于 $30\%$ 的数据，保证 $N \le 13, \ A_i \le 10^3$

对于 $40\%$ 的数据，保证 $N \le 50$ 。

对于 $60\%$ 的数据，保证 $N \le 1000,\ A_i \le 10^5$ 。

对于 $100\%$ 的数据，保证 $1 \le N \le 10^5, \ 0 \le A_i \le 10^9$ 。

## 序列（seq）




### 题目描述

我们定义一个“U 型”序列应该满足以下条件：

- 序列中的第一个数与最后一个数必须都严格大于序列中的所有其它数字。

现在有一个长度为 $N$ 的序列 $A_1, A_2, \cdots, A_N$，请找出其中长度最大的“U 型”**子序列**，并输出这个最大长度。

子序列是指从一个序列中删除一些元素（也可以不删除）之后，不改变剩余元素的顺序所得到的序列。

### 输入格式


第一行包含一个整数 $N$，表示数字个数。

第二行包含 $N$ 个正整数 $A_1, A_2, \cdots, A_N$。

### 输出格式


一个整数，表示能够找出的最长的“U 型”子序列的长度。


### 样例 1 输入


```
5
6 2 8 3 5
```

### 样例 1 输出


```
4
```

### 样例 1 解释


满足条件的子序列为 $\{6, 2, 3, 5\}$。


### 样例 2 输入


```
10
4 2 7 9 1 6 5 2 5 3
```

### 样例 2 输出


```
5
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `seq3.in`、`seq3.ans` |

### 数据范围


对于 $20\%$ 的数据，保证 $N \le 100$ 。

对于 $30\%$ 的数据，保证 $N \le 1000, A_i \le 1000$ 。

对于 $40\%$ 的数据，保证 $N \le 1000, \ A_i \le 10^5$ 。

对于 $100\%$ 的数据，保证 $2 \le N \le 10^5,\ 1 \le A_i \le 10^9$ 。

## 散步（wander）




### 题目描述

小 Y 喜欢在一棵包含 $N$ 个点，$N-1$ 条边的树上散步。树上的每个点分别编号为 $1, 2, 3, \cdots, N$。

小 Y 一开始站在编号为 $root$ 的点上，每次可以花 $1$ 分钟的时间走到与当前点相邻的点上（我们定义两个点是相邻的，当且仅当这两个点之间直接存在一条边）。

小 Y 希望能在最短的时间内把树上的每个点都走一遍，最后重新回到编号为 $root$ 这个点，并且每当走过一个之前没走过的点，他都会在他的笔记本上记下这个点的编号，最终形成一个整数序列。而他的真正目的是：计算出这个序列所包含的逆序对数！

当然，如果我们能够知道小 Y 在过程中具体是怎么走的，最后统计逆序对总数的这个问题对你来说就非常简单了~ 但现在的问题就是……小 Y 也不知道自己该怎么走……

作为小 Y 的好朋友，请你帮小 Y 找出所有能保证总时间最短的走法，并对于每一种走法，求出小 Y 记录下来的序列中的逆序对总数之和吧！小 Y 会感谢你的！

逆序对：对于一个包含 $N$ 个数字的序列 $A_1, A_2, \cdots, A_N$，如果存在一对正整数 $i, j$，满足 $1 \le i < j \le N$ 且 $A_i > A_j$，则称 $(i, j)$ 这个有序对为“逆序对”。

### 输入格式


第一行包含两个正整数 $N, root$，分别表示树上的点数以及小 Y 一开始所在的点的编号。

接下来 $N-1$ 行，每行包含两个整数 $u_i$ 和 $v_i$，表示树上有一条边连接着编号为 $u_i$ 和 $v_i$ 的这两个点。

### 输出格式


一个整数，表示对于每一种走法，小 Y 所记录下来的序列中的逆序对总数之和，答案可能很大，输出对 $998244353$ 取模后的结果即可。


### 样例 1 输入


```
3 2
2 1
2 3
```

### 样例 1 输出


```
3
```

### 样例 1 解释




![原题示意图][s-07-original-5-X61]



在这棵树上，小 Y 一开始站在编号为 $2$ 的点上，要想在最短时间内把树上每个点都走一遍再回到编号为 $2$ 的点，他只有两种走法：

```plain
 2 -> 1 -> 2 -> 3 -> 2
 2 -> 3 -> 2 -> 1 -> 2
```

对于每种走法，小 Y 会在他的笔记本上按顺序分别写下以下这些序列：

```plain
 2 1 3
 2 3 1
```

对于第一个序列，逆序对有 $(2, 1)$ 这一对。

对于第二个序列，逆序对有 $(2, 1)$ $(3, 1)$ 这两对。

总数为 $1 + 2 = 3$ 对。


### 样例 2 输入


```
5 4
3 1
1 5
4 1
4 2
```

### 样例 2 输出


```
20
```

### 样例 2 解释




![原题示意图][s-07-original-6-X72]



在这棵树上，小 Y 的走法有：

```plain
 4 -> 1 -> 3 -> 1 -> 5 -> 1 -> 4 -> 2 -> 4
 4 -> 1 -> 5 -> 1 -> 3 -> 1 -> 4 -> 2 -> 4
 4 -> 2 -> 4 -> 1 -> 3 -> 1 -> 5 -> 1 -> 4
 4 -> 2 -> 4 -> 1 -> 5 -> 1 -> 3 -> 1 -> 4
```

对于每种走法，小 Y 会在他的笔记本上按顺序分别写下以下这些序列：

```plain
 4 1 3 5 2
 4 1 5 3 2
 4 2 1 3 5
 4 2 1 5 3
```

对于第一个序列，逆序对有 $(4, 1)$ $(4, 3)$ $(4, 2)$ $(3, 2)$ $(5, 2)$ 这五对。

对于第二个序列，逆序对有 $(4, 1)$ $(4, 3)$ $(4, 2)$ $(5, 3)$ $(5, 2)$ $(3, 2)$ 这六对。

对于第三个序列，逆序对有 $(4, 2)$ $(4, 1)$ $(4, 3)$ $(2, 1)$ 这四对。

对于第四个序列，逆序对有 $(4, 2)$ $(4, 1)$ $(4, 3)$ $(2, 1)$ $(5, 3)$ 这五对。

总数为 $5 + 6 + 4 + 5 = 20$ 对。





### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `wander3.in`、`wander3.ans` |
| 4 | `wander4.in`、`wander4.ans` |

### 数据范围


对于 $\dfrac{6}{16}$ 的测试点，保证 $N \le 20$ 。

对于 $\dfrac{10}{16}$ 的测试点，保证 $N \le 1000$ 。

对于 $\dfrac{16}{16}$ 的测试点，保证 $2 \le N \le 300000, \ 1 \le root, u_i, v_i \le N, \ u_i \ne v_i$ ，保证给定的图是一棵树。


本题共 16 个测试点。第 6、10、15、16 个测试点各 7 分，其余测试点各 6 分，按测试点独立计分。


[s-07-original-5-X61]: data:image/png;base64,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
[s-07-original-6-X72]: data:image/png;base64,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
