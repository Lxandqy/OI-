# T2 平方和

---

## 题意简化

---

从 $n$ 个正整数中选择两个不同位置，使平方和能被 $k$ 整除，求最大的合法平方和。允许两个位置上的数相同，输入保证有解。

## 问题拆分

---

1. 判断一对数的平方和是否能被 $k$ 整除。
2. 对每个当前数，找到能与它配对的、平方最大的另一个数。
3. 对所有配对结果取最大值，并保证没有重复使用同一位置。

## 部分分（独立 20 分，$n\le2000$）：枚举数对

---

最直接的办法是枚举 $i<j$，计算 $a_i^2+a_j^2$，检查余数并更新答案。共有 $\binom n2$ 次常数时间检查；$n=2000$ 时不到两百万对，可以通过，但完整数据会达到约两百亿对。

$a_i\le10^9$，平方可能达到 $10^{18}$，平方和可能达到 $2\times10^{18}$，都应使用 `long long`。

时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
long long a[N];

int main(){
	int n,k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			long long sum = a[i] * a[i] + a[j] * a[j];
			if(sum % k == 0) ans = max(ans,sum);
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## 部分分（独立 30 分，$k\le10^5$）：按平方余数分组

---

只优化第二步。设当前平方为 $x$，$r=x\bmod k$，另一个平方必须满足

$$y\bmod k=(k-r)\bmod k.$$

同一余数组中，较大的平方永远不会更差。因此用 `f[r]` 记录已经读入的数中，该余数对应的最大平方。读入当前数后，先查询互补组并更新答案，再把当前平方放进自己的组。

“先查询、后放入”保证另一个数来自更早的位置，尤其在余数为 $0$ 或 $k/2$ 时不会选中自己。所有平方为正，所以可以用 $0$ 表示某组尚未出现。

时间复杂度为 $O(n+k)$，空间复杂度为 $O(k)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
long long f[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,k;
	cin >> n >> k;
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		x = x * x;
		int r = x % k,t = (k - r) % k;
		// 先查询此前元素，再加入当前元素，保证下标不同。
		if(f[t] > 0) ans = max(ans,x + f[t]);
		f[r] = max(f[r],x);
	}
	cout << ans << '\n';
	return 0;
}
```

## 满分做法：用 map 保存实际出现的余数组

---

完整数据中 $k$ 可达 $10^9$，不能按 $k$ 开数组；但实际读入的数只有 $n$ 个。将上面的数组换成 `map<int,long long>`，只保存用到的余数组即可，配对条件和处理顺序完全不变。

每次读入进行常数次查找和更新，映射中至多有 $O(n)$ 个键。时间复杂度为 $O(n\log(n+1))$，空间复杂度为 $O(n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

map<int,long long> f;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,k;
	cin >> n >> k;
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		x = x * x;
		int r = x % k,t = (k - r) % k;
		// 先查询此前元素，再加入当前元素，保证下标不同。
		if(f[t] > 0) ans = max(ans,x + f[t]);
		f[r] = max(f[r],x);
	}
	cout << ans << '\n';
	return 0;
}
```

## 知识点总结

---

- 两数之和需要整除 $k$，可以转成两个余数互补；同组只保留对目标最有利的代表。
- 不能使用同一位置两次时，边扫描边配对，先查询历史再加入当前元素。

