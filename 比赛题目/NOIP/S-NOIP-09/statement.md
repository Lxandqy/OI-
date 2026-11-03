# 提高组模拟赛

第 09 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 灯罩 | 采药 | 净化 | 传送 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | shade | herb | purify | portal |
| 可执行文件名 | shade | herb | purify | portal |
| 输入文件名 | shade.in | herb.in | purify.in | portal.in |
| 输出文件名 | shade.out | herb.out | purify.out | portal.out |
| 每个测试点时限 | 1 秒 | 1 秒 | 2 秒 | 2 秒 |
| 内存限制 | 256 MiB | 256 MiB | 256 MiB | 256 MiB |
| 测试点数目 | 20 | 20 | 20 | 20 |
| 测试点是否等分 | 是（每点 5 分） | 是（每点 5 分） | 否（捆绑计分） | 否（捆绑计分） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| C++ | shade.cpp | herb.cpp | purify.cpp | portal.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 前两题各测试点独立计分；第三、四题采用子任务捆绑计分，须通过同一子任务的全部测试点才能得到该子任务的分数。含多组数据的测试点，须答对该点内的全部数据才能通过。

## 灯罩（shade）

### 题目描述

菲伦准备给旅途中买来的灯换一个三角形灯罩。桌上有 $n$ 根木条，第 $i$ 根长 $a_i$，她要从中选出三根作为灯罩的三条边。

可以把选中的至多一根木条截短，截去的长度必须为非负整数且不超过 $K$，截短后这根木条的长度仍须为正。三根木条必须组成非退化三角形，即任意两边长度之和严格大于第三边。

求灯罩周长的最大值；若有多种方案达到最大周长，再求其中截去长度的最小值。若没有可行方案，输出 `-1 -1`。

### 输入格式

从文件 `shade.in` 读入数据。

第一行一个整数 $T$，表示数据组数。每组数据第一行两个整数 $n,K$，第二行 $n$ 个整数 $a_1,a_2,\ldots,a_n$。

### 输出格式

输出到文件 `shade.out`。

每组数据输出一行两个整数，依次表示最大周长、达到最大周长时的最少截去长度。无解时输出 `-1 -1`。

### 样例 1 输入

```text
1
5 3
2 3 7 20 4
```

### 样例 1 输出

```text
13 1
```

### 样例 1 解释

选择长度为 $3,4,7$ 的三根木条，将长度 $7$ 截短为 $6$，得到周长 $13$，截去长度为 $1$。

### 附加样例

样例 $1\sim6$ 的输入与答案见下发文件 `shade/shade编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
|---|---|
| 1 | $T=1$，$n\le5$ |
| 2 | $T=5$，$n\le12$ |
| 3 | $T=5$，$n\le290$ |
| 4 | $T=5$，$n\le290$ |
| 5 | $T=5$，$n\le190000$ |
| 6 | $T=5$，$n\le190000$ |

### 数据范围

对于所有数据，$1\le T\le30$，$3\le n\le2\times10^5$，$1\le a_i\le10^9$，$0\le K\le10^9$；一个测试点内所有数据的 $n$ 之和不超过 $2\times10^5$。

每个测试点 $5$ 分，独立计分。

| 测试点编号 | $n$ 的上界 | $a_i,K$ 的上界 |
|---|---|---|
| $1\sim4$ | $12$ | $30$ |
| $5\sim10$ | $300$ | $10^9$ |
| $11\sim20$ | $2\times10^5$ | $10^9$ |

## 采药（herb）

### 题目描述

芙莉莲和菲伦在林间收集药草。不同药草的采集难度不同，同一种药草也会随着附近容易找到的植株逐渐减少而越来越难采。

共有 $n$ 种药草。第 $i$ 种药草的第 $j$ 株需要消耗 $a_i+(j-1)d_i$ 点体力，其中 $j=1,2,\ldots$。每种药草都有足够多的植株；若采集这种药草 $x$ 株，就必须支付它的前 $x$ 株的全部体力消耗。

她们需要恰好采集 $K$ 株，并且其中至少有 $R$ 种不同的药草。求所需体力之和的最小值。

### 输入格式

从文件 `herb.in` 读入数据。

第一行一个整数 $T$，表示数据组数。每组数据第一行三个整数 $n,K,R$。接下来 $n$ 行，每行两个整数 $a_i,d_i$。

### 输出格式

输出到文件 `herb.out`。

每组数据输出一行一个整数，表示最少体力消耗。

### 样例 1 输入

```text
1
4 6 3
1 2
7 1
9 3
10 2
```

### 样例 1 输出

```text
32
```

### 样例 1 解释

依次从四种药草中采集 $4,1,1,0$ 株，体力消耗为 $(1+3+5+7)+7+9=32$，恰好使用三种药草。

### 附加样例

样例 $1\sim6$ 的输入与答案见下发文件 `herb/herb编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
|---|---|
| 1 | $T=1$，$n\le4$，$K\le6$ |
| 2 | $T=5$，$n\le6$，$K\le18$ |
| 3 | $T=5$，$n\le2000$，$K\le190000$ |
| 4 | $T=5$，$n\le2000$，$K\le190000$ |
| 5 | $T=5$，$n\le190000$，$K\le99000000$ |
| 6 | $T=5$，$n\le190000$，$K\le99000000$ |

