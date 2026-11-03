# 提高组模拟赛

第 18 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 限速 | 字符串 | 追逐 | 周期 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | speed | string | chase | period |
| 可执行文件名 | speed | string | chase | period |
| 输入文件名 | speed.in | string.in | chase.in | period.in |
| 输出文件名 | speed.out | string.out | chase.out | period.out |
| 每个测试点时限 | 1 秒 | 1 秒 | 1 秒 | 2 秒 |
| 内存限制 | 256 MiB | 512 MiB | 256 MiB | 256 MiB |
| 测试点数目 | 11 | 10 | 38 | 20 |
| 测试点是否等分 | 否（分组捆绑） | 否（分组捆绑） | 否（分组捆绑） | 否（分组捆绑） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | speed.cpp | string.cpp | chase.cpp | period.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 限速、字符串、追逐、周期按数据范围表分组捆绑，每组全部通过才得分。所有题目采用全文比较评测。


## 限速（speed）




### 题目描述

某国有 $n$ 个城市（编号从 $1$ 到 $n$）和 $m$ 条双向道路，第 $i$ 条道路连接城市 $x_i$ 和 $y_i$，限速为 $s_i$。这些道路保证每个人都可以往来任意两个城市之间。

现在州长小 Z 正计划对道路进行改革。

首先，维护所有 $m$ 条道路的成本太高，因此将放弃 $m-(n-1)$ 条道路，以便剩余的 $n-1$ 条道路仍能保证每个人都可以往来任意两个城市之间。

其次，剩余道路的限速可能会发生变化。更改将按顺序进行，每次更改要么将某条道路的限速提高 $1$，要么降低 $1$。由于更改速度限制需要大量工作，州长小 Z 希望尽量减少更改次数。

小 Z 的目标是建立一个由 $n-1$ 条道路组成的道路网络，所有道路的**最高**速度限制**恰好**等于 $k$。他给你分配了一项任务，请你来帮他计算他们必须执行的速度限制更改次数的最少值，使道路网络满足他们的要求。你可以自由选择要放弃哪 $m-(n-1)$ 条道路。

### 输入格式


第一行包含三个整数 $n,m,k$， 分别表示城市数量、道路数量和所需的最高限速。

接下来是 $m$ 行。第 $i$ 行包含三个整数 $x_i,y_i$ 和 $s_i$，分别表示第 $i$ 条道路连接的城市和该道路的限速。所有道路都是双向的。

保证道路网络是连通的（即沿着道路行驶可以从任意一个城市到达任意一个城市）。

### 输出格式


输出一行一个整数，表示必须执行的最少更改次数，以便剩余 $n-1$ 条道路中的最大速度限制恰好为 $k$ 。



### 样例 1 输入


```
4 5 7
4 1 10
1 2 8
2 3 8
2 4 1
3 4 9
```

### 样例 1 输出


```
2
```

### 样例 1 解释


最优方案之一是放弃连接$1$和$4$的道路，以及连接$3$和$4$的道路，然后将连接$1$和$2$的道路限速降低$1$，再将连接$2$和$3$的道路限速降低$1$。



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `speed2.in`、`speed2.ans` |

### 数据范围


本题采用子任务捆绑计分，通过一个子任务内的全部测试点才能获得该子任务的分数。

对于所有数据，$2\le n\le2\times10^5$，$n-1\le m\le\min(2\times10^5,\frac{n(n-1)}2)$，$1\le k,s_i\le10^9$，$1\le x_i,y_i\le n$，$x_i\ne y_i$。

| 子任务 | 测试点编号 | 分数 | 附加限制 |
| :---: | :---: | :---: | :---: |
| 1 | 1～2 | 20 | 所有 $s_i\le k$ |
| 2 | 3～4 | 20 | 所有 $s_i\ge k$ |
| 3 | 5～6 | 20 | $n\le10^3$ |
| 4 | 7～11 | 40 | 无附加限制 |

## 字符串（string）




### 题目描述

小 Z 有一个字符串 $S$，字符串只包含三种数字字符 `0,1,2`。

现在给出一个定义：一个字符串是**优雅的**，当且仅当没有相邻的两个字符是相同的。

- 例如，字符串 `01220` 不是优雅的，因为有两个相邻的 `2`，字符串 `01020102120` 是优雅的。

