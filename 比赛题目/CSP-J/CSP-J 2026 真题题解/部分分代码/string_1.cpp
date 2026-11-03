// 回文串，部分分 1：至多两段时直接计算。
// 适用 n <= 2，保证覆盖测试点 1 至 4，共 16 分。
// 时间 O(n)，额外空间 O(1)。
#include<bits/stdc++.h>
using namespace std;

int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int n;
	long long a,b = 0;
	char c,d = 'a';
	cin >> n >> a >> c;
	for(int i = 2; i <= n; i++){
		cin >> b >> d;
	}
	if(n == 1 || c == d){
		cout << 0 << '\n';
	}else{
		cout << min(a,b) << '\n';
	}
	return 0;
}
