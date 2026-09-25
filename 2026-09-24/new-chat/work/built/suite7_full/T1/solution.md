# T1 回文串

---

## 题意简化

---

输入长度 $1\le n\le10^6$ 的小写字母串 $s$。可任意重排字符，要求非空连续回文子串的最大数量；即使内容相同，不同起止位置也分别计数。输出最大数量。

## 问题拆分

---

1. 按字符统计出现次数，给每个回文子串的端点归类。
2. 求端点对给出的上界，并构造能使每个上界都达到的排列。

## 部分分（累计 30 分，$|s|\le3$）：枚举不同排列

---

1. 先排序字符串，再用 `next_permutation` 枚举至多 $n!$ 种不同排列，排序花 $O(n\log n)$。
2. 每个排列枚举 $O(n^2)$ 个非空区间，每区间双指针判回文 $O(n)$，计数并更新最大值。

总时间 $O(n\log n+n!n^3)$、额外空间 $O(n)$；$n\le3$ 时可直接完成。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	sort(s.begin(),s.end());
	int n = (int)s.size();
	long long ans = 0;
	do{
		long long count = 0;
		for(int l = 0; l < n; l++){
			for(int r = l; r < n; r++){
				bool same = true;
				int i = l,j = r;
				while(i < j){
					if(s[i] != s[j]) same = false;
					i++;
					j--;
				}
				if(same) count++;
			}
		}
		ans = max(ans,count);
	}while(next_permutation(s.begin(),s.end()));
	cout << ans << '\n';
	return 0;
}
```

## 满分做法：相同字符连续分块

---

长度不超过 $3$ 的累计 30 分可用下方排列枚举；其余 70 分用频次公式。排列枚举在 $n=10^6$ 时无法运行。

1. 扫描 $n$ 个字符统计 26 个频次，$O(n)$ 时间、$O(26)$ 空间。
2. 某字符出现 $c$ 次，它能贡献的单点与同字符端点对至多 $c+\binom c2=c(c+1)/2$；26 类各算一次 $O(26)$。把同字符连续排列，块内任一端点对之间全相同，全部达到上界。

总时间 $O(n+26)$、空间 $O(26)$；答案最大约 $n(n+1)/2$，须用 `long long`。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	long long cnt[26] = {};
	for(int i = 0; i < (int)s.size(); i++){
		cnt[s[i] - 'a']++;
	}
	long long ans = 0;
	for(int i = 0; i < 26; i++){
		// 将相同字符放在一起，该块贡献 1+2+...+cnt[i]。
		ans += cnt[i] * (cnt[i] + 1) / 2;
	}
	cout << ans << '\n';
	return 0;
}
```

## 知识点总结

---

重排后最大化局部相等结构时，先用相同字符端点对限制答案，再让相同字符相邻以达到上界。
