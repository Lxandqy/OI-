# T2 交错四元组

---

## 题意简化

---

输入 $4\le n\le2000$ 的整数数组 $a$，元素在 $[-10^9,10^9]$ 内，可相等或为负。统计所有递增下标 $i<j<k<l$ 且严格满足 $a_i<a_k<a_j<a_l$ 的四元组数量，按下标区别方案并输出。

## 问题拆分

---

1. 固定中间下标 $j,k$，先检查 $a_k<a_j$。
2. 分别数左侧 $i<j$ 且 $a_i<a_k$、右侧 $l>k$ 且 $a_l>a_j$ 的位置。
3. 两侧独立组合，累加各中间对的乘积。

## 部分分（累计 20 分，$n\le20$）：四重枚举

---

1. 读入数组，$O(n)$ 时间、空间。
2. 枚举 $i<j<k<l$，共 $\binom n4$ 组；每组 $O(1)$ 检查三个严格不等式并加一。

总时间 $O(n^4)$、空间 $O(n)$；$n=20$ 仅 $4845$ 组。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			for(int k = j + 1; k <= n; k++){
				for(int l = k + 1; l <= n; l++){
					if(a[i] < a[k] && a[k] < a[j] && a[j] < a[l]){
						ans++;
					}
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## 部分分（累计 50 分，$n\le800$）：三重计数

---

1. 对每个 $j$ 从右往左计算各 $k$ 右侧大于 $a_j$ 的位置数，每个 $j$ 花 $O(n)$，共 $O(n^2)$。
2. 枚举 $i<j<k$ 并检查 $a_i<a_k<a_j$，每组 $O(1)$；成立时加对应右侧数量，共 $O(n^3)$。

总时间 $O(n^3)$、空间 $O(n)$；$n=800$ 时约检查一亿组三下标，1 秒测试机上实测可通过。$n=2000$ 的一般数据需要换用平方级方法。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[2005], greaterRight[2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	long long ans = 0;
	for(int j = 2; j <= n - 2; j++){
		greaterRight[n] = 0;
		for(int k = n - 1; k > j; k--){
			greaterRight[k] = greaterRight[k + 1];
			if(a[k + 1] > a[j]){
				greaterRight[k]++;
			}
		}
		for(int i = 1; i < j; i++){
			for(int k = j + 1; k < n; k++){
				if(a[i] < a[k] && a[k] < a[j]){
					ans += greaterRight[k];
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## 满分做法：固定中间两项的平方级计数

---

公开分档对应：1～2 点 $n\le20$（20 分）用四重枚举；3～5 点 $n\le800$（新增 30 分）用三重计数，连同前两点共 50 分；6～10 点（其余 50 分）用平方级程序。第 3～5 点接近 $800$ 个元素，四重枚举不能在时限内通过。

1. 预处理 $leftLess[j][k]$：固定 $k$，让 $j$ 从左到右增长并累积小于 $a_k$ 的左侧元素；$O(n^2)$ 时间、空间。
2. 对每个 $j$ 从右向左扫 $k$，维护右侧大于 $a_j$ 的位置数，$O(n^2)$ 次 $O(1)$ 更新；先计当前 $k$，再把它加入右侧，保证 $l>k$。
3. 仅当 $a_k<a_j$ 时加 $leftLess[j][k]$ 乘右侧数量，$O(1)$；所有中间对共 $O(n^2)$。

总时间 $O(n^2)$、空间 $O(n^2)$，$n=2000$ 时约四百万表项。严格比较使相等元素不被误计。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[2005], leftLess[2005][2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	// leftLess[j][k]：下标小于 j、数值小于 a[k] 的元素数。
	for(int k = 1; k <= n; k++){
		for(int j = 2; j < k; j++){
			leftLess[j][k] = leftLess[j - 1][k];
			if(a[j - 1] < a[k]){
				leftLess[j][k]++;
			}
		}
	}
	long long ans = 0;
	for(int j = 2; j <= n - 2; j++){
		long long rightGreater = 0;
		for(int k = n; k > j; k--){
			if(a[k] < a[j]){
				ans += leftLess[j][k] * rightGreater;
			}
			// 更新放在计数之后，保证第四个位置严格大于 k。
			if(a[k] > a[j]){
				rightGreater++;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## 知识点总结

---

四元组的条件可由固定中间两项分离为左右独立计数时，预处理一边、扫描另一边，比四重枚举更稳。
