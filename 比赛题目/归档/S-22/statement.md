# 提高组模拟赛

第 22 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 队列 | compare | 异或 | 城市 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型（SPJ） |
| 目录 | queue | compare | xor | city |
| 可执行文件名 | queue | compare | xor | city |
| 输入文件名 | queue.in | compare.in | xor.in | city.in |
| 输出文件名 | queue.out | compare.out | xor.out | city.out |
| 每个测试点时限 | 1 秒 | 2 秒 | 1 秒 | 1 秒 |
| 内存限制 | 512 MiB | 512 MiB | 512 MiB | 512 MiB |
| 测试点数目 | 20 | 20 | 20 | 20 |
| 测试点是否等分 | 否（分组捆绑） | 是（每点 5 分） | 否（分组捆绑） | 否（分组捆绑） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | queue.cpp | compare.cpp | xor.cpp | city.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 队列、异或、城市按数据范围表分组捆绑，每组全部通过才得分。其余题目各点独立计分。城市采用 Special Judge；其余题目采用全文比较评测。


## 队列（queue）




### 题目描述

作为霍格沃兹学校的一名老师，为了保持秩序，你正在让学生列队。

你喜欢规律，所以你希望每相邻两个学生之间的身高差相同，并且你希望学生从矮往高排。

具体的，记从队首数起的第 $i$ 名学生身高为 $a_i$，你希望对于所有的 $i=2,3\cdots n$，都有 $a_i-a_{i-1}=V$，其中 $V$ 为一个大于等于 $0$ 的常数。

但学生们的身高参差不齐，所以你打算使用你最擅长的魔法，去修改学生的身高。

但因为奇怪的校规，每个学生的身高在变化之前和变化之后都必须是在 $[1,w]$ 范围内的正整数。

你一次魔法只能修改一个同学的身高，你想知道你最少需要使用多少次魔法才能得到你喜欢的队列。

### 输入格式


第一行两个整数 $n, w$，表示学生个数和身高上限。

接下来一行 $n$ 个整数 $a_1, a_2, \ldots , a_n$，表示每个学生的初始身高。

### 输出格式


一行一个整数，所求答案。



### 样例 1 输入


```
10 2
2 1 2 2 1 1 2 2 2 2
```

### 样例 1 输出


```
3
```


### 样例 2 输入


```
6 1000
1 2 999 4 72 6
```

### 样例 2 输出


```
2
```







### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `queue3.in`、`queue3.ans` |
| 4 | `queue4.in`、`queue4.ans` |
| 5 | `queue5.in`、`queue5.ans` |

### 数据范围

本题采用子任务捆绑计分，通过同一子任务内的全部测试点才能获得该子任务的分数，各子任务的分数相加。

对于全部测试数据，$1\le n,w\le3\times10^5$，$1\le a_i\le w$。

| 子任务编号 | 测试点编号 | 分值 | 附加限制 |
|---|---|---|---|
| 1 | 1～4 | 10 | $n,w\le2$ |
| 2 | 5～8 | 20 | $n,w\le100$ |
| 3 | 9～10 | 5 | 所有 $a_i=1$ |
| 4 | 11～20 | 65 | 无 |

## 比较（compare）




### 题目描述

有 $n$ 个人，$q$ 组询问。一开始这 $n$ 个人之间有 $m$ 组关系，每组关系为一个二元组 $(x,y)$ 表示 $x,y$ 初始为朋友关系。

定义一个人的强度为其编号，定义一个人所处的朋友圈为和他有间接或直接朋友关系的人的集合（包括他自己）。如果把每个人视作图上一个点，朋友关系视作边，那么朋友圈就是一个连通块对应的点集。

有 3 种操作：

- $1 \space u \space v (1 \le u,v \le n,u \ne v)$ 表示 $u$ 和 $v$ 变成了朋友。保证 $u$ 和 $v$ 在此次操作之前不是朋友。

- $2 \space u \space v (1 \le u,v \le n,u \ne v)$ 表示 $u$ 和 $v$ 发生了矛盾，不是朋友了。保证 $u$ 和 $v$ 在此次操作之前是朋友。

- $3$ 表示执行以下操作直至不可再执行为止。在每个 **大小大于 1** 的朋友圈中进行一次攀比，找到强度最小的人，将这个人暂时踢出朋友圈（即所有和这个人是朋友的暂时删去和这个人的朋友关系，同时因为这个人被踢出，一个朋友圈可能会暂时分裂成多个朋友圈）。在所有操作执行完毕后，请你输出有多少人没有被踢出朋友圈。**注意，每个 3 操作之间彼此独立**。即删人只是暂时的，这次操作结束之后所有被删的人连同边会恢复操作三之前的状态。

