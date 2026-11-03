# 提高组模拟赛

第 04 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 接水 | 山路 | 点心 | 书签 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | calibrate | hill | snack | bookmark |
| 可执行文件名 | calibrate | hill | snack | bookmark |
| 输入文件名 | calibrate.in | hill.in | snack.in | bookmark.in |
| 输出文件名 | calibrate.out | hill.out | snack.out | bookmark.out |
| 每个测试点时限 | 1 秒 | 1 秒 | 3 秒 | 1 秒 |
| 内存限制 | 256 MiB | 256 MiB | 256 MiB | 256 MiB |
| 测试点数目 | 20 | 20 | 20 | 20 |
| 测试点是否等分 | 是（每点 5 分） | 是（每点 5 分） | 否（分组捆绑） | 否（分组捆绑） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | calibrate.cpp | hill.cpp | snack.cpp | bookmark.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 接水、山路各测试点独立计分；点心、书签按数据范围表分组捆绑，每组全部通过才得分。所有题目的答案唯一，采用全文比较评测。

# 接水（calibrate）

## 【题目描述】

穗织的祭典快到了，丛雨挽起袖子，要帮茉子接水。她正准备搬来最大的木桶，茉子却拦住她，把接水、用水的顺序写在了纸上。

茉子的计划一共有 $n$ 步。第 $i$ 步会使桶里的水量增加 $a_i$；若 $a_i<0$，就表示取出 $-a_i$ 的水。水量均用整数表示。

茉子发现，照这份计划做完，桶里的水未必和开始时一样多。她可以修改至多一步：把这一项 $a_i$ 改成任意整数，修改后仍按原顺序执行。开始时装多少水也可以由她决定。

设木桶的容量为非负整数 $C$，初始水量为整数 $x$。整个过程中不能把水用光后继续取水，也不能让水溢出，也就是说，初始时和每一步结束时的水量都必须在 $[0,C]$ 内。执行完全部 $n$ 步后，水量还要恰好回到 $x$。

丛雨不想搬一个没必要的大桶。请你求出满足条件的最小容量 $C$。初始水量与修改后的 $a_i$ 不受原 $a_i$ 的范围限制。

## 【输入格式】

从文件 `calibrate.in` 读入数据。

第一行包含一个整数 $n$，表示步骤数。

第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$。

## 【输出格式】

输出到文件 `calibrate.out`。

输出一行一个整数，表示木桶的最小容量 $C$。

## 【样例 1 输入】

```text
5
6 -9 5 8 -3
```

## 【样例 1 输出】

```text
9
```

## 【样例 1 解释】

将第 $4$ 步的 $a_4$ 从 $8$ 改为 $1$，初始时装 $3$ 的水。桶里的水量依次为

$$3,9,0,5,6,3.$$

容量为 $9$ 的桶就能完成全部步骤，最后的水量也回到了 $3$。不存在容量更小的可行方案。

## 【样例 2 输入】

```text
1
-17
```

## 【样例 2 输出】

```text
0
```

## 【样例 2 解释】

将唯一一步的 $a_1$ 改为 $0$，初始水量和容量都取 $0$ 即可。

## 【附加样例】

