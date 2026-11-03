# 提高组模拟赛

第 14 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 机器 | 登山 | 数列 | 染色 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | alice | mountain | sequence | color |
| 可执行文件名 | alice | mountain | sequence | color |
| 输入文件名 | alice.in | mountain.in | sequence.in | color.in |
| 输出文件名 | alice.out | mountain.out | sequence.out | color.out |
| 每个测试点时限 | 1 秒 | 1 秒 | 1 秒 | 1 秒 |
| 内存限制 | 512 MiB | 512 MiB | 512 MiB | 512 MiB |
| 测试点数目 | 11 | 81 | 10 | 10 |
| 测试点是否等分 | 否（各点分值不同） | 否（分组捆绑） | 是（每点 10 分） | 是（每点 10 分） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | alice.cpp | mountain.cpp | sequence.cpp | color.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 登山按数据范围表分组捆绑，每组全部通过才得分。其余题目各点独立计分。所有题目采用全文比较评测。


## 机器（alice）




### 题目描述

Alice 喜欢数，尤其是 $l\sim r$ 之间的所有整数。狂热的Alice认为，自己拥有 $l\sim r$ 之间的所有整数。

某一天，Alice获得了一台机器，这台机器可以接受一个输入 $x$ ，接着，这台机器会自动找到离 $x$ 最近的完全平方数 $y^2$ （换句话说，机器的目标是使 $\left\vert x-y^2\right\vert $ 最小）。接着，机器将会根据 $y$ 的奇偶性作出不同反应：

* 如果 $y$ 是奇数，那么机器会奖励使用者 $x$ 个金币；

* 如果 $y$ 是偶数，机器就会要收取 $x$ 个金币作为费用；

* 特别地，如果离 $x$ 最近的完全平方数不止一个，那么机器将会直接损坏。

Alice希望将自己“拥有”的所有整数全部输入机器，不过她想先计算一下，自己总共会获得多少金币，或者需要支付多少金币。

Alice告诉我们，她初始拥有 ${10}^{1000}$ 个金币。假设她将 $l\sim\ r$ 之间的所有整数全部输入机器后，会剩余 $a$ 枚金币，请你输出 $\left(a-{10}^{1000}\right)\bmod\ {10}^9+7$ 的值。特别地，如果机器在中途会损坏，请输出 `Game Over`（区分大小写）。

### 输入格式


输入一行，两个整数 $l,\ r$ 。

### 输出格式


输出一行，一个整数代表答案对 ${10}^9+7$ 取模的结果。



### 样例 1 输入


```
10 20
```

### 样例 1 输出


```
999999908
```


### 样例 2 输入


```
1919 114514
```

### 样例 2 输出


```
968970539
```


### 样例 3 输入


```
123456789 1145141919810
```

### 样例 3 输出


