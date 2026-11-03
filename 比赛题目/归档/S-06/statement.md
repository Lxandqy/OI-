# 提高组模拟赛

第 06 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 瓶子 | 鲜花 | 对战 | 颁奖 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | bottle | flower | master | prize |
| 可执行文件名 | bottle | flower | master | prize |
| 输入文件名 | bottle.in | flower.in | master.in | prize.in |
| 输出文件名 | bottle.out | flower.out | master.out | prize.out |
| 每个测试点时限 | 0.5 秒 | 1 秒 | 1 秒 | 1 秒 |
| 内存限制 | 64 MiB | 64 MiB | 64 MiB | 64 MiB |
| 测试点数目 | 10 | 28 | 4 | 10 |
| 测试点是否等分 | 是（每点 10 分） | 否（分组捆绑） | 否（各点分值见数据范围） | 是（每点 10 分） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | bottle.cpp | flower.cpp | master.cpp | prize.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 鲜花按数据范围表分组捆绑，每组全部通过才得分。其余题目各点独立计分。所有题目采用全文比较评测。


## 瓶子（bottle）




### 题目描述

鲨鲨有 $p$ 个 $0$ 号空瓶子。

有 $N$ 个商店，在第 $i$ 个商店可以用 $A_i$ 个空瓶子（$0$ 号瓶子或者 $i$ 号瓶子）换取 $B_i$ 个装满果汁的 $i$ 号瓶子。保证 $A_i > B_i$。

鲨鲨每喝掉一瓶装在 $i$ 号瓶子里的果汁，就会获得 $C_i$ 的精神值。

请对于 $p \in \{1, 2, \dots, M\}$，分别求出鲨鲨可以获得的最大精神值。

### 输入格式


第一行两个整数 $N, M$。

接下来 $N$ 行，每行三个整数 $A_i, B_i, C_i$。

### 输出格式


对于 $p \in \{1, 2, \dots, M\}$，各输出一行，一个整数表示答案。



### 样例 1 输入


```
2 5
4 3 3
5 2 8
```

### 样例 1 输出


```
0
0
0
9
18
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `bottle2.in`、`bottle2.ans` |

### 数据范围


对于 $20\%$ 的数据，$N = 1$ 。

对于 $100\%$ 的数据，$1 \le N \le 5000,2 \le M \le 5000,1 \le B_i < A_i \le M,1 \le C_i \le 10^9$ 。

## 鲜花（flower）




### 题目描述

_自那场“天与地之战”结束后的百年内，被地鸣践踏过的土地逐渐恢复着生机。在山坡上的那棵树下，一座墓碑旁盛开着鲜花……_

这个地方不知何时起总共开了 $n$ 朵花，它们排成了一排，分别编号为 $1, 2, 3, \dots, n$。每朵花的鲜艳度并不是相同的，第 $i$ 朵花一开始的鲜艳度为 $a_i$。

但这些花儿似乎并不会受到四季变化的影响，它们就一直在这儿开着，不会凋谢，并且在每一年中的某个特定时刻，所有花的鲜艳度都会发生这样的变化：

*   首先，所有花的鲜艳度都会增加 $1$。
*   然后，每朵花会受到所有与其**相邻**的花的影响，如果相邻的花中有鲜艳度比自己更高的花，那么它的鲜艳度就会变得跟**所有相邻的花中鲜艳度最高的花**一样。所有花的鲜艳度都是**同时变化**的，在同一年内并不会产生连带影响。
*   对于编号为 $i$ 的花，只有 $i - 1$ 与 $i + 1$ 这两个编号与其相邻（如果存在）。

之后又过了很久很久，久到已无人知晓此地，但花儿却依旧自顾自地开着……请问在花开 $m$ 年之后，每朵花的鲜艳度情况是怎么样的呢？

### 输入格式


第一行包含两个整数 $n, m$，分别表示花的数量以及经过的年数。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$，分别表示每朵花一开始的鲜艳度。

### 输出格式


$n$ 个整数，按编号顺序输出每朵花在 $m$ 年后的鲜艳度，相邻整数间以单个空格隔开。


### 样例 1 输入


```
6 1
4 1 2 3 1 1
```

### 样例 1 输出


```
5 5 4 4 4 2
```

### 样例 1 解释


初始时，每朵花的鲜艳度分别为 $(4, 1, 2, 3, 1, 1)$。

一年后，首先所有花的鲜艳度都会增加 $1$，变为 $(5, 2, 3, 4, 2, 2)$。

然后每朵花受到相邻的花的影响，例如编号为 $2$ 的花原本的鲜艳度为 $2$，与其相邻的两朵花鲜艳度分别为 $5$ 和 $3$，所以它的鲜艳度会变成其中的较大值 $5$。最终每朵花的鲜艳度分别为 $(5, 5, 4, 4, 4, 2)$。


### 样例 2 输入


```
6 2
4 1 2 3 1 1
```

### 样例 2 输出


```
6 6 6 5 5 5
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `flower3.in`、`flower3.ans` |