样例 $1\sim6$ 的输入与答案见下发文件 `calibrate/calibrate编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
| --- | --- |
| 1 | $n=5$ |
| 2 | $n=1$ |
| 3 | $n=40$ |
| 4 | $n=2\times10^5$ |
| 5 | $n=2\times10^5$ |
| 6 | $n=2\times10^5$，满足特殊性质 A |

## 【数据范围】

对于所有数据，$1\le n\le2\times10^5$，$-10^9\le a_i\le10^9$，所有输入均为整数。

| 测试点编号 | $n$ 的上界 | 特殊性质 |
| --- | --- | --- |
| $1\sim4$ | $200$ | 无 |
| $5\sim8$ | $3000$ | 无 |
| $9\sim10$ | $2\times10^5$ | A |
| $11\sim20$ | $2\times10^5$ | 无 |

特殊性质 A：$\sum_{i=1}^{n}a_i=0$。

# 山路（hill）

## 【题目描述】

丛雨听说大家要去山里野餐，早早把点心准备好了。地点还没定下来，蕾娜已经把相机装进了背包。

丛雨把山路图交给了茉子。茉子需要考虑路途上的体力消耗，选出一个大家都能到达的集合地点。

山路图中有 $n$ 个景点，编号为 $1\sim n$。景点之间的 $n-1$ 条道路构成一棵树。每条道路连接两个景点 $u,v$，从 $u$ 到 $v$ 是上坡，从 $v$ 到 $u$ 是下坡：

- 经过一条上坡道路，体力减少 $1$。
- 经过一条下坡道路，体力增加 $1$。

每个景点都有一位参加野餐的人。茉子要选一个景点作为集合地点，大家沿自己所在景点到集合地点的唯一简单路径行走，不绕路，也不往回走。已经在集合地点的人不需要行走。

如果每个人出发时都有 $K$ 点体力，那么在行走途中，每经过一条道路后的体力都不能为负；体力恰好为 $0$ 是允许的。下坡恢复的体力可以超过出发时的 $K$。

接下来有 $q$ 次询问，每次给出一个非负整数 $K$。请你求出有多少个景点可以作为集合地点，让所有人都能顺利到达。每次询问独立考虑，大家都从原来的景点出发。

## 【输入格式】

从文件 `hill.in` 读入数据。

第一行包含两个整数 $n,q$，表示景点数和询问数。

接下来 $n-1$ 行，每行包含两个整数 $u,v$，表示一条道路，且从 $u$ 到 $v$ 为上坡，从 $v$ 到 $u$ 为下坡。

接下来 $q$ 行，每行包含一个非负整数 $K$，表示所有人出发时的体力。

## 【输出格式】

输出到文件 `hill.out`。

对每次询问输出一行一个整数，表示可以作为集合地点的景点数。

## 【样例 1 输入】

```text
5 4
1 2
3 2
2 4
5 4
0
1
2
1000000000
```

## 【样例 1 输出】

```text
0
3
5
5
```

## 【样例 1 解释】

当 $K=1$ 时，可以在景点 $1,2,3$ 集合。

如果选择景点 $5$，景点 $1$ 的人要经过路径 $1\to2\to4\to5$。虽然最后一段是下坡，但前两段都是上坡，出发时只有 $1$ 点体力就无法走完第二段。因此不能只看走完全程后还剩多少体力。

当 $K=2$ 时，五个景点都可以作为集合地点。

## 【样例 2 输入】

```text
1 1
0
```

## 【样例 2 输出】

```text
1
```

## 【样例 2 解释】

只有一个景点，不需要经过任何道路，所以出发时的体力为 $0$ 也能在这里集合。

## 【附加样例】

样例 $1\sim6$ 的输入与答案见下发文件 `hill/hill编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
| --- | --- |
| 1 | $n=5$，$q=4$ |
| 2 | $n=q=1$ |
| 3 | $n=60$，$q=80$ |
| 4 | $n=q=2\times10^5$ |
| 5 | $n=q=2\times10^5$ |
| 6 | $n=q=2\times10^5$，满足特殊性质 A |

## 【数据范围】

对于所有数据，$1\le n,q\le2\times10^5$，$0\le K\le10^9$，$1\le u,v\le n$。所有输入均为整数。

| 测试点编号 | $n$ 的上界 | $q$ 的上界 | 特殊性质 |
| --- | --- | --- | --- |
| $1\sim4$ | $100$ | $200$ | 无 |
| $5\sim8$ | $2000$ | $2000$ | 无 |
| $9\sim10$ | $2\times10^5$ | $2\times10^5$ | A |
| $11\sim20$ | $2\times10^5$ | $2\times10^5$ | 无 |

特殊性质 A：以景点 $1$ 为根，每条道路从父亲走向儿子都是上坡。

# 点心（snack）

## 【题目描述】

出发野餐前，丛雨又拉着茉子去了点心铺。竹篮里已经放了茶壶，留给点心的位置不多；可买得太少，丛雨又担心大家不够分。