### 数据范围

对于所有数据，$1\le T\le30$，$1\le n\le2\times10^5$，$1\le K\le10^8$，$1\le R\le\min(n,K)$，$1\le a_i\le10^9$，$1\le d_i\le100$；一个测试点内所有数据的 $n$ 之和不超过 $2\times10^5$，$K$ 之和不超过 $10^8$。

每个测试点 $5$ 分，独立计分。

| 测试点编号 | $n$ 的上界 | $K$ 的上界 |
|---|---|---|
| $1\sim4$ | $6$ | $18$ |
| $5\sim10$ | $2\times10^5$ | $2\times10^5$ |
| $11\sim20$ | $2\times10^5$ | $10^8$ |

## 净化（purify）

### 题目描述

古老的遗迹里散落着 $n$ 座石台，编号为 $1\sim n$。石台之间的通道构成一棵以 $1$ 为根的树，$1$ 号石台位于遗迹入口。每座石台上都残留着一些魔力，芙莉莲和菲伦需要将它们净化。

芙莉莲准备了 $m$ 张卷轴。使用第 $j$ 张卷轴时，净化魔法会从石台 $s_j$ 出发，沿着通往根的道路传递，到石台 $t_j$ 停止。保证 $t_j$ 是 $s_j$ 的祖先，允许 $s_j=t_j$。这条路径上的每座石台都会被净化一次，包含两个端点。

石台 $i$ 至少需要被净化 $a_i$ 次。每张卷轴只能使用一次，不同卷轴可以对应相同的路径，使用顺序不影响效果。

请问最少需要使用多少张卷轴，才能满足所有石台的要求？如果无法满足，输出 $-1$。

### 输入格式

从文件 `purify.in` 读入数据。

第一行一个整数 $T$，表示数据组数。对于每组数据：

第一行两个整数 $n,m$。

第二行 $n$ 个整数 $a_1,a_2,\ldots,a_n$。

第三行 $n-1$ 个整数 $p_2,p_3,\ldots,p_n$，其中 $p_i$ 是石台 $i$ 的父亲；$n=1$ 时省略这一行。

接下来 $m$ 行，每行两个整数 $s_j,t_j$，描述一张卷轴。

### 输出格式

输出到文件 `purify.out`。

每组数据输出一行一个整数，表示最少使用的卷轴数；无解时输出 $-1$。

### 样例 1 输入

```text
1
6 6
2 2 1 1 0 1
1 1 2 2 3
4 2
4 1
5 1
6 1
2 2
3 3
```

### 样例 1 输出

```text
3
```

### 样例 1 解释

可以使用第 $2,3,4$ 张卷轴，各座石台被净化的次数依次为 $3,2,1,1,1,1$，均满足要求。

要净化石台 $6$，必须使用第 $4$ 张卷轴；这张卷轴不经过石台 $2$，而石台 $2$ 还需要被净化两次，因此至少需要三张卷轴。

### 附加样例