### 数据范围


对于 $32\%$ 的数据，$n\le 10$ 。

对于 $60\%$ 的数据，$n \le 1000,n \times m \le 10^6$ 。

对于 $100\%$ 数据， $1 \le n \le 2 \times 10^5,1 \le m \le 3 \times 10 ^5,1 \le a_i \le 5 \times 10^5$ 。


本题采用子任务捆绑计分。通过一个子任务内的全部测试点，才能获得该子任务的分数。

| 子任务 | 测试点编号 | 分值 |
| --- | --- | --- |
| 1 | 1～11 | 32 |
| 2 | 12～18 | 28 |
| 3 | 19～28 | 40 |

## 对战（master）




### 题目描述

为了八大师决赛的胜利，小智开始对自己的宝可梦进行特训。

在本题中，我们不区分物攻和特攻，且对战过程中除非当前宝可梦阵亡，否则不会更换宝可梦。每只宝可梦的四个技能均为攻击技能且没有攻击特效。

宝可梦的对战规则如下：

- 每回合双方可以从宝可梦的四个技能中选择**能对对方当前宝可梦造成伤害最高**的技能进行攻击。
- 每个技能有且仅有一个独立的属性，进攻时的属性克制倍率**按技能计算**而并非按宝可梦属性计算。
- 双方首发（第一只上场）的宝可梦即**输入顺序**中的第一只宝可梦。
- 一旦宝可梦的血量变为 $0$ 及以下，则视为阵亡，此时应当派上**输入顺序**中的下一只宝可梦。
- 在一回合内，速度较快的宝可梦会先出手，较慢的宝可梦会后出手。如果双方速度相同，则小智的宝可梦先出手（主角光环）。
- 如果先出手的宝可梦击杀了对手的宝可梦，该回合内对手将**不会**打出攻击，在其换上下一只宝可梦后，将直接进行**下一回合**的战斗。
- 伤害的计算公式为：$\frac{110\times\text{[我方]攻击力}\times\text{招式威力}}{250\times{[敌方]防御力}}$

为再次简化问题，每个属性都用一个数值来表示。属性克制表如下所示：（复制即可，注意下标从 $0$ 开始）

```
double f[18][18] = {{1,1,1,1,1,0.5,1,0,0.5,1,1,1,1,1,1,1,1,1},
          {2,1,0.5,0.5,1,2,0.5,0,2,1,1,1,1,0.5,2,1,2,0.5},
          {1,2,1,1,1,0.5,2,1,0.5,1,1,2,1,1,1,1,1,2},
          {1,1,1,0.5,0.5,0.5,1,0.5,0,1,1,2,1,1,1,1,1,2},
          {1,1,0,2,1,2,0.5,1,2,2,1,0.5,2,1,1,1,1,1},
          {1,0.5,2,1,0.5,1,2,1,0.5,2,1,1,1,1,2,1,1,1},
          {1,0.5,0.5,0.5,1,1,1,0.5,0.5,0.5,1,2,1,2,1,1,2,0.5},
          {0,1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,0.5,1},
          {1,1,1,1,1,2,1,1,0.5,0.5,0.5,1,0.5,1,2,1,1,2},
          {1,1,1,1,1,0.5,2,1,2,0.5,0.5,2,1,1,2,0.5,1,1},
          {1,1,1,1,2,2,1,1,1,2,0.5,0.5,1,1,1,0.5,1,1},
          {1,1,0.5,0.5,2,2,0.5,1,0.5,0.5,2,0.5,1,1,1,0.5,1,1},
          {1,1,2,1,0,1,1,1,1,1,2,0.5,0.5,1,1,0.5,1,1},
          {1,2,1,2,1,1,1,1,0.5,1,1,1,1,0.5,1,1,0,1},
          {1,1,2,1,2,1,1,1,0.5,0.5,0.5,2,1,1,0.5,2,1,1},
          {1,1,1,1,1,1,1,1,0.5,1,1,1,1,1,1,2,1,0},
          {1,0.5,1,1,1,1,1,2,1,1,1,1,1,2,1,1,0.5,0.5},
          {1,2,1,0.5,1,1,1,1,0.5,0.5,1,1,1,1,1,2,2,1}};
```

