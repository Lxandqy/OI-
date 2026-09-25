# T1 上下五千年

---

## 题意简化

---

输入合法公历日期 $y,m,d$，年份 $2000\le y\le7000$。把年、月、日的十进制写法直接拼接，不补前导零；若拼接串回文，则称为回文时间。求严格晚于输入日期的第一个回文时间，输出其年月日。

## 问题拆分

---

1. 按大小月及闰年规则推进到下一合法日期。
2. 拼接该日的年、月、日并检查是否回文；若不是则回到步骤 1。

## 满分做法：逐日枚举合法日期

---

原有年份上界 $2200$、$4000$、$7000$ 的累计 30/60/100 分均使用这份程序；闰年按能被 $400$ 整除或能被 $4$ 整除且不能被 $100$ 整除判断。

1. 用 $O(1)$ 的闰年和每月天数判断推进一天；一定先推进，排除输入当天。
2. 把日期转成至多固定长度的字符串，双指针检查回文，每天 $O(1)$；首次成功即停止。

若距离答案有 $D$ 天，总时间 $O(D)$、额外空间 $O(1)$。按时间递增检查，因此第一次命中就是所求。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool leap(int y){
	return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int days(int y, int m){
	static int d[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(m == 2){
		return d[m] + leap(y);
	}
	return d[m];
}

void nextDay(int &y, int &m, int &d){
	d++;
	if(d > days(y, m)){
		d = 1;
		m++;
	}
	if(m > 12){
		m = 1;
		y++;
	}
}

bool palindromeDate(int y, int m, int d){
	string s = to_string(y) + to_string(m) + to_string(d);
	string t = s;
	reverse(t.begin(), t.end());
	return s == t;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int y, m, d;
	cin >> y >> m >> d;
	do {
		nextDay(y, m, d);
	} while(!palindromeDate(y, m, d));

	cout << y << ' ' << m << ' ' << d << '\n';
	return 0;
}
```

## 知识点总结

---

要求时间上第一个满足性质的对象且合法日期容易推进时，按顺序枚举比枚举任意数字再筛日期更直接。
