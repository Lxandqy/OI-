# 提高组模拟赛

第 08 套

提高组

| 项目 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|---|
| 题目名称 | 种树 | 吉祥 | 黑白 | 网格 |
| 题目类型 | 传统型 | 传统型 | 传统型 | 传统型 |
| 目录 | tree | luck | bandw | grid |
| 可执行文件名 | tree | luck | bandw | grid |
| 输入文件名 | tree.in | luck.in | bandw.in | grid.in |
| 输出文件名 | tree.out | luck.out | bandw.out | grid.out |
| 每个测试点时限 | 1 秒 | 1 秒 | 0.5 秒 | 1 秒 |
| 内存限制 | 256 MiB | 256 MiB | 64 MiB | 256 MiB |
| 测试点数目 | 10 | 10 | 15 | 11 |
| 测试点是否等分 | 是（每点 10 分） | 是（每点 10 分） | 否（分组捆绑） | 否（分组捆绑） |

提交源程序文件名

| 语言 | 第一题 | 第二题 | 第三题 | 第四题 |
|---|---|---|---|
| C++ | tree.cpp | luck.cpp | bandw.cpp | grid.cpp |

编译选项

| 语言 | 编译参数 |
|---|---|
| C++ | `-O2 -std=c++14` |

**注意事项（请仔细阅读）**

1. 文件名及目录名均使用英文小写。

2. 每题程序从指定文件读入，并将结果写入指定文件。

3. 提交源程序文件的名称与英文题名相同。

4. 附加样例位于选手下发包的同名题目目录。

5. 黑白、网格按数据范围表分组捆绑，每组全部通过才得分。其余题目各点独立计分。所有题目采用全文比较评测。


## 种树（tree）




### 题目描述

落落计划在一条长度为 $n$ 的道路旁种植一排树，路的位置编号从 $1$ 到 $n$。

在接下来的 $m$ 次操作中，落落会选择一个区间 $[l,r]$，并在该区间内的每个位置种植树木。具体来说，在位置 $i \ (l \leq i \leq r)$ 种植的树木数量为  $i-l+1$ 棵树。

经过所有操作后，您需要告诉落落每个位置上种植了多少棵树。

### 输入格式


输入的第一行包含两个正整数 $n,m $，分别表示道路的长度和种树操作的次数。

接下来的 $m$ 行，每行包含两个正整数 $l_{i},r_{i} \ (1\leq l_{i} \leq r_{i} \leq n)$，表示每次种树的区间。

### 输出格式


请输出一行包含 $n$ 个整数，表示道路上每个位置处种植的树木数量。



### 样例 1 输入


```
6 2
1 6
3 6
```

### 样例 1 输出


```
1 2 4 6 8 10
```


### 样例 2 输入


```
5 2
2 4
1 3
```

### 样例 2 输出


