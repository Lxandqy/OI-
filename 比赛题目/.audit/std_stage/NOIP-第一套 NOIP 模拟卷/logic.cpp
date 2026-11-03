#include<bits/stdc++.h>
using namespace std;

const int N = 55;
int n,k,r,a[N][N],rhs[N];
long long b[N];

// b[i] 是第一个 1 在第 i 列的差分基向量。
void add(long long x){
	for(int i = 1; i <= n; i++){
		if(((x >> (i - 1)) & 1) == 0) continue;
		if(b[i] != 0){
			x ^= b[i];
		}else{
			b[i] = x;
			r++;
			return;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	long long first = 0;
	for(int i = 1; i <= k; i++){
		string s;
		cin >> s;
		long long x = 0;
		for(int j = 1; j <= n; j++){
			if(s[j - 1] == '1') x |= 1LL << (j - 1);
		}
		if(i == 1) first = x;
		add(x ^ first);
	}
	if((1LL << r) != k){
		cout << -1 << '\n';
		return 0;
	}

	// 消掉其他基向量中的主元，使每个主元列只有一个 1。
	for(int i = n; i >= 1; i--){
		if(b[i] == 0) continue;
		for(int j = 1; j < i; j++){
			if((b[j] >> (i - 1)) & 1) b[j] ^= b[i];
		}
	}

	int q = 0;
	for(int j = 1; j <= n; j++){
		if(b[j] != 0) continue;
		q++;
		a[q][j] = 1;
		for(int i = 1; i <= n; i++){
			if(b[i] != 0) a[q][i] = (b[i] >> (j - 1)) & 1;
		}
		// 右端由第一组赋值确定。
		for(int i = 1; i <= n; i++){
			if(a[q][i] == 1 && ((first >> (i - 1)) & 1)) rhs[q] ^= 1;
		}
	}

	// 对构造出的方程组再消元，满足题目要求的输出顺序。
	int row = 0;
	for(int j = 1; j <= n; j++){
		int p = row + 1;
		while(p <= q && a[p][j] == 0) p++;
		if(p > q) continue;
		row++;
		for(int t = 1; t <= n; t++) swap(a[row][t],a[p][t]);
		swap(rhs[row],rhs[p]);
		for(int i = 1; i <= q; i++){
			if(i == row || a[i][j] == 0) continue;
			for(int t = 1; t <= n; t++) a[i][t] ^= a[row][t];
			rhs[i] ^= rhs[row];
		}
	}

	cout << q << '\n';
	for(int i = 1; i <= q; i++){
		for(int j = 1; j <= n; j++) cout << a[i][j];
		cout << ' ' << rhs[i] << '\n';
	}
	return 0;
}
