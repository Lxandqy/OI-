# T3 文件判定

---

## 题意简化

---

输入 $t\le100$ 组父子关系，每组至多 $10$ 条，关系 `A B` 表示条目 $B$ 是 $A$ 的直接孩子，顺序任意，同名表示同一条目。判断是否恰好是一棵三层目录树：唯一根名为非空字母后接非空数字；根下恰好四个名称互异的纯字母题目条目；每题下恰有一个名为“题名.cpp”的叶条目。大小写敏感，不允许多余条目或关系，每组输出 `yes` 或 `no`。

## 问题拆分

---

1. 确定唯一根，并核查根名称及总关系数。
2. 找到根的四个直接孩子，检查其名称和各自唯一文件名。
3. 确认所有给定关系均已被这八条合法边消耗。

## 满分做法：逐项核对关系

---

公开分档对应：1～2 点同时满足性质 1、2、3；3～4 点满足性质 1、3；5～6 点满足性质 2；7～10 点无额外性质。四档均由本节的 8 条关系完整核验代码处理：性质只预先保证部分合法条件，仍须检查其余条件，因此不另写部分分代码。

1. 每组先要求恰好 $8$ 条关系；在至多 $n$ 个名称中找作为父但不作为子者并验证唯一根及字母数字格式，朴素比较 $O(n^2)$。
2. 扫描关系找根下四个互异纯字母题目名；再分别找它们唯一的 `题名.cpp` 叶子，最多 $O(n^2)$。
3. 八条合法关系已恰好占满输入；再核查没有额外连接或重复，$O(n^2)$。各组独立清理状态。

每组总时间 $O(n^2)$、空间 $O(n)$；$n\le10$，直接检查足够。名称大小写原样比较，不能按路径顺序假设输入已排序。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

string a[11], b[11];
int n;

bool isLetter(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool rootNameOK(const string &s){
	int i = 0;
	while(i < (int)s.size() && isLetter(s[i])){
		i++;
	}
	if(i == 0 || i == (int)s.size()){
		return false;
	}
	while(i < (int)s.size()){
		if(s[i] < '0' || s[i] > '9'){
			return false;
		}
		i++;
	}
	return true;
}

bool check(){
	if(n != 8){
		return false;
	}
	string root = "";
	for(int i = 1; i <= n; i++){
		bool hasParent = false;
		for(int j = 1; j <= n; j++){
			if(a[i] == b[j]){
				hasParent = true;
			}
		}
		if(!hasParent){
			if(root != "" && root != a[i]){
				return false;
			}
			root = a[i];
		}
	}
	if(!rootNameOK(root)){
		return false;
	}
	int tasks = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] != root){
			continue;
		}
		tasks++;
		string task = b[i];
		for(int j = 0; j < (int)task.size(); j++){
			if(!isLetter(task[j])){
				return false;
			}
		}
		int files = 0;
		for(int j = 1; j <= n; j++){
			if(a[j] == task){
				files++;
				if(b[j] != task + ".cpp"){
					return false;
				}
			}
		}
		if(files != 1){
			return false;
		}
	}
	// 四条根边 + 四条代码文件边已经占满全部八条关系。
	return tasks == 4;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i] >> b[i];
		}
		if(check()){
			cout << "yes\n";
		}else{
			cout << "no\n";
		}
	}
	return 0;
}
```

## 知识点总结

---

小规模关系判定题可按必要条件逐层核对，并用总边数与唯一性证明没有遗漏的多余条目。