样例 $1\sim6$ 的输入与答案见下发文件 `purify/purify编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
|---|---|
| 1 | $T=1$，$n=m=6$ |
| 2 | $T=5$，$n\le19$，$m\le20$ |
| 3 | $T=1$，$n=m=200000$，满足特殊性质 A |
| 4 | $T=2$，$n,m\le2500$ |
| 5 | $T=1$，$n=m=200000$ |
| 6 | $T=2$，$\sum n=\sum m=200000$ |

### 数据范围

对于所有数据，$1\le T\le10$，$1\le n,m\le2\times10^5$，$0\le a_i\le m$，$1\le p_i,s_j,t_j\le n$。保证父亲关系构成一棵以 $1$ 为根的树，且 $t_j$ 是 $s_j$ 的祖先（包括自身）；不保证 $p_i<i$。一个测试点内所有数据的 $n$ 之和、$m$ 之和分别不超过 $2\times10^5$。

本题采用子任务捆绑计分，通过同一子任务的全部测试点才能得到该子任务的分数。

| 子任务 | 测试点编号 | 分值 | $n,m$ 的上界 | 特殊性质 |
|---|---|---|---|---|
| $1$ | $1\sim3$ | $10$ | $20$ | 无 |
| $2$ | $4\sim6$ | $15$ | $2\times10^5$ | A |
| $3$ | $7\sim10$ | $25$ | $2500$ | 无 |
| $4$ | $11\sim20$ | $50$ | $2\times10^5$ | 无 |

特殊性质 A：树是一条链，且根位于链的一个端点。


## 传送（portal）

### 题目描述

芙莉莲找到了一张记录着传送术的旧地图。地图上的 $n$ 个地点按顺序编号为 $1\sim n$，地点 $i$ 的魔法纹样类别为 $c_i$，每次进入该地点还需要消耗 $a_i$ 点魔力。

地图上有 $m$ 条传送术。每条用四个整数 $(u,l,r,w)$ 表示：身处地点 $u$ 时，可以消耗 $w+a_v$ 点魔力，传送到任意满足 $l\le v\le r$ 且 $c_v\ne c_u$ 的地点 $v$。一条传送术可以使用任意多次，每使用一次都计作一次传送。除这些传送术外，没有其他移动方式。

芙莉莲从地点 $s$ 出发，起初不支付 $a_s$。请对每个地点分别求出到达它所需的最少魔力，以及在魔力消耗最少的前提下，所需的最少传送次数。不可达的地点输出 `-1 -1`；起点的答案为 `0 0`。

![传送范围和类别限制][portal-rule]

### 输入格式

从文件 `portal.in` 读入数据。

第一行一个整数 $T$，表示数据组数。每组数据第一行三个整数 $n,m,s$，第二行 $n$ 个整数 $c_1,c_2,\ldots,c_n$，第三行 $n$ 个整数 $a_1,a_2,\ldots,a_n$。接下来 $m$ 行，每行四个整数 $u,l,r,w$，描述一条传送术。

### 输出格式

输出到文件 `portal.out`。

每组数据输出 $n$ 行，第 $i$ 行输出两个整数，依次表示到达地点 $i$ 的最少魔力、在此前提下的最少传送次数。不可达时输出 `-1 -1`。

### 样例 1 输入

```text
1
4 3 1
1 2 1 3
0 2 1 3
1 2 4 1
2 3 4 0
1 4 4 0
```

### 样例 1 输出

```text
0 0
3 1
4 2
3 1
```

### 样例 1 解释

到地点 $2$ 使用第一条传送术，消耗 $1+2=3$；再由地点 $2$ 使用第二条到地点 $3$，总消耗为 $4$，共两次传送。直接使用第三条到地点 $4$，消耗 $3$，共一次传送。第一条不能直接到地点 $3$，因为它与地点 $1$ 类别相同。

### 附加样例

样例 $1\sim6$ 的输入与答案见下发文件 `portal/portal编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
|---|---|
| 1 | $T=1$，$n\le4$，$m\le3$ |
| 2 | $T=8$，$n\le180$，$m\le190$ |
| 3 | $T=8$，$n\le190000$，$m\le190000$，每条传送术均有 $l=r$ |
| 4 | $T=8$，$n\le190000$，$m\le190000$，所有地点的类别互不相同 |
| 5 | $T=8$，$n\le190000$，$m\le190000$ |
| 6 | $T=8$，$n\le190000$，$m\le190000$ |

### 数据范围

对于所有数据，$1\le T\le30$，$1\le n\le2\times10^5$，$0\le m\le2\times10^5$，$1\le s,c_i,u\le n$，$1\le l\le r\le n$，$0\le a_i,w\le10^9$；一个测试点内所有数据的 $n$ 之和、$m$ 之和均不超过 $2\times10^5$。

本题采用子任务捆绑计分，须通过同一子任务的全部测试点才能得到该子任务的分数。

| 子任务 | 测试点编号 | 分值 | $n,m$ 的上界 | 特殊性质 |
|---|---|---|---|---|
| $1$ | $1\sim4$ | $20$ | $200$ | 无 |
| $2$ | $5\sim8$ | $20$ | $2\times10^5$ | 每条传送术均有 $l=r$ |
| $3$ | $9\sim12$ | $20$ | $2\times10^5$ | 所有地点的类别互不相同 |
| $4$ | $13\sim20$ | $40$ | $2\times10^5$ | 无 |



[portal-rule]: data:image/png;base64,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