### 输入格式


第一行两个正整数 $n,m$，意义见题目描述。

接下来 $m$ 行每行两个正整数 $u,v$ 表示 $u,v$ 两个人一开始是朋友。

接下来一行一个正整数 $q$ 代表操作次数。

接下去 $q$ 行每行一个操作，具体的格式参考题目描述。

### 输出格式


对于每个 $3$ 操作，输出一行一个正整数，即最后没有被踢出朋友圈的人数。


### 样例 1 输入


```
4 3
2 1
1 3
3 4
4
3
1 2 3
2 3 1
3
```

### 样例 1 输出


```
2
1
```


### 样例 2 输入


```
4 3
2 3
3 4
4 1
1
3
```

### 样例 2 输出


```
1
```







### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `compare3.in`、`compare3.ans` |
| 4 | `compare4.in`、`compare4.ans` |
| 5 | `compare5.in`、`compare5.ans` |

### 数据范围


对于 $20\%$ 数据， $n, m, q \le 10$ 。

对于 $30\%$ 数据， $n, m, q \le 500$ 。

对于另外 $10\%$ 数据， $n, m, q \le 10^5$ ，保证每个点度数时刻不超过 $2$ 。

对于另外 $10\%$ 数据， $n, m, q \le 10^5$ ，保证每个点度数时刻不超过 $3$ 。

对于另外 $10\%$ 数据， $n, m, q \le 10^5$ ，没有操作 $2$ 。

对于 $100\%$ 的数据，$2\le n\le10^5,\ 1\le m,q\le10^5,\ 1\le u,v\le n,\ u\ne v$。

## 异或（xor）




### 题目描述

这次又轮到你来让学生列队了，与之前相反，今天你想制造一点不规律。

可惜的是，今天 $n$ 名学生已经按照从矮到高排队排好了。

于是今天你想试试新魔法，每次选择两个相邻的人，把他们合并成一个连体人，并且连体人的身高是合并前两个人身高的按位异或结果。

你希望用最少魔法次数**破坏**整个队列的**不降**，即存在一个人比他后面的人高。

### 输入格式


本题采用多组测试数据。

第一行一个正整数 $T$ 表示数据组数。

对于每组测试数据：

第一行一个整数 $n$，表示学生个数。

接下来一行 $n$ 个整数 $a_1, a_2, \ldots , a_n$，表示每个学生的初始身高。

### 输出格式


对于每组测试数据，输出一个正整数，表示破坏队列不降需要的最少魔法次数，如果无论如何都达不到，输出 $-1$ 即可。


### 样例 1 输入


```
1
4
2 5 6 8
```

### 样例 1 输出


```
1
```


### 样例 2 输入


```
2
5
1 2 4 6 20
3
1 2 3
```

### 样例 2 输出


```
2
-1
```







### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `xor3.in`、`xor3.ans` |
| 4 | `xor4.in`、`xor4.ans` |
| 5 | `xor5.in`、`xor5.ans` |

### 数据范围

本题采用子任务捆绑计分，通过同一子任务内的全部测试点才能获得该子任务的分数，各子任务的分数相加。

对于全部测试数据，$1\le T\le10^5$，$\sum n\le2\times10^5$，$2\le n\le10^5$，$1\le a_i\le10^9$，且 $a_i\le a_{i+1}$（$1\le i<n$）。

| 子任务编号 | 测试点编号 | 分值 | 附加限制 |
|---|---|---|---|
| 1 | 1～6 | 20 | $n\le400$；其中测试点 1～4 还满足 $n\le10$ |
| 2 | 7～8 | 5 | 所有数全相等 |
| 3 | 9～10 | 10 | 所有 $a_i$ 都是 $2$ 的幂 |
| 4 | 11～20 | 65 | 无 |

## 城市（city）




### 题目描述

B 国是一个拥有 $n$ 个城市的国家，n 个城市依次编号为 $1,2,\cdots ,n$ 。B 国的首脑计划在国内修建 $m$ 条城市间的单向道路。

如果从一个城市 $x$ 出发，经过若干条道路能够到达城市 $y$ ，我们就称 $x$ **可达** $y$ 。特殊的，我们认为每个城市都可达它本身。注意：$x$ 可达 $y$ 并不一定意味着 $y$ 可达 $x$ 。

对于一个城市的集合 $S$ ，如果 $S$ 中任意两个城市 $u,v$ 都满足 $u$ 可达 $v$ 且 $v$ 可达 $u$ ，那么我们称 $S$ 是**互通**的。特殊的，大小为 $1$ 的集合总是互通的。