柜台上还有 $n$ 包点心，编号为 $1\sim n$。第 $i$ 包的重量为 $a_i$，价格为 $b_i$。每包点心只能整包购买，至多购买一次；不同包的重量、价格都可以相同。

茉子算出，买下的点心总重量至少要有 $L$，至多只能有 $R$。她原本预计花费 $K$，希望实际花费与 $K$ 尽量接近。实际花费可以小于、等于或大于 $K$。

请你选择一些点心，使它们的总重量在闭区间 $[L,R]$ 内，并使总价与 $K$ 的差的绝对值最小。输出这个最小值；如果无论怎样选择，总重量都不在 $[L,R]$ 内，则输出 $-1$。

## 【输入格式】

从文件 `snack.in` 读入数据。

第一行包含一个整数 $T$，表示测试数据组数。

对于每组数据，第一行包含四个整数 $n,L,R,K$，含义如题目描述。

接下来 $n$ 行，每行包含两个整数 $a_i,b_i$，表示第 $i$ 包点心的重量和价格。

## 【输出格式】

输出到文件 `snack.out`。

对每组数据输出一行一个整数，表示总价与 $K$ 的差的绝对值的最小值；如果不存在符合重量要求的选择，输出 $-1$。

## 【样例 1 输入】

```text
1
4 5 7 16
2 5
3 9
4 10
6 17
```

## 【样例 1 输出】

```text
1
```

## 【样例 1 解释】

选择第 $1,3$ 包点心，总重量为 $6$，总价为 $15$，与 $K=16$ 相差 $1$。只选第 $4$ 包也符合重量要求，总价为 $17$，同样相差 $1$。

不存在总重量符合要求、总价恰好为 $16$ 的选择，所以答案为 $1$。

## 【样例 2 输入】

```text
2
2 4 4 7
3 5
5 8
1 2 2 0
2 9
```

## 【样例 2 输出】

```text
-1
9
```

## 【样例 2 解释】

第一组数据中，可能的总重量为 $0,3,5,8$，都不等于 $4$，所以输出 $-1$。

第二组数据必须买下唯一的一包点心，总价为 $9$，与 $K=0$ 相差 $9$。不买任何点心时总重量为 $0$，不符合要求。

## 【附加样例】