其中 `f[i][j]` 表示用属性为 $i$ 的技能攻击属性为 $j$ 的宝可梦时所能造成的伤害倍率。

如果被攻击的宝可梦拥有两种属性，则造成的伤害倍率为**两种属性各自的伤害倍率的乘积**。例如，当使用属性为 $a$ 的技能攻击某只拥有 $b,c$ 两种属性的宝可梦时，伤害倍率为 `f[a][b]*f[a][c]`。

特别注意：如果宝可梦使用的**技能的属性**与**自身的某一属性**相同时，技能威力将提升至原来的 $1.5$ 倍。

每一次攻击，在按照倍率计算出伤害数值后，应**保留其整数部分**（向下取整）作为**实际造成的伤害**。

在某一方失去全部的宝可梦时，游戏结束，另一方将赢得该局游戏。

### 输入格式


多组数据。第一行包含一个整数 $T$，表示测试数据组数。

每组数据共 $12$ 行，前 $6$ 行表示小智的宝可梦，后 $6$ 行表示对手的宝可梦。

每行格式如下：

首先输入四个整数 $a,d,s,h$，分别表示该只宝可梦的攻击力、防御力、速度、血量；

其后再输入四组整数 $t_i, p_i$，分别表示该只宝可梦的四个技能的属性和威力；

其后再输入一个 $k$，表示该只宝可梦的属性个数；

最后再输入 $k$ 个整数 $b_i$，表示该只宝可梦的属性（保证互不相同）。

数据保证游戏不会陷入死局，即双方在任一时刻都至少有一方的宝可梦能够有效地攻击对方。

### 输出格式


对于每组数据，在一行内输出一个字符，若小智胜利，输出 Y，否则输出 N。


### 样例 1 输入


```
1
1 1 1 1 1 10 2 10 3 10 4 10 1 1
2 2 2 2 1 10 2 10 3 10 4 10 1 1
3 3 3 3 1 10 2 10 3 10 4 10 1 1
4 4 4 4 1 10 2 10 3 10 4 10 1 1
5 5 5 5 1 10 2 10 3 10 4 10 1 1
6 6 6 6 1 10 2 10 3 10 4 10 1 1
1 1 1 1 1 10 2 10 3 10 4 10 1 1
2 2 2 2 1 10 2 10 3 10 4 10 1 1
3 3 3 3 1 10 2 10 3 10 4 10 1 1
4 4 4 4 1 10 2 10 3 10 4 10 1 1
5 5 5 5 1 10 2 10 3 10 4 10 1 1
6 6 6 6 1 10 2 10 3 10 4 10 1 1
```

### 样例 1 输出