小 Z 每一次可以交换字符串 $S$ 中任意一对相邻的字符，问把字符串 $S$ 变成**优雅的**的至少需要操作几次？如果字符串 $S$ 原本就是优雅的，则输出 `0`。

### 输入格式


输入一行一个字符串 $S$，其中只包含三种字符 `0,1,2`。

### 输出格式


输出一行一个整数，表示最少操作次数。如果不需要操作，则输出 `0`，如果无解输出 `-1`。


### 样例 1 输入


```
00122
```

### 样例 1 输出


```
2
```

### 样例 1 解释


交换 $(S_2,S_3)$，结果为 `01022`。

交换 $(S_3,S_4)$，结果为 `01202`。


### 样例 2 输入


```
0101020002
```

### 样例 2 输出


```
-1
```


### 样例 3 输入


```
000201202
```

### 样例 3 输出


```
6
```


### 样例 4 输入


```
0000120202010210211110212202020222222200000111111000001112222000012120102012010201200
```

### 样例 4 输出


```
55
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 5 | `string5.in`、`string5.ans` |

### 数据范围

本题采用子任务捆绑计分，通过同一子任务内的全部测试点才能获得该子任务的分数，各子任务的分数相加。

对于全部测试数据，$1\le\vert S\vert\le400$，$S$ 只含数字字符 `0`、`1`、`2`。

| 子任务编号 | 测试点编号 | 分值 | 附加限制 |
|---|---|---|---|
| 1 | 1～3 | 20 | $1\le\vert S\vert\le12$ |
| 2 | 4～6 | 15 | 字符 `0` 的个数大于 $\lfloor\vert S\vert/2\rfloor$ |
| 3 | 7～10 | 65 | 无 |

## 追逐（chase）




### 题目描述

小 Z 和小 Y 正在一棵无根树上玩追逐游戏。树由 $n$ 个节点构成，编号分别是 $1,2,\dots,n$ 。

已知小 Z 会在 $0$ 秒时从 $S$ 号节点出发，以每秒一条边的速度前往 $T$ 号节点，且小 Z 会沿着这两点之间的最短路移动。形式化的，假设树上从 $S$ 到 $T$ 的最短路径经过的节点编号依次是 $p_0,p_1,\dots,p_k$，其中 $p_0=S,p_k=T$，那么小 Z 在第 $i$ 秒时会位于 $p_i$ 号节点。在小 Z 到达 $T$ 号节点后，他会一直停在 $T$ 号点，直到他被小 Y 抓住。

小 Y 会在 $0$ 秒时从 $S'$ 号节点出发，且小 Y 完全了解小 Z 的行动路线。每秒小 Y 可以选择沿着与当前节点连接的一条边移动，或者停在当前节点不动。小 Y 会选择最优的方式移动，使他能够尽早抓住小 Z 。 我们称小 Y 在 $t$ 秒时抓住了小 $Z$ ，当且仅当在第 $t$ 秒时，小 Y 和小 Z 恰好在同一个节点。注意小 Y 只能在节点上抓到小 Z，而不能在边上抓住小 Z。

他们一共进行了 $q$ 次追逐游戏，对于每次游戏，如果小 Y 都使用最优策略，请你计算小 Y 最早什么时刻抓住小 Z，以及在哪个节点抓住小 Z。可以证明，在最优策略下，题目所求的时间和节点都唯一。

### 输入格式


第一行两个整数 $n,q$ 。

接下来 $n-1$ 行，每行两个整数 $u_i,v_i\ (1\le u_i,v_i\le n, u_i\not = v_i)$，代表树上的一条边。保证输入的所有边构成了一棵树。

接下来 $q$ 行，每行三个整数 $S_i,T_i,S_i'(1\le S_i,T_i,S_i'\le n, S_i\not = T_i)$，代表小 Z 的起点，小 Z 的终点，小 Y 的起点。

### 输出格式


输出 $q$ 行，每行两个整数 $t_i,p_i$，代表第 $i$ 次游戏小 Y 最早在 $t_i$ 秒时抓住小 Z，相应的节点是 $p_i$ 号节点。


### 样例 1 输入


```
5 3 
1 2 
1 3 
3 4 
3 5 
4 1 2 
3 5 1 
5 2 4
```

### 样例 1 输出


```
2 1 
2 5 
1 3
```





### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `chase2.in`、`chase2.ans` |
| 3 | `chase3.in`、`chase3.ans` |

### 数据范围


本题采用子任务捆绑计分，通过一个子任务内的全部测试点才能获得该子任务的分数。

对于所有数据，$2\le n\le2\times10^5$，$1\le q\le2\times10^5$。树上节点及询问中节点的编号均在 $1$ 到 $n$ 之间，每次询问均满足 $S_i\ne T_i$。

| 子任务 | 测试点编号 | 分数 | 附加限制 |
| :---: | :---: | :---: | :---: |
| 1 | 1～4 | 10 | 树是一条链 |
| 2 | 5～8 | 15 | $n,q\le100$ |
| 3 | 9～13 | 15 | 所有 $S_i'=T_i$ |
| 4 | 14～18 | 20 | $q\le10$ |
| 5 | 19～38 | 40 | 无附加限制 |

## 周期（period）




### 题目描述

对于一个字符串 $w=w_1 w_2 \ldots w_{len}$，我们称正整数 $p\ (1\le p\le len)$ 是$w$ 的周期，当且仅当对于任意的 $i\ (1 \leq i \leq len -p)$ 都有 $w_i=w_{i+p}$。

小 Z 有一个长度为 $n$ 的字符串 $d=d_1 d_2 \ldots d_n$，他用这个字符串生成了 $n+1$ 个字符串 $S_0, S_1, S_2, \ldots, S_n$，其中 $S_0$ 是空串。接下来，对于每个 $i\ (1 \leq i \leq n)$ ：

- 如果 $d_i$ 是一个小写英文字符，那么 $S_i=d_i+S_{i-1}$ ，也就是在 $S_{i-1}$ 前面添加字符 $d_i$ 得到 $S_i$。
- 如果 $d_i$ 是一个大写英文字符，那么假设 $d_i$ 的小写形式是 $c_i$，那么 $S_i=S_{i-1}+c_i$，也就是在 $S_{i-1}$ 后面添加字符 $c_i$ 得到 $S_i$。

小 Y 有 $m$ 个整数 $p_1, p_2, \ldots, p_m$，并向你问了 $q$ 个问题：

第 $i$ 个问题会提供三个参数 $k_i, l_i, r_i$ ，请你找出最小的整数 $x$，使得 $x$ 是 $S_{k_i}$ 的周期，并且 $x$ 是 $p_{l_i}, p_{l_i+1}, \ldots, p_{r_i-1}, p_{r_i}$ 中的某个数。如果你找不到这样的整数 $x$，输出 $-1$ 。

### 输入格式


第一行一个整数 $n$ 。

第二行一个长度为 $n$ 的字符串$d=d_1 d_2 \ldots d_n$，由大写和小写的英文字符构成。

第三行一个整数 $m$ 。

第四行 $m$ 个整数 $p_1,p_2,\cdots,p_m$ 。

第五行一个整数 $q$ 。

接下来 $q$ 行，每行三个整数 $k_i,l_i,r_i$ ，代表第 $i$ 个询问。

### 输出格式


对于每个询问，输出一行一个整数，代表答案。


### 样例 1 输入


```
7
AABAAba
9
4 3 2 1 7 5 3 6 1
6
1 4 4
2 1 4
2 1 3
3 3 5
5 4 7
7 8 9
```

### 样例 1 输出


```
1
1
2
-1
3
6
```

### 样例 1 解释






![构造过程][import-statement-image-0]











### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `period2.in`、`period2.ans` |
| 3 | `period3.in`、`period3.ans` |
| 4 | `period4.in`、`period4.ans` |

### 数据范围


本题采用子任务捆绑计分，通过一个子任务内的全部测试点才能获得该子任务的分数。

对于所有数据，$1\le n,m,q\le5\times10^5$，$1\le p_i,k_i\le n$，$1\le l_i\le r_i\le m$。

| 子任务 | 测试点编号 | 分数 | 附加限制 |
| :---: | :---: | :---: | :---: |
| 1 | 1～3 | 10 | $m\le3$，$n\le1000$ |
| 2 | 4～7 | 15 | $n,m,q\le100$ |
| 3 | 8～11 | 20 | 每次询问均满足 $r_i-l_i\le100$ |
| 4 | 12～15 | 25 | $p_1\le p_2\le\cdots\le p_m$ |
| 5 | 16～20 | 30 | 无附加限制 |

[import-statement-image-0]: data:image/png;base64,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