如果一个互通的城市集合 $A$ 满足不存在另一个互通的城市集合 $B$ 使得 $A$ 是 $B$ 的真子集，那么我们称 $A$ 是一个**城市群**。

可以证明，对于任意的修建 $m$ 条城市间的道路的方案，总能够将 $n$ 个城市划分为若干个城市群，满足每个城市恰好属于一个城市群且每个城市群包含至少一个城市。

B 国的首脑要求这 $n$ 个城市恰好被划分成 $X$ 个城市群，他还有额外的 $q$ 个限制 $(a_i,b_i)$ ，要求城市 $a_i$ 与城市 $b_i$ 属于同一个城市群。

你需要构造一种修建 $m$ 条道路的方案满足首脑的要求，或者报告满足要求的方案不存在。

如果存在多种可能的方案，你可以输出任意一种。

注意：对于任意的两个城市 $u,v$ ，从 $u$ 到 $v$ 的道路只能修建至多一条；你不能修建从一个城市到它本身的道路。

### 输入格式


第一行四个整数 $n,m,X,q$ 。

接下来 $q$ 行每行两个正整数，第 $i+1$ 行的两个正整数分别表示 $a_i,b_i$ 。

### 输出格式


如果不存在满足要求的方案，输出一行一个整数 $−1$ 。

否则输出 $m$ 行，每行两个正整数 $s_i,t_i$ ，表示你的方案中修建了一条从 $s_i$ 到 $t_i$ 的单向道路。


### 样例 1 输入


```
5 7 2 1
2 3
```

### 样例 1 输出


```
2 5
3 2
4 3
5 4
2 3
2 4
3 4
```

### 样例 1 解释




![样例示意图][s-22-city-sample]




### 样例 2 输入


```
5 2 3 3
1 2
2 3
3 4
```

### 样例 2 输出


