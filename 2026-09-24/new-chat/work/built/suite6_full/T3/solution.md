# T3 三元组

---

## 题意简化

---

输入 $n\le10^5$ 个三元组 $(a_i,b_i,c_i)$，三者为不超过 $10^9$ 的正整数。对每个 $i\le j$，若 $2\min(a_i+a_j,b_i+b_j)\le\max(a_i+a_j,b_i+b_j)$，累加 $c_ic_j$；允许 $i=j$，每个无序下标对只计一次。输出总和模 $10^9+7$。

## 问题拆分

---

1. 把好对条件拆成两种互斥的“单点键之和不大于零”。
2. 对每种键，统计满足阈值的 $i\le j$ 的权值乘积和。
3. 把两种情况相加并取模。

## 部分分（累计 20/40 分，$n\le1000$）：枚举下标对

---

1. 读入 $n$ 个三元组，$O(n)$ 时间、空间。
2. 枚举全部 $i\le j$，共 $n(n+1)/2$ 对；每对用 $O(1)$ 计算两个坐标和并判断条件。
3. 合法对加入 $c_ic_j$ 并取模，每对 $O(1)$。

总时间 $O(n^2)$、空间 $O(n)$，$n=1000$ 约五十万对。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
long long a[100005], b[100005], c[100005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> c[i];
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		// j 从 i 开始：允许选择同一个三元组两次。
		for(int j = i; j <= n; j++){
			long long x = a[i] + a[j];
			long long y = b[i] + b[j];
			if(2 * min(x, y) <= max(x, y)){
				ans = (ans + c[i] * c[j]) % MOD;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## 满分做法：排序、前缀和与双指针

---

累计前 20 分（$n\le1000$ 且总值较小）与前 40 分（$n\le1000$）均可用下方两重枚举，后者必须取模；其余 60 分使用排序与双指针。

1. 分别构造键 $2a_i-b_i$ 与 $2b_i-a_i$；两遍各 $O(n)$，键用 `long long`。两种不等式不能同时成立，因为原始两坐标和均为正。
2. 每种键排序 $O(n\log n)$，计算权值前缀和 $O(n)$；固定左端 $l$，右端 $r$ 单调左移，求满足键和非正的右侧权值和，共 $O(n)$ 次移动。
3. 把 $c_l$ 乘以区间权值和并累计，含 $l=r$ 的自对，每种键 $O(n)$；最终两种和相加取模，$O(1)$。

总时间 $O(n\log n)$、空间 $O(n)$。排序后只计 $l\le r$，每个无序下标对恰好一次；两类条件互斥，不会重计。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
struct Node {
	long long key, weight;
};
Node p[100005];
long long a[100005], b[100005], c[100005], prefix[100005];
int n;

bool cmp(const Node &u, const Node &v){
	return u.key < v.key;
}

long long calc(){
	sort(p + 1, p + n + 1, cmp);
	prefix[0] = 0;
	for(int i = 1; i <= n; i++){
		prefix[i] = (prefix[i - 1] + p[i].weight) % MOD;
	}
	long long result = 0;
	int r = n;
	for(int l = 1; l <= n; l++){
		while(r >= l && p[l].key + p[r].key > 0){
			r--;
		}
		if(r < l){
			break;
		}
		// 区间 [l,r] 包含自身，恰好统计一次无序点对。
		long long sum = (prefix[r] - prefix[l - 1] + MOD) % MOD;
		result = (result + p[l].weight * sum) % MOD;
	}
	return result;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> c[i];
		p[i].key = 2 * a[i] - b[i];
		p[i].weight = c[i];
	}
	long long ans = calc();
	for(int i = 1; i <= n; i++){
		p[i].key = 2 * b[i] - a[i];
		p[i].weight = c[i];
	}
	ans = (ans + calc()) % MOD;
	cout << ans << '\n';
	return 0;
}
```

## 知识点总结

---

若成对条件能写成两键之和的阈值，排序后用移动端点求合法区间，并用前缀和汇总带权贡献。