```
809956222
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 4 | `alice4.in`、`alice4.ans` |

### 数据范围


各测试点独立计分，测试点 1～5 每点 $8$ 分，测试点 6～11 每点 $10$ 分。

对于 $40\%$ 的数据， $r\le{10}^3$ 。

对于 $80\%$ 的数据， $r\le{10}^6$ 。

对于 $100\%$ 的数据， $1\le\ l\le\ r\le{10}^{18}$ 。

## 登山（mountain）




### 题目描述

Cuber QQ 和 Little Fang 正在进行一场奇妙的登山旅行。山脉由 $n+2$ 座排成直线的山峰/山谷组成，两位登山者初始时分别位于最左端（位置 0）和最右端（位置 $n+1$），起点海拔均为 $0$。  中间 $n$ 个位置的海拔由序列 $h_1, h_2, \dots, h_n$ 描述。例如，下图展示了一个 $n=3$ 且 $h_1=2,h_2=1,h_3=3$ 的时候的山形图。





![1][import-statement-image-0]





Cuber QQ 和 Little Fang 为了保证安全，在移动过程中必须保持对讲机畅通——**任意时刻**两人所在位置的海拔必须相同。  相邻位置由线段连接，两人沿这条折线连续移动，可以停留或往返。这可能导致有时候两个人必须走回头路，才能最终汇合。

请判断两位登山者能否在某个位置成功汇合。

### 输入格式


第一行一个整数 $n$ 。

第二行 $n$ 个整数 $h_1, h_2, \dots, h_n$ ，表示位置 $1$ 到 $n$ 的海拔。

### 输出格式


输出一行，若可汇合输出 `Yes`；否则输出 `No`。


### 样例 1 输入


```
3
2 1 3
```

### 样例 1 输出


```
Yes
```

### 样例 1 解释


两人可在位置 $3$（海拔 $3$）汇合，海拔变化 $0 \to 1 \to 2 \to 1\to 2 \to 3$。也就是说 Little Fang 在中间需要回头走一段路。


### 样例 2 输入


```
2
-1 1
```

### 样例 2 输出


```
No
```







### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `mountain3.in`、`mountain3.ans` |
| 4 | `mountain4.in`、`mountain4.ans` |
| 5 | `mountain5.in`、`mountain5.ans` |

其中 $n=300007$。

### 数据范围


本题采用子任务捆绑计分，通过一个子任务内的全部测试点才能获得该子任务的分数。

| 子任务编号 | 测试点编号 | 额外限制 | 分值 |
| --- | --- | --- | --- |
| 1 | 1～20 | $1\le n\le50$ | 20 |
| 2 | 21～30 | $0\le h_i\le10^9$ | 10 |
| 3 | 31～60 | $1\le n\le10^5$ | 30 |
| 4 | 61～81 | 无 | 40 |

对于 $100\%$ 的数据范围， $1 \leq n \leq 5 \times 10^6, \ -10^9 \leq h_i \leq 10^9$ 。

**本题输入输出量较大，请使用较快的 IO 方式** 。

## 数列（sequence）




### 题目描述

Z神有 $N$ 个整数 $A_1,\ldots,A_N$ ，他打算执行 $M$ 次操作，操作分为四种类型：

1. 给定 $l,r$ ，询问第 $l$ 个数到第 $r$ 个数的和。

2. 给定 $l,r$ ，询问第 $l$ 个数到第 $r$ 个数的平方和。

3. 给定 $l,r,p$ ，将第$l$个数到第$r$个数每个数都除以 $p$ （保证 $p\neq 0$ ）。这里有一个特别的规则，由于Z神喜欢整数，所以他会在这种操作之后，把每个数 $A_i$ 都变成不超过 $A_i$ 本身的最大整数，例如他会把 $23.33$ 变成 $23$ ，把 $-23.33$ 变成 $-24$ 。

4. 给定 $pos,v$ ，将第 $pos$ 个数修改为 $v$ 。

对于每次 $opt=1$ 或者 $2$ ，请你计算答案对 ${10}^9+7$ 取模的结果。

### 输入格式


第一行两个整数 $N,M$ 。

接下来一行 $N$ 个数，代表一开始 $N$ 个数的值。

接下来 $M$ 行，每行第一个整数 $opt$ 代表操作类型。如果 $opt=1$ 或者 $opt=2$ ，那么接下来会有两个整数 $l,r$ ；如果 $opt=3$ ，那么接下来会有三个整数 $l,r,p$ ；如果 $opt=4$ ，那么接下来会有两个整数 $pos,v$ 。

### 输出格式


对于每次 $opt=1$ 或者 $2$ ，输出一行一个非负整数代表答案对 ${10}^9+7$ 取模的结果


### 样例 1 输入


```
5 5
1 2 3 4 5
1 1 5
2 1 5
3 1 5 5
1 1 5
2 1 5
```

### 样例 1 输出


```
15
55
1
1
```







### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `sequence2.in`、`sequence2.ans` |
| 3 | `sequence3.in`、`sequence3.ans` |
| 4 | `sequence4.in`、`sequence4.ans` |

其中 $N=M=10^5$。

### 数据范围


对于 $20\%$ 的数据， $N,M\le 100$ 。

对于另外 $20\%$ 的数据， $opt\neq 3,4$ 。

对于另外 $20\%$ 的数据， $opt\neq 3$ 。

对于另外 $20\%$ 的数据， $a_i,v,p>0$ 。

对于 $100\%$ 的数据， $1\le\ N,M\le{10}^5,-{10}^9\le\ a_i,v,p\le{10}^9,1\le\ pos\le\ N,1\le\ l\le\ r\le\ N$ 。

## 染色（color）




### 题目描述

alice给出了一个 $n$ 个节点的树。

bob对这棵树进行了黑白染色，即将每个点染成黑色或者白色，显然一共有 $2^n$ 种方案。

树上两点的距离定义为两点之间最短路径上经过的边数。

设所有黑点中最远点对的距离为 $x$，白点中最远点对距离为 $y$，特别地，当图中不存在白色点，$y=0$，同理当图中不存在黑色点时，$x=0$。

一种染色的权值定义为 $\max(x,y)$，bob会等概率随机给这张图进行黑白染色，他想知道最终染色的权值的期望值，由于答案可能是个分数，你只需要输出答案对 $2^n$ 相乘后的结果，答案对 $10^9+7$ 取模。

### 输入格式


输入第一行，包含 $1$ 个正整数 $n$。

之后 $n-1$ 行，每行给定 $x_i,y_i$，表示图中的一条边。

### 输出格式


输出一行，包含一个整数，表示答案，答案对 $10^9+7$ 取模。


### 样例 1 输入


```
3
1 2
1 3
```

### 样例 1 输出


```
12
```

### 样例 1 解释


$0$ 表示黑色，$1$ 表示白色。

$\text{value}(000)=\text{value}(011)=\text{value}(100)=\text{value}(111)=2$。

$\text{value}(001)=\text{value}(010)=\text{value}(101)=\text{value}(110)=1$。


### 样例 2 输入


```
6
1 2
2 3
3 4
4 5
3 6
```

### 样例 2 输出


```
224
```


### 样例 3 输入


```
35
25 4
33 7
11 26
32 4
12 7
31 27
19 6
10 22
17 12
28 24
28 1
24 15
30 24
24 11
23 18
14 15
4 29
33 24
15 34
11 3
4 35
5 34
34 2
16 19
7 18
19 31
22 8
13 26
20 6
20 9
4 33
4 8
29 19
15 21
```

### 样例 3 输出


```
298219707
```





### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 4 | `color4.in`、`color4.ans` |
| 5 | `color5.in`、`color5.ans` |

其中 $n=2\times10^5$。

### 数据范围


对于 $10\%$ 的数据，$1 \leq n \leq 20$ 。

对于 $40\%$ 的数据，$1 \leq n \leq 10^3$ 。

对于 $100\%$ 的数据，$1 \leq n \leq 200000$ 。
[import-statement-image-0]: data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAL4AAACVCAYAAADmH0BoAAAAAXNSR0IArs4c6QAAF3J0RVh0bXhmaWxlACUzQ214ZmlsZSUyMGhvc3QlM0QlMjJhcHAuZGlhZ3JhbXMubmV0JTIyJTIwYWdlbnQlM0QlMjJNb3ppbGxhJTJGNS4wJTIwKE1hY2ludG9zaCUzQiUyMEludGVsJTIwTWFjJTIwT1MlMjBYJTIwMTBfMTVfNyklMjBBcHBsZVdlYktpdCUyRjUzNy4zNiUyMChLSFRNTCUyQyUyMGxpa2UlMjBHZWNrbyklMjBDaHJvbWUlMkYxMzguMC4wLjAlMjBTYWZhcmklMkY1MzcuMzYlMjIlMjB2ZXJzaW9uJTNEJTIyMjYuMS4zJTIyJTIwc2NhbGUlM0QlMjIxJTIyJTIwYm9yZGVyJTNEJTIyMCUyMiUzRSUwQSUyMCUyMCUzQ2RpYWdyYW0lMjBuYW1lJTNEJTIyJUU3JUFDJUFDJTIwMSUyMCVFOSVBMSVCNSUyMiUyMGlkJTNEJTIycVd5TTM1VXRMZ0dmaDdxWE1rWkMlMjIlM0UlMEElMjAlMjAlMjAlMjAlM0NteEdyYXBoTW9kZWwlMjBkeCUzRCUyMjEwMjYlMjIlMjBkeSUzRCUyMjY4NCUyMiUyMGdyaWQlM0QlMjIxJTIyJTIwZ3JpZFNpemUlM0QlMjIxMCUyMiUyMGd1aWRlcyUzRCUyMjElMjIlMjB0b29sdGlwcyUzRCUyMjElMjIlMjBjb25uZWN0JTNEJTIyMSUyMiUyMGFycm93cyUzRCUyMjElMjIlMjBmb2xkJTNEJTIyMSUyMiUyMHBhZ2UlM0QlMjIxJTIyJTIwcGFnZVNjYWxlJTNEJTIyMSUyMiUyMHBhZ2VXaWR0aCUzRCUyMjgyNyUyMiUyMHBhZ2VIZWlnaHQlM0QlMjIxMTY5JTIyJTIwbWF0aCUzRCUyMjAlMjIlMjBzaGFkb3clM0QlMjIwJTIyJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTNDcm9vdCUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214Q2VsbCUyMGlkJTNEJTIyMCUyMiUyMCUyRiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214Q2VsbCUyMGlkJTNEJTIyMSUyMiUyMHBhcmVudCUzRCUyMjAlMjIlMjAlMkYlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteENlbGwlMjBpZCUzRCUyMkZFSXNnZW9OeDFsM19yTzBZNkRyLTElMjIlMjB2YWx1ZSUzRCUyMiUyMiUyMHN0eWxlJTNEJTIyZW5kQXJyb3clM0Rub25lJTNCaHRtbCUzRDElM0Jyb3VuZGVkJTNEMCUzQiUyMiUyMGVkZ2UlM0QlMjIxJTIyJTIwcGFyZW50JTNEJTIyMSUyMiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214R2VvbWV0cnklMjB3aWR0aCUzRCUyMjUwJTIyJTIwaGVpZ2h0JTNEJTIyNTAlMjIlMjByZWxhdGl2ZSUzRCUyMjElMjIlMjBhcyUzRCUyMmdlb21ldHJ5JTIyJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhQb2ludCUyMHglM0QlMjIzNjAlMjIlMjB5JTNEJTIyMzYwJTIyJTIwYXMlM0QlMjJzb3VyY2VQb2ludCUyMiUyMCUyRiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214UG9pbnQlMjB4JTNEJTIyNDAwJTIyJTIweSUzRCUyMjI4MCUyMiUyMGFzJTNEJTIydGFyZ2V0UG9pbnQlMjIlMjAlMkYlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0MlMkZteEdlb21ldHJ5JTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDJTJGbXhDZWxsJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhDZWxsJTIwaWQlM0QlMjJGRUlzZ2VvTngxbDNfck8wWTZEci0yJTIyJTIwdmFsdWUlM0QlMjIlMjIlMjBzdHlsZSUzRCUyMmVuZEFycm93JTNEbm9uZSUzQmh0bWwlM0QxJTNCcm91bmRlZCUzRDAlM0IlMjIlMjBlZGdlJTNEJTIyMSUyMiUyMHBhcmVudCUzRCUyMjElMjIlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteEdlb21ldHJ5JTIwd2lkdGglM0QlMjI1MCUyMiUyMGhlaWdodCUzRCUyMjUwJTIyJTIwcmVsYXRpdmUlM0QlMjIxJTIyJTIwYXMlM0QlMjJnZW9tZXRyeSUyMiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214UG9pbnQlMjB4JTNEJTIyNDQwJTIyJTIweSUzRCUyMjMyMCUyMiUyMGFzJTNEJTIyc291cmNlUG9pbnQlMjIlMjAlMkYlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteFBvaW50JTIweCUzRCUyMjQwMCUyMiUyMHklM0QlMjIyODAlMjIlMjBhcyUzRCUyMnRhcmdldFBvaW50JTIyJTIwJTJGJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDJTJGbXhHZW9tZXRyeSUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQyUyRm14Q2VsbCUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214Q2VsbCUyMGlkJTNEJTIyRkVJc2dlb054MWwzX3JPMFk2RHItMyUyMiUyMHZhbHVlJTNEJTIyMCUyMiUyMHN0eWxlJTNEJTIydGV4dCUzQmh0bWwlM0QxJTNCYWxpZ24lM0RjZW50ZXIlM0J2ZXJ0aWNhbEFsaWduJTNEbWlkZGxlJTNCcmVzaXphYmxlJTNEMCUzQnBvaW50cyUzRCU1QiU1RCUzQmF1dG9zaXplJTNEMSUzQnN0cm9rZUNvbG9yJTNEbm9uZSUzQmZpbGxDb2xvciUzRG5vbmUlM0IlMjIlMjB2ZXJ0ZXglM0QlMjIxJTIyJTIwcGFyZW50JTNEJTIyMSUyMiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214R2VvbWV0cnklMjB4JTNEJTIyMzQ1JTIyJTIweSUzRCUyMjM1OCUyMiUyMHdpZHRoJTNEJTIyMzAlMjIlMjBoZWlnaHQlM0QlMjIzMCUyMiUyMGFzJTNEJTIyZ2VvbWV0cnklMjIlMjAlMkYlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0MlMkZteENlbGwlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteENlbGwlMjBpZCUzRCUyMkZFSXNnZW9OeDFsM19yTzBZNkRyLTQlMjIlMjB2YWx1ZSUzRCUyMjElMjIlMjBzdHlsZSUzRCUyMnRleHQlM0JodG1sJTNEMSUzQmFsaWduJTNEY2VudGVyJTNCdmVydGljYWxBbGlnbiUzRG1pZGRsZSUzQnJlc2l6YWJsZSUzRDAlM0Jwb2ludHMlM0QlNUIlNUQlM0JhdXRvc2l6ZSUzRDElM0JzdHJva2VDb2xvciUzRG5vbmUlM0JmaWxsQ29sb3IlM0Rub25lJTNCJTIyJTIwdmVydGV4JTNEJTIyMSUyMiUyMHBhcmVudCUzRCUyMjElMjIlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteEdlb21ldHJ5JTIweCUzRCUyMjM4NSUyMiUyMHklM0QlMjIzNTglMjIlMjB3aWR0aCUzRCUyMjMwJTIyJTIwaGVpZ2h0JTNEJTIyMzAlMjIlMjBhcyUzRCUyMmdlb21ldHJ5JTIyJTIwJTJGJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDJTJGbXhDZWxsJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhDZWxsJTIwaWQlM0QlMjJGRUlzZ2VvTngxbDNfck8wWTZEci01JTIyJTIwdmFsdWUlM0QlMjIyJTIyJTIwc3R5bGUlM0QlMjJ0ZXh0JTNCaHRtbCUzRDElM0JhbGlnbiUzRGNlbnRlciUzQnZlcnRpY2FsQWxpZ24lM0RtaWRkbGUlM0JyZXNpemFibGUlM0QwJTNCcG9pbnRzJTNEJTVCJTVEJTNCYXV0b3NpemUlM0QxJTNCc3Ryb2tlQ29sb3IlM0Rub25lJTNCZmlsbENvbG9yJTNEbm9uZSUzQiUyMiUyMHZlcnRleCUzRCUyMjElMjIlMjBwYXJlbnQlM0QlMjIxJTIyJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhHZW9tZXRyeSUyMHglM0QlMjI0MjUlMjIlMjB5JTNEJTIyMzU4JTIyJTIwd2lkdGglM0QlMjIzMCUyMiUyMGhlaWdodCUzRCUyMjMwJTIyJTIwYXMlM0QlMjJnZW9tZXRyeSUyMiUyMCUyRiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQyUyRm14Q2VsbCUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214Q2VsbCUyMGlkJTNEJTIyRkVJc2dlb054MWwzX3JPMFk2RHItNiUyMiUyMHZhbHVlJTNEJTIyJTIyJTIwc3R5bGUlM0QlMjJlbmRBcnJvdyUzRG5vbmUlM0JodG1sJTNEMSUzQnJvdW5kZWQlM0QwJTNCJTIyJTIwZWRnZSUzRCUyMjElMjIlMjBwYXJlbnQlM0QlMjIxJTIyJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhHZW9tZXRyeSUyMHdpZHRoJTNEJTIyNTAlMjIlMjBoZWlnaHQlM0QlMjI1MCUyMiUyMHJlbGF0aXZlJTNEJTIyMSUyMiUyMGFzJTNEJTIyZ2VvbWV0cnklMjIlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteFBvaW50JTIweCUzRCUyMjQ4MCUyMiUyMHklM0QlMjIyNDAlMjIlMjBhcyUzRCUyMnNvdXJjZVBvaW50JTIyJTIwJTJGJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhQb2ludCUyMHglM0QlMjI0NDAlMjIlMjB5JTNEJTIyMzIwJTIyJTIwYXMlM0QlMjJ0YXJnZXRQb2ludCUyMiUyMCUyRiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQyUyRm14R2VvbWV0cnklM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0MlMkZteENlbGwlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0NteENlbGwlMjBpZCUzRCUyMkZFSXNnZW9OeDFsM19yTzBZNkRyLTclMjIlMjB2YWx1ZSUzRCUyMiUyMiUyMHN0eWxlJTNEJTIyZW5kQXJyb3clM0Rub25lJTNCaHRtbCUzRDElM0Jyb3VuZGVkJTNEMCUzQiUyMiUyMGVkZ2UlM0QlMjIxJTIyJTIwcGFyZW50JTNEJTIyMSUyMiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214R2VvbWV0cnklMjB3aWR0aCUzRCUyMjUwJTIyJTIwaGVpZ2h0JTNEJTIyNTAlMjIlMjByZWxhdGl2ZSUzRCUyMjElMjIlMjBhcyUzRCUyMmdlb21ldHJ5JTIyJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhQb2ludCUyMHglM0QlMjI0ODAlMjIlMjB5JTNEJTIyMjQwJTIyJTIwYXMlM0QlMjJzb3VyY2VQb2ludCUyMiUyMCUyRiUzRSUwQSUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUyMCUzQ214UG9pbnQlMjB4JTNEJTIyNTIwJTIyJTIweSUzRCUyMjM2MCUyMiUyMGFzJTNEJTIydGFyZ2V0UG9pbnQlMjIlMjAlMkYlM0UlMEElMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlMjAlM0MlMkZteEdlb21ldHJ5JTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDJTJGbXhDZWxsJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhDZWxsJTIwaWQlM0QlMjJGRUlzZ2VvTngxbDNfck8wWTZEci04JTIyJTIwdmFsdWUlM0QlMjIzJTIyJTIwc3R5bGUlM0QlMjJ0ZXh0JTNCaHRtbCUzRDElM0JhbGlnbiUzRGNlbnRlciUzQnZlcnRpY2FsQWxpZ24lM0RtaWRkbGUlM0JyZXNpemFibGUlM0QwJTNCcG9pbnRzJTNEJTVCJTVEJTNCYXV0b3NpemUlM0QxJTNCc3Ryb2tlQ29sb3IlM0Rub25lJTNCZmlsbENvbG9yJTNEbm9uZSUzQiUyMiUyMHZlcnRleCUzRCUyMjElMjIlMjBwYXJlbnQlM0QlMjIxJTIyJTNFJTBBJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTIwJTNDbXhHZW9tZXRyeSUyMHglM0QlMjI0NjUlMjIlMjB5JTNEJTIyMzU4JTIyJTIwd2lkdGglM0QlMjIzMCUyMiUyMGhlaWdodCUzRCUyMjMwJTIyJTIwYXMlM0QlMjJnZW9tZXRyeSUy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