样例 $1\sim6$ 的输入与答案见下发文件 `snack/snack编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
| --- | --- |
| 1 | $T=1$，$n=4$ |
| 2 | $T=2$，$n\le2$ |
| 3 | $T=2$，$n\le26$ |
| 4 | $T=2$，每组 $n=40$ |
| 5 | $T=2$，每组 $n=40$ |
| 6 | $T=2$，每组 $n=40$，满足特殊性质 A |

## 【数据范围】

对于所有数据，$1\le T\le20$，$1\le n\le40$，$1\le a_i,b_i\le10^{12}$，$1\le L\le R\le4\times10^{13}$，$0\le K\le4\times10^{13}$。所有输入均为整数。

同一个输入文件内，所有测试数据的 $n$ 之和不超过 $80$。

| 子任务 | 测试点编号 | 分值 | $n$ 的上界 | 特殊性质 |
| --- | --- | --- | --- | --- |
| 1 | $1\sim4$ | $10$ | $18$ | 无 |
| 2 | $5\sim8$ | $20$ | $26$ | 无 |
| 3 | $9\sim10$ | $20$ | $40$ | A |
| 4 | $11\sim20$ | $50$ | $40$ | 无 |

特殊性质 A：$L=1$，且 $R\ge\sum_{i=1}^{n}a_i$。

每个子任务独立计分，通过该子任务的全部测试点才能获得对应分数。每个测试点内的全部测试数据都必须回答正确。

# 书签（bookmark）

## 【题目描述】

芳乃整理神社的书架时，找出了一盒印着字母花纹的长纸条。丛雨打算从纸条上裁下一段做书签，再将剩下的两端接起来，留作书页的装饰。她希望裁下的书签和接好的纸条都能从两头读出相同的花纹。

一张纸条上的花纹用长度为 $n$ 的小写字母串 $s$ 表示。选择一个连续区间 $[l,r]$，将其中的字符裁下，要求：

- 裁下的字符串 $s_ls_{l+1}\cdots s_r$ 是回文串。
- 将剩余的前缀 $s_1s_2\cdots s_{l-1}$ 和后缀 $s_{r+1}s_{r+2}\cdots s_n$ 按原顺序拼接后，得到的字符串也是回文串。
- 裁下的部分和剩余的部分都非空，即 $1\le l\le r\le n$ 且 $r-l+1<n$。

回文串是顺着读和倒着读完全相同的字符串，例如 `a`、`abba`、`abcba`。字符的顺序不能调整。

每种裁法独立考虑。只要区间端点不同，就算不同的裁法，即使裁下的字符串相同也要分别计算。请你求出所有合法裁法中，裁下的字符串长度之和。若没有合法裁法，答案为 $0$。

## 【输入格式】

从文件 `bookmark.in` 读入数据。

第一行包含一个整数 $T$，表示测试数据组数。

对于每组数据，第一行包含一个整数 $n$，第二行包含一个长度为 $n$ 的小写字母串 $s$。

## 【输出格式】

输出到文件 `bookmark.out`。

对每组数据输出一行一个整数，表示所有合法裁法裁下的长度之和。

## 【样例 1 输入】

```text
2
5
abbaa
3
abc
```

## 【样例 1 输出】

```text
8
0
```

## 【样例 1 解释】

第一组有四种合法裁法：

| 裁下的区间 | 裁下的字符串 | 拼接后剩余的字符串 |
| --- | --- | --- |
| $[1,4]$ | `abba` | `a` |
| $[2,3]$ | `bb` | `aaa` |
| $[4,4]$ | `a` | `abba` |
| $[5,5]$ | `a` | `abba` |

答案为 $4+2+1+1=8$。后两种裁法虽然得到相同的字符串，仍要分别计算。

![裁下中间一段后拼接][bookmark-example]

图 1　裁下区间 $[2,3]$ 后，将两端按原顺序接好。

第二组没有合法裁法。

## 【附加样例】

样例 $1\sim8$ 的输入与答案见下发文件 `bookmark/bookmark编号.in` 和对应的 `.ans` 文件。

| 编号 | 数据范围 |
| --- | --- |
| 1 | $T=2$，$n\le5$ |
| 2 | $T=5$，$n\le6$ |
| 3 | $T=2$，$n\le3000$，$\sum n=5998$ |
| 4 | $T=1$，$n=2\times10^5$ |
| 5 | $T=2$，$\sum n=2\times10^5$ |
| 6 | $T=2$，$\sum n=2\times10^5$，每组的字符均相同 |
| 7 | $T=2$，$\sum n=2\times10^5$，满足特殊性质 A |
| 8 | $T=2$，$\sum n=2\times10^5$，满足特殊性质 B |

## 【数据范围】

对于所有数据，$1\le T\le10$，$1\le n\le2\times10^5$，$s$ 仅由小写英文字母组成。

同一个输入文件内，所有测试数据的 $n$ 之和不超过 $2\times10^5$。

| 子任务编号 | 测试点编号 | 分值 | $n$ 的上界 | 特殊性质 |
| --- | --- | --- | --- | --- |
| 1 | $1\sim2$ | $10$ | $80$ | 无 |
| 2 | $3\sim4$ | $10$ | $3000$ | 无 |
| 3 | $5\sim7$ | $15$ | $2\times10^5$ | A |
| 4 | $8\sim10$ | $15$ | $2\times10^5$ | B |
| 5 | $11\sim20$ | $50$ | $2\times10^5$ | 无 |

特殊性质 A：设 $k$ 为满足 $0\le k\le\lfloor n/2\rfloor$ 且 $s_i=s_{n-i+1}$（$1\le i\le k$）的最大整数，保证 $k\le20$。也就是说，从两端向内连续相等的字符对数不超过 $20$。

特殊性质 B：$s$ 的所有回文子串的长度均不超过 $60$。

每个子任务采用捆绑计分，其中所有测试点全部通过才能获得该子任务的分数。每个测试点内的全部测试数据都必须回答正确。

[bookmark-example]: data:image/png;base64,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