```
-1
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `city3.in`、`city3.ans` |

### 数据范围

本题采用子任务捆绑计分，通过同一子任务内的全部测试点才能获得该子任务的分数，各子任务的分数相加。

对于全部测试数据，$1\le n,m\le5\times10^5$，$0\le q\le5\times10^5$，$1\le X,a_i,b_i\le n$，$a_i\ne b_i$。

| 子任务编号 | 测试点编号 | 分值 | 附加限制 |
|---|---|---|---|
| 1 | 1～4 | 10 | $n,q\le5$ |
| 2 | 5～7 | 10 | $X=1$ |
| 3 | 8～10 | 10 | $X=n$ |
| 4 | 11～14 | 20 | $n\le2000$ |
| 5 | 15～20 | 50 | 无 |

[s-22-city-sample]: data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAABRQAAAFeCAIAAAB7CASmAAAe80lEQVR4nO3dDbxlY6H48eeMwzGYdzPI1HjLvYYoUV6qqyakSaSbq2Fq3NtEIkVe5k4K1zjUuDEIzR+jpImIMuWlESI0Mo0mryNEwhgGGfPm7PsZu//pdObMXufst/Wstb7fj8/97DH77P3c3X4669fzrLVaSqVSAAAAANasX4W/AwAAAMQzAAAAJLPyDAAAAAnEMwAAACQQzwAAAJBAPAMAAEAC8QwAAAAJxDMAAAAkEM8AAACQQDwDAABAAvEMAAAACcQzAAAAJBDPAAAAkEA8AwAAQALxDAAAAAnEMwAAACQQzwAAAJBAPAMAAEAC8QwAAAAJxDMAAAAkEM8AAACQQDwDAABAAvEMAAAACcQzAAAAJBDPAAAAkEA8AwAAQALxDAAAAAnEMwAAACQQzwAAAJBAPAMAAEAC8QwAAAAJxDMAAAAkEM8AAACQoDXpCRC1MRMmVX7C7BntzRoLZJV5BACQqKVUKiU/CzJ1oL8mQhrMIwCA6ohn8t/Mq1PRFJZ5BABQHfFMtg/3Z02fUvlnx06cvKa/ktAUinkEAFAL8Uz2DvcTg7lPIS2hyT3zCACgduKZLB3xV53NlRNaP5Nj5hEAQF2IZ7JxxF+XbK6Q0PqZXDKPAADqRTxTuMP9riQ0eWUeAQDUVz8fKIU94l/99et4IWJIkXkEAFB3Vp6J9Ii/0dlcYQnaFm4yzTwCAGgEK8/EIsUj/m7vaP2Z7DKPAAAaRDwThXSP+Fd/X/1MFplHAACNI56JS1rlHMO7Q72YRwAAdSeeiWi5LIZ27RyDxWeyxTwCAGgo8UzKYm7UmMcGdf+uLnl96bwHHrnlznvvmDPvkT/9uaNUqsuHbB4BAPngattk+xTNeQ88evBRJ1V+zgd2edd3ppzQp5d18W0KNY/mzn/4osuvuWfuH1esXNn5LwcPHPDRD+02cdwnhg8bXN3AzCMAIE+sPBOFqjdsP/ynJ0MDxLCBHJrwvV258o3Tpl0y/uhv3DFnXtdyDiEsfuXVK669cd9Dj7n9nrnV/WdhHgEAeSKeSU1dNnM+/FhD4rkrm06JWS3fz45S6csn/+/M624KIbSts/Yn9vngNycfdfHUk8459diJ4/YfMWxICOFvry05cvI3q+7nuowTACAGrWkPAGpanirH81s22vCmK86r70c5a/qUrptOIX/z6LxLr7z1rt+FELbZarOzTzl2042Hd/7VmN13Pnz8J888/7Irr/9lR6l03GnTrp/x7Sr2b5tHAEBuWHkmHXVZhiqVSo8+/lQIYestRoVGsmhGnGr5Zj7z3AuX/uhnIYRNNx7x/6Z+rWs5l7Wts/bXv/K5Az/24RDCa0tev/Dyq1McLQBA6sQzGV52fvqvz7+25PU34/ltoQGcsUlWVPFdveLaG8onOZ9wxGcGDdhgTU87/ojx5f3bN/zqro6OjuaMDQAgQuKZDOs84flfGhPPkGO3/mbVhu0RGw794G7vrvC0ddva9vngbiGEl1/925/+/EwTBwgAEBfxTAo6d2/WuCTVGc+N27bdOUI7TsnTPFry+tInnv5rCGH3nbZvaWmp/OQtRm1afvDCi4urGql5BADkgXgmw8r3qWprW2fUyI1DlCQ3cVr44uIRGw4dseHQ0VtvkfjkN954o/ygdS2/MgCA4nK1bTKsvPK81WYj+/WL7pheNhOzUZtufMuPvtPLJy944unyg003GdHIQQEARE08k1V/e23JX55d+OY1t8Np0y7548N/WvTS4paWluHDhrznndvu++H3b/62t6QyMNlMnnR0dMy+c86bF+UevsmIDdMeDgBAalpKpVJ6704R1euE59/94aHPfvnkNf1tv379Pr3/XscdNr61da1Qs84bPs+e0d7XbK78I5DuPEr0g5/c0H7ejBDCkRMOPHz8AU2YRwAAcbLyTLb3bK+11lrbb7PV6K03H7nxiP7rtr308qtz5z98x5x5HR0dP7jmhseeePr8KSe0rbN2owdjtZlceuzJp789/YchhGFDBh3yyX3SHg4AQJrEM1nV0tJy8jET9/rALgMHrN/tr5546pnjTpv24IIn7r5vfvt5M04+ZmKDxqCZybFXXn3tSydNXbpsWQjh5GM+v8F6/dMeEQBAmsQzWfXp/fZa019t9ta3XHb2yQcfddKjjz/141mzP77X+3fc7l/TqmWBTRatWLny6G+c9eRfng0hHHzARyrfCxoAoAiiu0Yx1MV6/dedcsIR5ceXzPyZTxV6r1QqTT7zgjnzHggh7LzD6OMOG+/TAwAQz+TW6LdvXl5wvut39y9fsSLt4UBmnH7upT+/5c7yJo6zTzmmLlfdAwDIOvFMnu20wzYhhGXLVzy0YNXVxYBE37rg+z+87qYQwvBhgy86Y9KgARv40AAAnPNMzg0fNqT84IUXF9flBTtvsdP7M5ndlYdGaNC59N+efsVlP54VQhg4YP3vnjl5042HN+JdAACyyMozebZs2fLyg/IVg+to9ox2VUzOnHvplRfP/GkIof+6bRecfuLbN39r2iMCAIiIq22TZ08/+3z5weCBAxrx+lUsREOcLvj+1Rddfk0IYe3W1mmnfnWH0W9Pe0QAAHERz2TMb3//xxlXXR9COPBjH95j10q3zymVSnfOmVd+/Na3bNTQUZUrWkKTUdOvuPb8GVet2ozUr983Jx+167vfkfaIAACiY9s2zda5Wjt24uQqfnzQgA1uv3vu7XfP/dFPb678zJt//dunnnkuhLDpxsNriefOcSbu07aXm6zMo65mXHn9ORfPLD8++ZiJe37gvaEBej+PAADiJJ7JmK23eFu5hH/929/fN/+hNT3t+RdenDLtkvLj/fb+tyYOUEKTJT+45oapF11efvzVww45YJ8Ppj0iAIBIiWcypqWl5ZBP7FN+fOypZz/6+FOrP+fJvzw74ZhTF730cnmlevwBf39+M1mFJn4zr7up/fwZ5ccTx+0/4cCPpT0iAIB4OeeZ7Dlovz2vvfHWBxc8sXDR4oOO+O9P77/32DHv2+Ktb3mjo+OJp575+a9+88Nrb1y2fEW5tNtP/OKADdZPa6h2qBKtH8+aPeXcSzv/OP2Ka6dfcW3lH/nQ7jtNO/WrjR8aAECMWkqlUtpjoIg6r601a/qUKn78uYUvHvKlr//1+RcqPKdfS8vkL/3nf3x8z1ADJ2qSy3l07Y23nfStC/v63/9Vx7N5BADkgJVnMmmj4UNnfmfK8VOm3TP3jz0+YeQmIyZ/6T/f/553Nn1okAH77/1v+zf3WgAAAFknnknZ2ImTq1t8HjZk0MVTT7pjzryf3Xz73PkPv/Diy62taw0bMmjbrbfYY9cdP7LHbq2ta9U+thpfASKfR01gHgEA+SCeScfsGe11uSvy+3be4X077xAazKnL5HseNYd5BABkmqttk744F6biHBVk6xsb56gAAKognklNVpahsjJOiikr38+sjBMAYE3EM1GIbXkqtvFAFr+3sY0HAKAW4plYFqPiOc7uOhLLZcTPPAIAaALxTMpirtOYxwadIr9mmHkEAORDS6lUSnsM8I+j/9Rvt9O57OyIn+xms3kEAFB3Vp6JS7qbt+PZOg61LDibRwAAdSeeiUIMJ2061Zmsl7N5BADQOLZtE2kPNHnfqXIm0+XcNZvNIwCARhDPRF0FTUjobgvdTnUm0wvOPT7NPAIAqJ1t28SlWwY0egu3ciZ/5WweAQA0gpVnItXopTPZTF7LucJPmUcAAFUTz2SpFupy6L/6arat2mT6JOe+/qx5BABQBfFM9lbbqj7073ETuHImZtUtOPfmRcwjAIA+Ec9k+362iQFQ4axp2UwRyrnyq5WZRwAAicQzmVHh0L+vZDNFK+fKL1sd8wgAKBTxTPZUffTvWJ8iZ3Nv3qU3zCMAoJjEM9mWGAAO9MmW5pRzb960mQMAAIifeCY/ugaAY32yKJVyrjAA8wgAoFPrPx4CkM37UQEA0GjiGaDoC84AACTql/wUABpGOQMAZIJ4BkiNcgYAyArbtgFSEGE2rz6kMRMm2T0OAFBm5Rmg2SIsZwAAKhPPAE0VZzmv6VbPibeABgAoCNu2AZrH/agAADLKyjNAM4yZMCnacq68vGzxGQBAPAMUd6s2AAC9Z+UZoNDl3JuFZYvPAADOeQZooGi3agMA0CdWngEKd5JzFUvKFp8BgIITzwCF26oNAEBfiWeAgpZzXxeTLT4DAEXmnGeAwmUzAAB9JZ4BClrOq4+t2/8LMQ8eAKDJbNsGKGI5AwDQJ1aeAWoV/1W1AQCokXgGqJ4FZwCAgrBtG6BKyhkAoDjEM0A1lDMAQKHYtg3QZ05yBgAoGvEM0AcWnAEAism2bYDeUs4AAIUlngF6RTkDABSZbdsACWQzAABWngEqUc4AANi2DaCcAQBIZts2QM/cjwoAgE7iGaA7W7UBAOjGOc8A/0Q5AwCwOvEM8A/KGQCAHtm2DbCKbAYAoAIrzwDKGQCABOIZKDprzgAAJLJtGyg096MCAKA3xDNQUBacAQDoPdu2gSJSzgAA9Il4BgpHOQMA0Fe2bQPF4iRnAACqIJ6BorDgDABA1WzbBgpBOQMAUAvxDOSfcgYAoEa2bQN5JpsBAKgLK89AbilnAADqxcozkE/KGYAC/qbravaM9maNBQpBPAM55H5UABQzmNf0ZCENtRPPQK5YcAag4M1c+RVUNFRNPAP5oZwBKE42z5o+pfLPjp04eU0vKKGhCuIZyAnlDEDuf68lBvOantwtpCU0VEE8A5knmwHI/a+2PmXz6so/vnpCW4KG3hPPQLYpZwDy/autxmyunND6GXpPPAMZppwByJPGZXOFhLaFG3qpX2+fCJCF+1HZfgZARjWnnNf0+rVf0Btyz8ozkD0WnAHI8a+2RmdzhSVo/xs0VGDlGcgY5QxAzqRSzj2+o/VnqEA8A1minAHImXTLefX31c+wJuIZyAwnOQOQY2mVcwzvDpkgnoEMGDNhUo/lnNJwAKA+On+7xdCunWOw+Aw9Es9A7GzVBiCXYm7UmMcGaRHPQNSUMwC5VPupzvfe/+B2Yw7q+s/VP7+lxlE5+RkqcKsqIFKyGYAiqHrD9lkX/SA0wKzpUzpvXgV0ZeUZiJFyBiDHat8UfeOtd/3hoQWhwWzehq7EMxAd5QxAQVS97Lz3HrvOnz2z/M85px4byagg38QzEBf3owIg37K1nJut0UJDiWcgFu5HBUChxLzAG/PYIC3iGYiCrdoAAMRMPAPpU84AFO1XXvxLu50jtHMbytyqCojxJOeUxgIAAD0Tz0BqLDgDAJAVtm0D6VDOAABkiHgGUqCcASigDJ3wXOa0Z+jKtm2gqWQzAABZZOUZaB7lDABARolnoEmUMwAA2WXbNtAM7kcFAECmiWegsSw4AwCQA7ZtAw2knAEAyAfxDDSKcgYAIDds2wbqTzYDAJAzVp6BOlPOAADkj3gG6kk5AwCQS+IZaOz9qGbPaPcRA0D512L5cxg7cXImPpDOcfptDs55BurDgjMAAPlm5RmolXIGACD3xDNQE+UMAEARiGegek5yBoC8nvbshGfoxn2egWpYcAYAoFDEM9BnyhkAajd24uRZ06fU/jpjdt95/uyZ9f1PJP6FcWg+27aBvlHOAFCLbN32KVujhYay8gz0lmwGgDgXn+vLsjP0yMoz0CvKGQCKtpyblXFCc4hnIJlyBoCCLPPGNh6Ih3gGErgfFQA0dFE3nl7tOhLLztCNeAbWaMyEST2Ws48MAGoX86/UmMcGaRHPQM9s1QaApjVqDIvPnWNQztAj8Qz0QDkDQJOl288x1DtETjwD3TnJGQAKdfKzU52hN8Qz8A9OcgaAovWzcoZeau3tE4G8s1UbANIye0Z75y/ics3Omj6l0W/aLdSd6gyVWXkGVlHOAJCubu3a6CVo5Qx9ZeUZik42A0BU/dzoJWjZDNURz1BoyhkAYt7CXd+EXn0121Zt6D3xDMWlnAEgE/1ce0L3uAlcOUOfiGcoqB7vR5XSWACAhC3cqzdwYkhXOGvaL32ogniGwrHgDACZTuharigmm6Fq4hmKRTkDQOZ0Fm+Pv8f79ApA1cQzFIhyBoBM69rAiSEtmKG+xDMUgmwGgJzRxtBk/Zr9hkDTKWcAAKiReIacU84AAFA727Yhz9yPCgAA6kI8Qz5ZcAYAgDqybRtySDkDAEB9iWfIG+UMAAB1Z9s25IqTnAEAoBHEM+SEBWcAAGgc27YhD5QzAAA0lHiGzFPOAADQaLZtQ4bJZgAAaA4rz5BVyhkAAJpGPEMmKWcAAGgm27Yhe9yPCgAAmkw8Q5ZYcAYAgFTYtg2ZoZwBACAt4hmyQTkDAECKbNuG2MlmAABInZVniJpyBgCAGIhniJdyBgCASNi2DZFyPyoAAIiHeIboWHAGAIDY2LYNcVHOAAAQIfEMEVHOAAAQJ9u2IRZOcgYAgGiJZ0ifBWcAAIicbduQMuUMAADxE8+QJuUMAACZYNs2pEM2AwBAhrSUSqW0xwD1Kc/KZs9oj+eDVs7EIOvzCACgmWzbhmZTzgAAkDlWninEolk8y2XuR0VUMjqPAACazznP0CQWnAEAILts2yarer8IFsNymXImTtmaRwAAKRLP0HDKGQAAss45z+T8jM3Ul8uc5Ez84p9HAACpc84zNIoFZwAAyA3btsm2ygtiKS6XKWcyJNp5BAAQD/EM9aecAQAgZ5zzTB7EE6vxjAT6yrcXAKACK89QN9oDAADySjyTB6sv7TZosbfCRYmVM1nXtHkEAJBF4hn6psdI7vF+VMIDAAByQzyTE00o1c5C7prKYyZMcidnAADIPfEM1bNVGwAACqI17QFAJjt5TSc/26oNAAC55FZVZFuFK3jVt2ab9kbQfL7eAACJxDM5PNCve99KC/Kn+fMIACDTxDP5P9av/ei/8ltrCTIkxXkEAJBp4plsH+7Pmj6l8s+OnTi5xkP/3sSGiiB+6c4jAICsE89k73A/8UC/TwGQeOgvnsm6GOYRAEDWiWeydMRf9eF+5UP/Csf9vd/jKh6IUwzzCAAgB8Qz2Tjir8vhfoVD/zUd9/fpBFHxQGwimUcAADkgninc4X7vD/2ruLSSeCAS8cwjAIB8EM8U94i/wnG/3dpkWiTzCAAgT8QzkR7xN+Fwv5cXE16dMCBmkcwj0wQAyBnxTCxSPOIvczMeciCqeaSfAYA8Ec9EIfUj/jIXECbTIpxH+hkAyI1+aQ8A/kmKR/yrv7vjfjIqqnkEAJAP4pmIlstiOOaOYQyQm3lUxSXrAQDi1Jr2ACi6mI+tx0yYZPGZgsyjZxcuuvu++U8+/dclry8dPGjAtm/f4j3vGr1uW1tdxmYeAQA54JxncnuK5kMLnjj/sqvO/Z/jqvhZJ21SnHn0/KKXzjz/sptvv6ejVOr67wcPHPC5cft95t/H9mtpqW5g5hEAkCe2bROFupfzsuUrTjj9vOUrVkYyHmiCKr63DzzypwM+d/yNt93drZxDCItfeXXqhZcffmL70mXLmjYeAIBoiWfyuWH7rIsuf+zJp3O/sRxq+X4+v+ilz5/QvviVV0MIW2028puTj5o98zv3/OzS6y6ZetShB26wXv8Qwm/uvf+YU86u/XM2jwCArBPPpK/uy1N3zpn3w+tuqvFFLJqRLVV8Y08/99JyOe+y43Y/uqD9ox/afaPhQ9dfr/+Wo0YedsgBV17YPmLDoSGE2++Ze/0vf920UQEAxEk8k47GLUO99PKrX/vWBaXV9qDWwqIZcarlm/n4n5+ZfcecEMLQwQOnnnR02zprd3vC2zbd+LTjDi8/nvnTm0PNzCMAINPEMymr+8LUyWd9d+GixXV5KYtmZEUV39Vf/Oo35f+N6fDxnxw8cECPz9ltp+2HDxscQrj/wQWrnxTduLEBAETIrarIlat/fsvsO1ctpgGVvWObrb7+5f8KIXx8rw9UeNqIDYcuXLS4o6PjtdeWDNhgfZ8qAFBYVp5JQefuzfouST31zHNnfud7IYR129paqr25TjedI7TjlJzNo/e/550H7rvngfvuWeFmzh0dHc88uzCE0H/dtlrK2TwCAHJAPJMTHR0dJ7aft+T1pSGE448YX694rpHkJtPfk2tvvO2ll1ddUWznHUanPRYAgJSJZ3Liwu9fM++BR0MIe+z67gM/9uEYcijaIiJCEX5hbrj1rinTLik//sy/j017OAAAKXPOM3kw74FHL7z8mhDCsCGD/uerh6U7mNgSiAwpf3lmz2hPawDLlq9YuOil3z/wyLU33Hr3ffPL//LQ/9h3lx23S2tIAACRsPJM5k94XvL60hPbz+vo6AghnHb8F4YMHhjqqvena0a4eEgW9eaL1IgLBzy38MV37zP+I4d86cTTzyuXc0tLy8Rx+39l4rjaX9xpzwBA1ll5JvPaz7/sqWeeCyGM23/v97/nnamMQTOTv1XoEMKGQwdt9y9b9ovjCgIAAOkSz2Tb7Dvm/OQXvwohbDlq5LGfP7jJ766Zadp3LJWKXrho8dHfOOtDu+90xqQj1+u/bvMHAAAQD/FMhi1ctPgbZ303hLB2a+uZ/31kW9s6EdaywCat715fbTR86L0/v+zlV157/Kln/vDQghtuvevhx54MIdxy571fmHTGxVNPam1dq9FjAACIlnOeyapSqfS1b12w+JVV99E5+r8O+tetNkt7RJB567a1bTR86C47bjdx3P5Xf/fMc045dtCADUIIv/vDQxd8/+q0RwcAkCbxTFZd8ZMb75wzL4Tw3ndt+9lPuY8O1N+Y9+38vXNO7r9uWwhhxlXXv/q313zKAEBhiWcy6bEnn/7f6T8IIQwcsP7pJ3yxxQWNoDG2HDXy0AP3XXUXq2XLb7v7Ph8zAFBY4pnsWbFy5Qmnn7ds+YoQwje+MnGj4UPTHhHk2R677lh+8NCbp0ADABSTC4aRPedcPPOhBU+UHx932rTjTpsWSqVVZ0H//yeU3vxjCOHOOfO2G3NQ+fHvfvH9tnXWrvGtu13xuDfXcEr3VkNkQhVfpGZeiG7woL/fO33psuVNe1MAgNiIZzJmzrwHvnfVrM4/dnR0pDiYzp5xSW0a/R2rr6kXXT7jyutDCLO+d/aoTTeu/OSFi14sPxg2ZFAjBgMAkAnimYy5/Z65H9xtp+UrVrz5z8pV/3f5yhX//MflK1Y0OarLhSOhqfuXqkF22fEd5Xj+6U23H3XogZWffOtdfz/VefTbN2/ckAAAItfSucEVmqYzMmdNn9Kgt9h+z3EdHR2777zDRWfUurt17MTJfYqZbglt2zYN+s7UMo9Wrnxjz3FfXLho8cAB68+a8e0hg/++MXt1zy5c9PFDj13y+tIN1l/vth9fVPW5D32dRwAAsXHBMKiz2TPa5QGRf3laW9c6+BP7hBBeefW1SWecv3LlGz0+7YUXF39h0hlLXl8aQjjs4E/UftUAAIDsEs/QEBKayL8wn/3U2C1HjQwh3DFn3me/csr9Dy7o+rcrVq687qbbPnX4iY8+/lQIYacdRo//5EebOTwAgNg45xkayBI00X5P1m5tPX/K8eOP/vrCRYvnPfDIuCO/NmLYkC1Hjezfv23xy397cMHjry9dVn7m9ttsNe2UY1tb12r+IAEA4mHlmTRTofM0yGg5UZMcz6ORm4yYef7p733XtuU/Pr/opbvu+8Mtd9573/yHyuW8dmvr+E9+9LKzTx44YP1ahmoeAQA5YOUZoLg2Gj704qknzZn3wPW/vGPu/Ieff+HFpcuXDx44YNSmG+/67u332/sDm4zYMO0xAgBEQTyTsrETJzfimtv333xF7S8S/8I41GUe7bzD6J13GN2gD9M8AgDywbZt0pGtk4GzNVqKI1vfzGyNFgCgG/FM+uJcmIpzVJCtb2ycowIAqIJ4JjVZWYbKyjgppqx8P7MyTgCANRHPRCG25anYxgNZ/N7GNh4AgFqIZ2JZjIrnOLvrSCyXET/zCACgCcQzKYu5TmMeG2Tluxrz2AAAek88E9GxdQyLz51jcMRPtphHAAANJZ6JS7r9HEO9Q+3MIwCAuhPPRCGGkzad6kzWmUcAAI0jnolFusf9ypl8MI8AABqkpVQqNeq1oe/GTJjU9Y+zpk9p9KfYLdSd6kwOmEcAAHVn5Zm4dGvXRi9BK2dyyTwCAKg7K88UdOlMNlME5hEAQL2IZzJz3F+vhF59NdtWbXLMPAIAqAvxTMaO+2tJ6B43gStncs88AgConXgmq4f+vQzpCmdNy2YKxTwCAKiFeCYPh/59JZspLPMIAKA64pkCHf1rZjCPAACqI57JeUgLZjCPAABqJ54BAAAgQb+kJwAAAEDRiWcAAABIIJ4BAAAggXgGAACABOIZAAAAEohnAAAASCCeAQAAIIF4BgAAgATiGQAAABKIZwAAAEggngEAACCBeAYAAIAE4hkAAAASiGcAAABIIJ4BAAAggXgGAACABOIZAAAAEohnAAAAEM8AAABQGyvPAAAAkEA8AwAAQALxDAAAAAnEMwAAACQQzwAAAJBAPAMAAEAC8QwAAAAJxDMAAAAkEM8AAACQQDwDAABAAvEMAAAACcQzAAAAJBDPAAAAECr7P/QXBD+Tseu8AAAAAElFTkSuQmCC