```
Y
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `master2.in`、`master2.ans` |

### 数据范围


对于 $100\%$ 的数据，$T \le 100,1 \le a,d,s \le 500,1 \le h \le 10^7,0 \le t_i \le 17,1 \le p_i \le 300,1 \le k \le 2,0 \le b_i \le 17$

各测试点独立计分，具体限制和分值如下。

| 测试点编号 | 分值 | 特殊限制 |
| --- | --- | --- |
| 1 | 15 | $h\le5000,\ k=1$ |
| 2 | 15 | $h\le5000,\ k=2$ |
| 3 | 30 | $k=1$ |
| 4 | 40 | 无 |

## 颁奖（prize）




### 题目描述

奥运会某个项目的比赛结束啦，现在到了颁奖的环节。

这个项目总共有 $n$ 位参赛选手，每位选手在该项目中的成绩可以用一个正整数 $a_i$ 来表示，并且**整数越小**，**排名越靠前**。

现在这些选手站成了一排，从左到右每个人的成绩依次是 $a_1, a_2, \dots, a_n$。

由于这个项目的难度有亿点点大，所以我们可以认为**不存在成绩相同**的选手。

众所周知，冠亚季军的颁奖台一般是长下面这张图这个样子的，冠军在中间，左边是亚军，右边是季军。



![原题示意图][s-06-original-6-X76]



于是，主办方想要知道，如果从这 $n$ 位选手中选出三位选手，按照原先顺序排好，那么存在多少种不同的选法，使得这三位选手的排名满足“中间第一，左边第二，右边第三”呢？

换句话说，请求出存在多少组三元组 $(i, j, k)$，满足 $1 \le i < j < k \le n$ 且 $a_j < a_i < a_k$？

### 输入格式


第一行包含一个正整数 $n$。

第二行包含 $n$ 个正整数 $a_1, a_2, \dots, a_n$。

### 输出格式


一个整数，表示答案。


### 样例 1 输入


```
5
3 2 5 1 4
```

### 样例 1 输出


```
4
```

### 样例 1 解释


对于样例：满足条件的 $(i, j, k)$ 有：$(1, 2, 3), (1, 2, 5), (1, 4, 5), (2, 4, 5)$。





### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `prize2.in`、`prize2.ans` |
| 3 | `prize3.in`、`prize3.ans` |

### 数据范围


对于 $ 20\%$ 的数据，$n \le 500$ 。

对于 $40\%$ 的数据，$n \le 8000$ 。

对于 $100\%$ 的数据，$3 \le n \le 2 \times 10^5,1 \le a_i \le 10^9,\forall_{i \ne j}:\ a_i \ne a_j$ 。

[s-06-original-6-X76]: data:image/png;base64,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8crpM2c/++I///jM3yORyHmnHdO1c8fmtM15BF/nIhSwoQjPwGahIl5ZX6j+b4qGzU28surnN97513+8EYlEOnfsMObiH61RYfu+WxcWtF9eVHzjnQ/eeOeD0Wg0KyszJysrOztz1RCPtNra2nhlVdWq5zNX/f6/e9R1L7A95vvNbKHziNao7opq3YikTcVFKGBdhGdoEy495+TNfGLqleUV9YV4ZVVLtwXWbvKnM2tqa6PRaFpa7JYrL+jYof0aFbKzs+6/9aq7f//UxCnTl60oqlj1XENFRTxStM4u7dyxw047bH/k9w7YfZcdm9/vziNan48mT49EInm5uZvsiC5CAesiPAObheKS0vpCaVmD3n8Lm96Qgf2GDOy3286DahOJoYMHrLVOv769b736wvpyIpGomx2gbo6Aurnuqqqra2sTaWmxVdMN1M2hl5mR/vWXnDeH84hU96e/vfrCq28WdijIycqKV1Z+9vkXkz+dueqF6j03WRtchALWRXgGNguLli6vLyxYtKSl2wLrM+rg/RrYQdFotC4nZ6RHIlmbpk+dR6S6kSN2u+b239WN11hNYUH7E448ZJO1wUUoYF2EZ2CzcM7JR59z8tEt3QpIbc4jUl1ebs4O228zZfrMgvz8Th0LturRffDAfgfvt1f7/HabrA0uQgHrEk2+HgYAAABYq003dSEAAACkKOEZAAAAAoRnAAAACBCeAQAAIEB4BgAAgADhGQAAAAKEZwAAAAgQngEAACBAeAYAAIAA4RkAAAAChGcAAAAIEJ4BAAAgQHgGAACAAOEZAAAAAoRnAAAAEJ4BAACgedx5BgAAgMj6/R9C73tX1zXEVwAAAABJRU5ErkJggg==