```
1 3 5 3 0
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 3 | `tree3.in`、`tree3.ans` |

### 数据范围


对于 $30\%$ 的数据 ，保证 $n \le 10^{3} ,m \le 10^{3}$ 。

对于 $70\%$ 的数据，保证 $n \le 10^{4} ,m \le 10^{4}$ 。

对于 $100\%$ 的数据，保证 $n \le 2 \times 10^{5} ,m \le 2 \times 10^{5}$ 。

## 吉祥（luck）




### 题目描述

在我国传统文化中，数字“八”象征着吉祥与好运，因此这个数字在许多场合中都受到特别的重视。落落深受这一文化影响，非常喜爱数字“八”，也很喜欢一些带“八”的成语，如八面来财、八仙护佑、八斗之才等。

数组中数字“八”在也具有特殊意义。具体来说，如果一个区间 $[l,r]$ 内恰好包含了八个互不相同的数字，那么我们称这个区间为一个“吉祥区间”。

落落非常喜爱“吉祥区间”，他想知道，对于某个给定的区间 $[l,r]$，最多能够划分出多少个互不相交的子区间，满足“吉祥区间”的条件。

### 输入格式


第一行包含两个正整数 $n,m $ ，表示数组长度和操作的总次数。

第二行包含 $n$ 个整数 $a_{i}$ ，表示数组的每个数字。

接下来 $m$ 行，每行表示一次查询操作，则包含两个正整数 $l,r \ (1\leq l \leq r \leq n)$ ，表示查询的区间。

### 输出格式


对于每次查询操作，输出一个整数，表示在给定区间 $[l,r]$ 内，最多能够划分出多少个互不相交的子区间，满足“吉祥区间”的条件。


### 样例 1 输入


```
18 8
1 2 3 4 5 6 7 8 8 7 6 5 4 3 2 1 88 88
1 7
1 8
2 9
2 15
2 16
2 17
1 16
2 18
```

### 样例 1 输出


```
0
1
0
0
1
1
2
1
```

### 样例 1 解释


对于第三组查询，给定的区间 $[2,9]$ 最多只能包含 $7$ 个互不相同的数字，因此无法满足“吉祥区间”条件。

对于第七组询问，给定的区间可以划分为两个互不相交的子区间： $[1,8]$ 和 $[9,16]$，各包含八个互不相同的数字。每个子区间都恰好包含 $8$ 个互不相同的数字，因此能够满足“吉祥区间”条件。



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 2 | `luck2.in`、`luck2.ans` |

### 数据范围


对于 $30\%$ 的数据，保证 $n \le 10^{3} ,m \le 10^{3}, \vert a_{i}\vert  \le 10^{2}$ 。

对于 $70\%$ 的数据，保证 $n \le 10^{4} ,m \le 10^{4}, \vert a_{i}\vert  \le 10^{4}$ 。

对于 $100\%$ 的数据，保证 $n \le 2 \times 10^{5} ,m \le 2 \times 10^{5}, \vert a_{i}\vert  \le 10^{9}$ 。

## 黑白（bandw）




### 题目描述

Shiro 与 Kuro 最近喜欢上了一种正整数，他们把这种正整数称作“黑白交替整数”。

对于一个正整数，只要它至少拥有两个数位，且任意两个**相邻**数位的奇偶性均**不同**，那就可以被称作是“黑白交替整数”。

例如，$34$ 这个数字是一个“黑白交替整数”，因为 $3$ 是奇数，$4$ 是偶数。此外，$765, 121, 7092$ 这些都是“黑白交替整数”，而 $5, 42, 756, 1009$ 这些则不是。

现在他们俩想要知道，第 $N$ 小的“黑白交替整数”是什么？

### 输入格式


仅一行，包含一个整数 $N$。

### 输出格式


一个整数，表示第 $N$ 小的“黑白交替整数”。


### 样例 1 输入


```
2
```

### 样例 1 输出


```
12
```


### 样例 2 输入


```
6
```

### 样例 2 输出


```
21
```


### 样例 3 输入


```
46
```

### 样例 3 输出


```
101
```


### 样例 4 输入


```
12345
```

### 样例 4 输出


```
274589
```

### 数据范围


对于 $20\%$ 的数据，保证 $N \le 10^5$  。

对于 $100\%$ 的数据，保证 $1 \le N \le 10^{12}$ 。


本题采用子任务捆绑计分。通过一个子任务内的全部测试点，才能获得该子任务的分数。

| 子任务 | 测试点编号 | 分值 |
| --- | --- | --- |
| 1 | 1～3 | 20 |
| 2 | 4～15 | 80 |

## 网格（grid）




### 题目描述

Shiro 与 Kuro 最近喜欢上了涂格子。

现在他们拥有了一个大小为 $n \times m$ 的网格图，一开始每个格子都没有颜色。

接下来他们会给整个网格图中的每一个格子都涂上黑色或者白色，但他们同时又希望每一块**相同颜色的连通块**在整个网格图当中都是以一个矩形样式呈现。

如下图，第一行的三种涂法是合法的，第二行的三种涂法是不合法的。


![原题示意图][s-08-original-5-X65]



除此之外，网格图中还有 $k$ 个特殊的格子，这些格子最终所涂的颜色应该是固定的。其中第 $i$ 个格子出现在 $(x_i, y_i)$ 位置，应该涂上 $c_i$ 这个颜色。

请你帮他们找出总共有多少种符合条件的涂色方案，并对 $998244353$ 取模。

### 输入格式


第一行包含三个正整数 $n, m, k$，表示网格的行数、列数以及特殊格子的数量。

接下来 $k$ 行，第 $i$ 行包含三个正整数 $x_i, y_i, c_i$，表示坐标为 $(x_i, y_i)$ 的格子应该被涂为 $c_i$ 颜色。其中 $c_i = 0$ 表示白色，$c_i = 1$ 表示黑色。

### 输出格式


一个整数，表示方案数。答案可能很大，请输出对 $998244353$ 取模后的结果。


### 样例 1 输入


```
2 2 2
1 2 1
2 1 0
```

### 样例 1 输出


```
2
```


### 样例 2 输入


```
4 5 5
1 4 1
2 2 0
4 1 1
3 5 0
4 5 0
```

### 样例 2 输出


```
8
```


### 样例 3 输入


```
123 321 3
100 200 1
120 200 0
100 150 1
```

### 样例 3 输出


```
131616716
```



### 附加样例

见下发文件中的对应输入及答案。

| 样例编号 | 文件 |
|---|---|
| 4 | `grid4.in`、`grid4.ans` |

### 数据范围


对于 $20\%$ 的数据，保证 $n, m \le 6,\  k \le 10$ 。

对于 $50\%$ 的数据，保证 $n, m \le 5\,000,\  k \le 5\,000$

对于 $100\%$ 的数据，保证 $1 \le n, m \le 10^9, \ 0 \le k \le 3 \times 10^5, \ 1 \le x_i \le n ,\ 1 \le y_i \le m$ 。


本题采用子任务捆绑计分。通过一个子任务内的全部测试点，才能获得该子任务的分数。

| 子任务 | 测试点编号 | 分值 |
| --- | --- | --- |
| 1 | 1～2、6 | 20 |
| 2 | 3～5 | 30 |
| 3 | 7～11 | 50 |


[s-08-original-5-X65]: data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAzcAAAIdCAIAAACP8xRpAAAy+ElEQVR4nO3d6ZIb13034F4BDKX4TvIl5XLsULRiW67yJSeRzcUkFVec5EvuJDY1WHp5y/N/faoznMEMZWFwDvQ8H1jgGPR042y/szRUz/NcAQCQmebcFwAAwB2kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAPCDTGmHw6Gqqnme46/xYpqm+96/fGd6W/rhWYzjmK5kHMfzXsz3aLfbxb3MN6rSzPM8DEN6XV26TyqvZduZpin9wye50nuvJy4g9QnFldp+v7/VlZUlfebzPO92u+pyXV9f3+q6U19xn+lG+ut5yze1kbik5Z+luNRxcxiG1JvdqjMnUj/BZ/fhw4fPPvusqqqXL182TTNNU9/39/3eaZqa5i/ZcZ7nuq7btr2V2J5e27bRo61Wq7j+/X7fdV1VsmEYNpvN4XAYhqG9EZWvlPuapqlt267rttvtz3/+87Zt67pOlefyvHz58pPKK7WdiGipTZ2rHaULjgvb7XZd1/V9P45jVYhhGJ49e7a/0bbt1dXVt99+W0p7GYahaZqu68Yb8eFvt9tf/vKX1YXa7Xb/8R//Udf1druNWtf3/X1ZrW3bqJxN00RPEgPQuernarWKy26aZp7nrus+fPjw7NmzgoLaRY6b403befHixeFw6Pv+aX7pU3xkn332WdxS0zRfffVVXdfHpzV1XaepTBpdzp7E27aNFvvq1atf//rXBbWWO71///7HP/7xarWKzijqX4zrRYir3e/3f/jDH7quOxwOXdddakSrqmqz2XxSeS1nO+mfpMb19OJq379///z583TlxaXq/X7f9/0f//jHH//4x2Vd+bLCRH3Y7/f/+Z//WV2ocRz7vm/b9ic/+UlKBsuGcEsaYlKryaG9xAW/fv36iy++6LruaVZuvl8XNm5WNzcyDMNypenUleTkHc1+v6+qKlJnzFeGYTgSqG/dcNTLM0a0aLRN08RqTdd1cRdV4bbb7Wq1ig/87Nth30GMN9FUYn5zrv40z/JaxrJYHgjVmcSQEzuG0abGcSwu6EQ1+/Of/1zclacKk5JKrNZUF6q5cX193XVdLCEvN+A+Fq0jFevZ20td14fDIVb1oq87fv25udRxs7tZjY4AE4uvTzB0nnwtbbVaxbQgwtY8z9Ff3/f+W/9TaifnyhBxwTH1jDbz4PmGIsRCeuzdROWL7qwqRJRFbGTEwDNN0+FwWK/X1SX6zuWVSZlGuFytVjENjdZ0vCvISgwwsW+bptFlLT/H0BILG+M4xj5UddHiBtMgEo3oyPtThD17tYyZVexBxXwm9j1LGX0uddwcb9Zo4+Bg3/exG1B8Skvbt9Fg+r6Pc5GliKWaqqrW6/XhcIiTQGk9o2h1XUemiVlaHB0oZdRJm2XjOEZxpNu5VN+tvDJZYowL/vbbb6M3iHXBfC7vQWk9o2maYRjixFJBh2zSVDnCcUFX/t1EvVoecU5HzR7/z89ov983TRMRLQqurKHzUsfN+aYK7Xa79XodrekJpmonb6uRNyNZx2rHarU6HA73ldatgjx7oca2+nq9joOQTdPEHm7pYoyP7ae01P8E04LvS6onKaksj8lfnk8tryPnb6pzaJpmHMd0/Llpmpi/lVXfohOLiBMlcvbh/JFShYlalE7KVz8AKbEdSQm5tZeYxkTnlp4oLCjlXOq4Wd+0muh4o/nEnZ40qD3FjCpuJo6jpSXQ+96cWy2MAtjtdtFC5nkuaGg5Itr8sraFUkadtDwTjSRazgWcezh1eZ33NPRut0u9QbSjgupbSP1AXHkp15+6rKhCsdd8Af3Y8c4hlnMikkaRldJeonSisUS3VtaO4aWOm9VftwdjsTDa0anX0p5uLhWjaYkH1aOpp6lMWRf/yA4obqqUISek7Yw0S77stYGiyys6slRksRxV0PUvFRfRbj04v/zJpUprhx8/GVCEdMHldmsXOW7Oi7b/ZKeDiix+AICLJ6UBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAH2pKG4Zhnue6rqdp6vu+vnHk/cs31HXdNM3x959U/Oqm+csHNc9zvGjbtroIUS5VVU3TFH+tyjGO43yj+uGZpukxN37r8zn7ZxXNJ9W3cRyrcsQ1x585fJjfwa3KUOItPNIwDNF7xz0+pn+LD2Se5+nG2T+cdAHzPBc34lzquNm27a1+IL04ne7Uv2Capq7rxnGMvHU4HFIRPrKCnr21dF03DEPf99M0jeMYt1MVLj7ViM5N00T7SZ1a/sZxXMb3/X6/Wq2qy5UGm2EYuq5Lcee4Ww3tjLOdaMjRcKLspmkqqNcehiE+vbZtU/Mfx7GgW0hT5U+qQoXqur8Mbfv9PkoterYj/dutpYH08zP2h3EZEXGipuWQHX/g4+b414JommYYhjR0lp3SmqbZ7Xbr9TqqXZRc27Yx17lPak6pplZnkn51rAjGHRWUZu4TVW15I1HzzjiQf5Ku62LUj2uOTjluobpEEQ7atl2G0SMpYflRxGzvwTXsk4qaFsUUf47jWFC2TtcclS2G/IIiWqoqdV3HZ15WxPxUUf83m02sjbVtG0V2XxO41UbSutoZP6IYKJummed5vV7vdrtSOucLHjebv4az+LNpmv1+3zRN9A8ncvJPLfqCw+HQ9/3vfve7vu/jxo7U/uWcJqRZ+NOL2Wc08rQe0Pd96bVtGIZnz55dX19fXV0dDoe4x7quC5ruRMWYpunFixdd13348OGzzz6rLtRvf/vbv/u7v/vzn/8cXfZ2u/3ss8+OT3VSt5hGoDNOeGIXqe/7qqpiQb2qqtVq9QT7Bd+LuOarq6tYnum6brfbnbRr/t71ff/hw4c03n/++ed/+tOfvvrqq+pCzfP89u3bSDm73e5HP/rRn/70p/uKLHr4W63mjDs5u93u2bNnaRVqv9+v1+uC1tIuddwcb4rjiy++iDlwWoE6rfn0xnEchmEcx7dv3y63qx8jBbXqfJaBsmmad+/eVeV79epVlM52u43Gv91u00mv/MU1T9P08uXLeZ4Ph0P68yK9evVqtVqlhZC0LnKkiGOql8/8u+u6169fx8XH9Re0lpNWMdu2ffXqVfRg+Xy2D0rbtRGO67ru+z7azgX7/e9/n7qF7XZ7/M3pONqdf316EdHmeX7z5k3at63KcZHjZlVVr1+/jrqx2+2ipE49bp58LpjW1VOde2QHd+ug67kqaJwJSPsd0zSlsw5Fa9v2+vp6fSN+sl6vo4CqEtw6tBFbn2WtbXySWIFOizqxexgbcHe+Py2h3XLGqhvHodJDA1FwpTSlqGOx2LxcAizl+qPCxGWnKc0Ft5c4RxiDTgxAfd9HL3Hn+2+VYzpvc67+8HA4pMMAh8MhznEWVN8uddxsbpZmlycHPmnVKd9zaVHPuq6LVbEH9ziWbePjF08sfm9sQkdYXK1WpUSZI+Z5vrq6SsNPRJy07F9KLxy7tGlt5oLPpUUe7bouUtqtM4V3Wm5xLk/bVGfSdd319fVqtRqGIa6/uCclo6ZdX19HNStlu/bj4L5er9OBoYsU+SAOlsWsIDqKUm45EkC0kciXZR3qutRxc1xMLCM9pxPDBae0uq7jQY90kLDv+3Qw5ci/Wo4u5z1PE207TtUcbiyf8ypUepw4tZ/jp2tzEye4l8dsy3pm8FPFGnusgsQ+5neogWfs6KMfWK/XsSIYLSitEJRiuJGmBGX1AzGWRFe22+3S11VcpLjZdDoq5m9H9mQ+Hm7Ou8mYHsiNll5cS7nUcbO6GXrquo4TaemJ6dP+xpP+v388rVmeHb5PVt/wtPxWp/QdPBdQ1dIBwfQJl5LPkrQYE93xpa6ihfTNQ2lR5MHIlVU7St8ksnwYqKyBJ0kbAmX1A9FxLZv5Bc9q4tZiSvOYYza3/qezdybL/rm4iHbB42b119uJk0JPc/D3kgc2AIBySWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQDgh53S6rqe57mu66qqVqvV8XfG2269Ppe+7+PPeZ7TX0vXNM1+v4/X4zhG6VTliKud57lt27quD4dDXdfTNFUXre/71BzmeW6aY+03h7aTxJW0bRvXnM+FPV76tOPiy7qFpmlSA6/r+jI6sceY53kcx6qqHuwc5hv3/fWJxdXGiBk1reu6gqpc0zS3mknbttVFqG+GmzQGPcHQ2Z30/z0lgCi2rvv/vy7lgzt9fM/nzRCHw6FpmsgB8zynF1XJDodDZOVxHKNcpmkqqyGN49i27W63S13A8dRStGmaondo2zYl1CNZ4dYYE29L06Snl351dAjRgpbRIXPzPE/TtFqt9vt9VLN5nlerVfTXpYhP/ocwq4n6H8mm67rdbpdmCA/+w9S9nzEVNU0T/Vs0/Lquh2EoaG4wTVO07riRaPgFXf99om70fT9N07IHO+l9nTylpYF/nuftdtvcON61pRGlykDbtql69X2/3++jtVyGtB4zDEM0p1KCTl3XTdNEstztduv1Ojq16kLF3LRpmrZtY5Lz+FE2paLzNqsYaWK2NgxDWSmh7/vD4RARbb/fd103TdPx2WZWUviIcPmYtdiixeRzv9/Hja9Wq7quj3cRtwba8+aJVDq30kApTSYaSLSaGEMj3JQ1q7nPdCOtOp26qjzFWlpUrL7vY2bzYDndWnauzioadvwZnfKzZ88uYC2t7/somui2Yt+wKkcsaq5Wq3me1+v14XC4+E2cGGLHcez7fhiG42s59zWic5Vy27bDMFxdXaVwE+sEVSHSCvo0TZvNJk3VSmk1McOMhaV4UV20WD+LcBY/GYah67oj/fZyUSTa2hk/pfjVEQXSpm1B9S0aSDSW7XZb1/XV1VU0oqpk81/rT7SjruuapollgrLX0iIHxC09ZiFquZaWw7paWrDdbDa73W6/3xc0utwn8lnbttFyYp0jTQ7yFxklzThTHTt+5LFccb8x8MT0Ok0b7rNsO6kFnaspRX27vr5O24XnPffzqWIZIHY8D4dDdGWP7NBysN/v05JG3MV6vS7o8/8O1uv1drtN+SxWdx5cPkynqc6+6Rm92XAjpjRd15WyFhVjSiSYaO8fPnwoqL0cn202TROFEhtQJ41of/kwT91QI9BEDfv666/7G9FZ3Pn+5XnJ5WbNuYJR2oSOpj5N0ziOq9UqTW4KlYb5zz//fLvdxiAaZyCqckRr+cUvfjHP826322w21YV68+bNMAyxahg1MO79vvKKHdK0yZV+fq52FL83bmGZp0sJCvv9frPZRKuP7aeY4ZSyaRiHtGIhs23bvu93u13XdV9++WV1uV6/fh0zz9h3O1LfUiyLhhMjznnPcabfHj1z3/cfPnwoaBYaaWaapvV6PU3Tbrd79uxZ6SltvOl7f/KTn6RT3bG5Ufa5tHQKLXamfvnLXz7+icIU18477V7OANq2ffny5YsXL6rCvXnzJu4i7RWWda4r6sMwDH/4wx+iqqzX6wteS6vr+le/+lVaDIjQcyQiLAeYHHY8w9u3b3/6059GfYuBsJQqF598/Pn73//+5z//eSxHVeVY1pl0I9XliiXPf/7nf46e7fhUP30FQYiIVp1VTAa6rvu3f/u3Fy9epBlOEZbLlvH63bt3z58/rwo3TdO7d+9iQ6Ou67RVeFInnwhGCIhjT7EQ9WBEuxXOzttgYoUz1jZT6y1rwelOqc9KK4Vxp1U5lsucUUMuNaKlbfe0URi7CY/8t2nsqc4qzkFGkRX3THHs3cTAGZ9/rGtW5UirRGnSW/qGwIOdw36/j4gWCfvIiY50MCAOgZ09oqWxJk6ktG1b0HGUW9/8Eg/clHXC4T7pkdXU/T5BIzp5wce8OcrskYfMcnt6YPkU8dkflPsepRNC6bttCuoIlrEj5gCXUSj3Scfvlt8UcMSdmey8QS19h0jax6mK8vEcoMQHVqLyXPw31yzrWFodeMwsNJNuZPldXOmrrKpipcWnqnzN//3exCcol4ILHgDggklpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR/U8z0/wa+Yb79+/r6pqmqZ5nuu6vu+dTfOX7Bjvadu2rutpmsZxfILrpBRRPaKqPH/+vL5RXa43b9580vuj7TRNM47jMAzp83ma9k4pvvzyy+pCTdP07t27GG66rhvHsWma++p/0zTTNFVVFa0mRpwj4xQ/TPM8t237/PnzGHqmaYo+tm3bglPa8gaGYYjXR6p+3Ha8iMaThuSTXifFiao7jmPXdfGTU7eWgqR2FBOkFNHih3DZ9vv9arXabrebzSZ+Eint+NCzHHGi1Rh3uOX6+vrq6iqmvhHrT51PTp7SYrSY53m/36/X63mej7eW9PO4MAsA3Gme52maYql1t9utVqtYc73UFPId2mlqO7faFNyqJBfcPzyyCdR1vXzbNE0R0TQZbqnrehiG5kb1JJ4ipaUZyWOWOpbz/gvuRPi+pEoV099LTWmfatmOlkOUBsUPxH6/7/t+HMfY/X/8P7SQxvE12rQckLbFy97xXDocDn3fx9Zn2qW65db1GFS4U6pCqVLx4GxHSuMH4lZVj6W12J+67/337eTAxwtPT7kicPKUllrLBe9Gkc8ZLB0rEJO3/X7fdV30CXoGvhe31pjiQZOTrhTcvaD1PUqHAx4/R1kGx/R+bYw768myYtyqbD9kt2ZfKb9qR/wQxKgZD2zGT+Jhz+NraR/TXvh4IW05+jzBAbWn2PFMB4bSESLP4vE3ulWXlscfgR+45dMDn7qNY0me45ZPQC4fDT4Rz7AAAOTIQTEAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0A4AeZ0qZpmue5qqpxHOd5Hoahqqr4SRHiUqcb8aK6FPM8L2+qoEJJ4sqjUl1Y6Rz34J1mWJrjOMaLKK9UasU1mfhsM/yEH1TiNX9nadz51Mq2LOVM5HY936EILqP6zTeWo+cT3Ff9BB/cPM91XUdptW07DEPbtvGTO9/8f67vnrc9mSiMtm3TXaQXFyPu6Hi55GYYhq7rIvp3XXd5hXLLNE31jegm0utS7jou9fr6+urq6uM2VYT45Jumub6+3mw2dV1P09Q0ZWxHxEd9q/LE7VSX217idYm3OY5jXddN0yzbyDiOBd1IDPfp4qPHLj2o1YuGs5ytnbRcniKlHQ6Hpmnatk0vqtKkfJkCwQXUtugIxnHs+37Zj1clGMex67rlX6M7KKgX+1RpiE2dxSdFnCjZc6WilMxS3Cwo4oTD4dD3fXzs8To6hKoQywaeslp1oaJ2RTHFTx5cHbj1mcRKyRmraNxCXFUsR5U4dA7D0Nworr3fJ1r9MAzjOK5WqyeYLZ98VE6d8vKH0WDuvqC/rldVeUhtNWLBsuVUJYs93Bhj0gp/NKeqENM0DcOwWq32+31742I6ggeLLM0c7nvzsoreinfVOaSrjRfLP6ty7Pf71WoVr8uKaLcqTBo7qwsVXcE333xzfX0d4Szazn0jS8qvTdPE6/Men4hYFtsF8WK3261Wq1IOdaSUfHV1tdvtogiiFKqSTTf39cUXXyw7rlP3Y0/Ry0Slj5STtqge/CdVHqLRxpwsEudyLb1cMbmJJfR5nssaLFMKWa1W8zynzusCyuU+v/3tb3/0ox/t9/vxxoOjTuoW06GW+OsZT4NFWIxOIFbWP//88+vr66oE0Uai1ez3+/V6HaG5lCoXRZ8ae9u2fd//7//+769//evqEjVNs7/xm9/8Jm78+GnOlNKW28HV+cR5gMgEL1++/OlPfxrrNwVNDOLi08Tm5cuXv/jFL0ppL0e8f//+1tLgqUfPkxd50zTb7Xaz2XRd9+rVqwdnb8s1gDTMpCXfpzfPc0wIopEcDoe6rmPZpirZMAybzWa/38cyYQzqMV2rCjFN02q1+vOf//zVV19FO4k9teoSrdfrv//7v7+6ulr+8EivHfk7jTcppZ2xlxzH8ZtvvvnZz36Wrnm3263X66oE8QFut9uu6/7whz/80z/9U1k7hh9P97/99tv/+q//qi5U7EbFcvsynz1YZLfy2RnXntNYuVxBz2eX6TEOh0MMKGmIKev6P1bX9YcPH9KOX8zTTr0m3T1NGjgcDl3XNU3zy1/+MqbRD/7D5QbNGVNaVVWbzWa73VZVFZtrb9++ff78eUEd9J3evXv34x//OLbV00nVqhwxak7T9M0338SRwUKPPD7SPM8R0YZhSOs6x9fS4sWtMHGuXjL202NBfRiGqG/r9bqUXjvayGaziSKITzW6taoEaRoTN9J13bNnz0r58L+zGHRS8IpN9jvfees8QFpXO9dHlM7VpHNpUWqlFNlyIT8tO5Vy8cfFxDLy2fIUR3UyJ+9iomKlI5xRZin3HJHJ4+5t28YEOjrluq73+33pES1O2KzX69RnxQhaUFZLzwrEKc4YLMvaEfgk6dsr0pT0wacBPj4QfcbzlOlXL5/uLKi80mmN9LFP05S6tSLEZx4PQKQT0NWFSoEsiqzv+8PhcGSqnwaaTNZ70hGOlC9L/HqBuP7UOZd18XeK5YDUcaWHoqpTeqJzabfy1oMRLR/Lr9tZ1rnSRcVK42WJR9NCSpYXUzR3itJZTqYf7PI+3pI7Yy+Z0n8sEsRfyyqv2EFezhCqoizzR3zyhTb5R4rOLT2T+5j4dWu7M4e4lmpacRHt1hSxrMZ+n3iCMN3L06xrFNbRAAD8QEhpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0A4Aec0g6HQ13X8zxXBarrOl60bVtdilQW6cU4jlU54rLHcZznOQooFdNFapq/NNXhRrrlaZqqQsSl1nU9TVNc/HyjKkeqYPFiv99XRZnnOdr4MAxlNfbvrOu6+DNGn2hED8qhJ0ltJG4hNflSxAUfDofU9ruui78WbZqmpmmWfVf0aSf9pX+pASc1DEPXdX3fLzu1vu/vK7BbdfHs/Xg07Hme45rbG1FUVcnquh6Goa7riJ7xoqC+IHW70UKiaEovlCMij0aXHc2quXFfA7mvHM/VoJqmiXCQXqzX66oc0Y9Fw9/tdvM8r1arw+HQ931Vgrjyruu22+1qtYqGc/be9XRiMrDf79u2jTWCruuix7vz/cuPYjkAP9X13nE9bdtGLx0lFWmglC6urutxHPu+j4YzDMN2uy2lsRyRPv8YgKJoUrdcakqLELDdbjebTX1jnucjmTq3jqPruv1+33VdzD6j5ZfSVI5o2zbqVuoCYsgvJaVFLxyXHbl/mqZxHC9pvXMpbnYcx2EY1ut1JIbvMJCcsXxjSWO/3/d9n+peKU0prjM+vc1mE5VttVpVhYhY1jTNer2ORY7UA1ykNH9Lc7n01wfbxVMuk9ynaZrUm8X8M+JOVYi4+Gmauq6LHLNerwua1dxnnufr6+uoLdvt9urqKk3hqpM5ealHjY95c2zWrNfr3W53fE4TYS6HxBCLFsMwxDATf63Kl5Y2I+gc78IyFDUkRCOJHFNdqKZpttvt+kYE6+gEj9xy2jSp8rDf71c3ogfP58IeI21zpBWasmY16Rai4UR72e121YWKcJZiVuyEbDab+275ztp4xvKdpimuOcprHMeYmJVS3yJfxopM3/fzPG+320hsVcnquv78888Ph0PXdVdXV+M4pv2oglNa0zTRO8frvu93u92RHc/ltGbZSM5VutHaY6lmGIa+7/NJkH+LKJHYgYrbLGuuFv1v27axMJOCS3Wh5nnebDZp2pDu9MEdnHyq63q9TnODNPCU0muntdtoO7EuFeuCVQliIbZt2zThTJPnC5aWoyIrbLfbx/yrdIT6jJUz1jujc466F5OEUtYI4pNfHhCKiUFVuOFGtPool1gvPOkvPfmoPE3TarWKEJCOE0ZP8Rhn78Svrq5ihTN2PKPlXMDO2uFwiFhza3Xw7B/4I6Xjz/EizkBkEkdOIe28pE3e46k6fRTpoOt541r0aG3bprYTF19KeaWPPfJldGUF7XimTdvlXnNxD0A8Xpzo6rru5cuXKXIdWUtLRzxjBS6OHJ2xP4yz9qvV6vr6ummat2/fph2PIjRNEwuB6fVqtXr16lUpKfM+sbEWASYODj5BDXmKtbTdbrderyN+fuqp1TSZqM7k+vo6jgmnmXSsdlaFW61W+/1+vV7H3lP8WVDKiSKIjjhddizPVJdonudvvvnmw4cPV1dXcXJguUr9sbQOH80tdY7nergvHX/+/e9/33Xdbre7urra7XZlzXbSBsc333yz3+8L2mRPR7kjhaQ9tepyxQGVX/3qV2k+c6S9fPzEwHnXriJGx/HB9+/ff/nllxELCno4N52djc/2zZs3X331VUFB8051Xb969SoydEzV0hMS1ck8xZC2Xq9jZ22e55cvXx4/NRzbWKlbj7gaZ3Wrc0jfHZBmWtM0vXv3rqDWcqdhGP77v//7+vo6lqBSxCmoFUW4TA9wXXBEiw76Jz/5SdxmNJDjC7qpiS0Hm7On8Ldv3/785z9Pi3wFjTppVWCapjdv3nzxxRdlfbVQenogra02TfO73/2uulBxs2nVNqbWR9Y+P24X543gUVJx/DHmBmV9k0X6DoHoc+I0Z1W++aYvjTlPnHd8gpM2TzGqpaWapmliTlCWW2PbmzdvXrx4URXu9evXP/vZz9LdnX38/s7evHmTnlGtLld63jvlreNdw/KJ8Vtf9HVGaQ4QRVZKRFt+P1+6i4Ii2vIMTaoDBR1F/w5uneIocdUwfSXCg1+MkKFbB/vi8FZBSwBHpIWk5NTt6JIHNgCAcklpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgCXZpqmvu/j9TzPj/+Hn/Tmk5rnua7rtm2rqqrruipKXHbTNPM8N00Tf70A9U1BzDfGcazrepqmk/5GKQ2AizKOY9M0h8Mh4lqMrMMw3Pf+eWH51+pMxnGMQDDP83a77fs+sk5ViK7rxnHsui4SzDRN8zyn0Fyu/uYWxnGMStW27eFwOHW5dCf9fweAJxYrN8usU9d119073uW2UpWuv23bzWYTUeDUazbfowjEwzD0fX84HFKgqQp3uLmFpmnquo7Xfd9HMZ3ul0ppAFyUiGWx8hGLal3XHVmOimWzlNVu/fXp7Xa79XrdNM04jikZpEXB/MWVR5Tpum4Yhuvr69j9rErW3phu9H0/3DiS/r8XUhoAF+VwOKxWq3Ry6MG9tmX6ib3O8+ah9Xodm7axbLNer3e7XUHLafGxR1YbhqGu69VqldWZv+9mGIb9ft+27TAMsaV7ZBv9+yKlAXBRIhPEVlQkm8PhEKe77nx/2hVNr+Pn50oV8zynTc+6rne7Xdu2BUWcOJcWQTMdDSwlYh4RoXkYhvV6Hfns1AtpUhoAlyat38SOW/r5kRWyWEKLVJGC2hlX1IZhiEcj40b2+31VjnQirWmauJHqIszzHFucKUbHzZ40q1lLA+CixKg5juMf//jHWNSJ1Z373p82E9u2jdfjOJ5x33Mcx1itiWv413/91/StFlVRpmlK609v3749UgRFmKYptjsjqEVuK/5cWhRSnIVMXzRyZI6SGka0mcjgZz8lEBewvKTSxecZOwKxqF7X9amfVfkexaPdsZ0RE99oP9WFGsfx3//936+vr9OuTRTWkR2cGG/SuZBl63t6UUx1XX/99dfPnj3b7XbzPK9Wq1J67ahs6an7N2/epJ9XJUjNJNp7LDJdRld23PPnz9NuZimFlcQ1v3nz5ssvvzz7IPipbl3wmzdvXrx4UZXv9evXEcuerDhOntKaprm+vr66uhqG4XA4vHv3LgbU4/9k+YV+UVPP9RBv27b7/X69Xk/TFCdSx3F88+ZNcQ3+lnEc379/H1PGtCg9TdMT7LJ/j+USs7TIK5HYLnXg2Ww2//AP/7Ber9O+zPHZTvoolkehz/6VS69fv/7Nb34T1/ZgP5CV9IRd27a//e1vf/WrX0X2LaUfiO2n5aJR3/dff/31ua8LeMDJh+RhGK6urmL4b9v2H//xH7uuOxJC08PG0f3lMOjGlcRG+zzP79+/j/lZVbKXL19++eWX6SmVdIaglIEznn4ahuHVq1dRSQpaCPwOYjU6NZBYgjq+lpZeLxvRuVJFfA9k+q7L2E4q7rRNnEqJJwdjOaoqRLrUmMxEqy+lscMP2clTWgycKXtF0InHbe58fxpRbj1oc65UtN/v44nuuOD4JuiC5tD36bouPur09YPLeXb+4htr4nBAXddRTPFndYnSd16nBvXgyYE7f36udpTOCUU+iJBdVkSLJwfTg/exxL7b7apCxCefwnFsiJ/7ooBzp7Q4zhXDfxy7a9v2yBPRdwayM6ai9ER3Oi242WyKOyLwscjKsYMTCxtP89Uv35flVwum0rnUiBaZIC2eRd17/A5vJtV1nuf9fr9cuC3oNPQ0TSncRFc2juNut8vhg32k1Ma7G9bSoAhPseOZjjrF6/R9d0f+1Z1BrTqHw+HQtm26hUyeZvjbRRHEpmEs1ZR1ziaO003TFANn/PAJvgb6XFIAjeNcD1a/9IblO8/7tQJd16U5T4lfnhQXPI5jnLI97+zxU8VzJCmfpZ2Nc18X8IDTfyHb4vnnWAmIE9+ftCNzxq4wlmridZwHiv/SRVW4+F6+uJf0nyUuaG0jRs34j6jEX7fb7WazqS5UelTzkWfvbpXj8hs7q3OIfiCdiIqaVtDybaScmBjsdrt0tK4qRKw6p2Yet1PcjjP8AJ08pS3PdMcwE7PqTxotzrtwlb69Op5jj0Pcpeu6Lr7W4XA4xG5OvKjKkf6rKTEIbTabC36AIH0rT2SFB7955FaTyWHpNw5CpaeJ4/xDVYjll6en02kFneOMrxGJeXIcFbCWBkV4iqcH0nfVxKBS3J7Ure8vKGgCfUTcRcyt4/R9DgP5J4mD28tvDL/UiLaMWbEUXWI7ulX3Ssk3Hzf89LxkQbcQu8zxZ/phQdcPP1jF79wBAFwkKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkqHuC3zHPc31jmqZ5nuMnTdMceXO8qKoqXp9XXdfzjbjmYRiq8sUH2zRNfM7ph8u/Zi6udhzHqFpRx6oLNY5j/BmVMBXTkVuOSrv8WFLjOotpmuIumqYZx7Ft2+KaUtu2cRdR98pqL33fHw6HeZ67rivuk/9U+/1+tVpFtxC3nEaf4/Ip067rUquP5tO2bSbX9qBhGPq+j888Wk3f91X56r92p8Mw1HXdtm2MPvflmWJSWtSweZ6j2KKzu++dd44i5x1d0qA4DEPTNF33RB/aSUVBRMsfx7Hcjnuz2USPXF20qHWRbKLjW05m7utNbrWaM45A0Wu3bRs1bbVa7ff7qhxx2TFexmB5Ky5nrq7r+MDX6/Vut0uJs7pQq9XqcDi0N8ZxHIbhyKCTmkY0maZpHhnpTifqWLT09XqdRsBSJqJ9319fX282m/gwm6Y5HA7xuirZfGMYhuiQY5ng1JHg5IFju92uVqtYs4mZzfHUefZAdmepTNPUdV1Usqwu7zuLUojpWlrVKKjjjs43Cigi2jzPh8PhUuNa0zTX19dXV1fLHiF1Fh+LVbe0DJxGoHPV3phJT9OUIloqwSLESBOfXrwupaWEVPq73S5d/EkXAM4r6n/TNP/yL/+yXq/TCuh99T9NYFKriaB23rXn6Jn/9Kc/vX//fhzHU6/ZfI/S+uXhcOj7PhY4vv766+NZOX/zzWJTlE5UpydYtTn5L9hsNlFUKXtWVRUld+f775zBnLGppAXzuOamaWIxo/SsltbSYjYQuyFnn0E+XlpwjguOrHkZi+p32m63//M//7Pf78cbscx+pIOIwSalipTSzhWMoo61bfvy5cuu62IULCjrxOdW13W0lK+//rrv+7iLqhzxmccKzeFwKL0TOyLSwPPnz2MmU9f1kSlNuHXG5rxHblJJRZuNKU1BESftdUZfHS8uoL5N//doTaSCUxfNyXdAUl2f5/nt27exEBo3duf704Q1/TVeHA6H6nwTmsPhcHV1tdvtYqfpjKPd9yWtC6YdgXSMoyrKPM8vXryIkyibzaa6XNONNNIc7xqWE4m0lnbGjjIuIJJBpLS0x1SVIF1qDPa3yiJ/ESijwlz8QlqMF3H8MRbX41BEOtZ5p2UsO/up6IiV0XJXq1XUuoLay62glkqk9FpX36xGR4BpmiYWO0/dDzzROZX0W2JP98i2VAoKt9rM2Us3Tjmkg89V4Zblnj7eglbU08C57L/Kuv5PdStsHT+9/nFvft5V0rQksFxKL6u8Uj6LsWe3263X66oo33777bNnz9KzUEf2NC5G5OnYqHp81332PLTs1mK749b6RebiHOqt6cEFmP9aMZZtp/i1tLiZeZ73+310ascnNPdVxDOOMbFgm645tZ+qZGmYT+cG0oH0UqSeaxzH2JW+jAB9fKV9ecjsSCXMrR1F0aR8UNf1drstaO0ztfq4/vhrQfUtXXnqisuKyN9BnLVdPhDw4JHoeJFa1tkfWVvuRBVXWB8n3bNn379dNPkYNJ/siwWeYi3tVtf24JuXf82kUJfnAy6jti2/8eTWiyKkq734weZODxZWbqV5ZwsqqOyWF/w0h1FOIS1sFPf5f6p06jHtEjy4yZvVubR0DcuvGcqtUR+3XDJP3/pU0PXfJ61rxMr6E9xXLt8NAwDA0mVOpAAASielAQDkSEoDAMiRlAYAkCMpDQAgR1IaAECOpDQAgBxJaQAAOZLSAAByJKUBAORISgMAyJGUBgCQIykNACBHUhoAQI6kNACAHElpAAA5ktIAAHIkpQEA5EhKAwDIkZQGAJAjKQ0AIEdSGgBAjqQ0AIAcSWkAADmS0gAAciSlAQDkSEoDAMiRlAYAUGXo/wHkIybpg6JDEgAAAABJRU5ErkJggg==
