# T2 平方和

---

## 题意简化

---

输入 $n$ 个正整数 $a_i$（$n\le2\times10^5$、$a_i\le10^9$）和 $k\le10^9$。从不同位置选两数，使 $a_i^2+a_j^2$ 是 $k$ 的倍数并最大；保证至少有合法对，输出该最大平方和。

## 问题拆分

---

1. 求每个数平方模 $k$ 的余数，确定合法配对需要的互补余数。
2. 在每组余数中保存最大候选；同组配对还需第二个不同位置，最后比较平方和。

## 部分分（独立 20 分，$n\le2000$）：枚举位置对

---

1. 读入 $n$ 个数，存储耗时、空间均为 $O(n)$。
2. 枚举 $i<j$ 共 $\binom n2$ 对；每对用 $O(1)$ 算平方和、取模并更新最大值。

总时间 $O(n^2)$、空间 $O(n)$，代入 $n=2000$ 约检查两百万对。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	long long k;
	cin >> n >> k;
	static long long a[200010];
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

## 部分分（独立 30 分，$k\le10^5$）：余数数组

---

1. 扫描 $n$ 个数，对每个平方余数保存最大的两个原数；$n$ 次、每次 $O(1)$。
2. 枚举 $k$ 个余数，$O(1)$ 找互补组并比较，同组需两名。

小模数子域时间 $O(n+k)$、空间 $O(k)$。代码在 $k$ 超过数组上限时用成对枚举保底，仍保持答案正确，但大 $n$ 时会自然超时。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,k;
	cin >> n >> k;
	static long long a[200010];
	for(int i = 1; i <= n; i++) cin >> a[i];
	long long ans = 0;
	if(k <= 100000){
		static long long first[100010],second[100010];
		for(int i = 1; i <= n; i++){
			long long x = a[i];
			int r = x * x % k;
			if(x > first[r]){
				second[r] = first[r];
				first[r] = x;
			}else if(x > second[r]){
				second[r] = x;
			}
		}
		for(int r = 0; r < k; r++){
			int s = (k - r) % k;
			long long x = first[r];
			long long y = r == s ? second[r] : first[s];
			if(x > 0 && y > 0) ans = max(ans,x * x + y * y);
		}
	}else{
		for(int i = 1; i <= n; i++){
			for(int j = i + 1; j <= n; j++){
				long long sum = a[i] * a[i] + a[j] * a[j];
				if(sum % k == 0) ans = max(ans,sum);
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

## 满分做法：按余数维护前两大值

---

独立小规模档 $n\le2000$ 用下方两重枚举；独立小模数档 $k\le10^5$ 用余数数组；其余 50 分由本程序覆盖。

1. 扫描 $n$ 个数，计算 $a_i^2\bmod k$，用有序映射为每个实际出现的余数保留最大的两个原数；每次插入 $O(\log M)$，$M\le n$。
2. 遍历最多 $M$ 个余数组；对余数 $r$ 查询 $(k-r)\bmod k$，每次 $O(\log M)$。异组用各组第一名，同组用前两名，取最大平方和。

总时间 $O(n\log n)$、空间 $O(n)$。$a_i^2+a_j^2\le2\times10^{18}$，使用 `long long`。同余数组中的两个值来自不同位置。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

map<long long,pair<long long,long long> > best;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	long long k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		long long r = x * x % k;
		pair<long long,long long> &p = best[r];
		if(x > p.first){
			p.second = p.first;
			p.first = x;
		}else if(x > p.second){
			p.second = x;
		}
	}

	long long ans = 0;
	for(map<long long,pair<long long,long long> >::iterator it = best.begin(); it != best.end(); it++){
		long long r = it->first;
		long long other = (k - r) % k;
		map<long long,pair<long long,long long> >::iterator jt = best.find(other);
		if(jt == best.end()) continue;
		long long x = it->second.first;
		long long y = jt->second.first;
		if(r == other) y = it->second.second;
		if(y > 0) ans = max(ans,x * x + y * y);
	}
	cout << ans << '\n';
	return 0;
}
```

## 知识点总结

---

模条件把两数配对时，先按余数分组并求互补余数；相同余数组要保留足够多的不同位置。
