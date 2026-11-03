#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 环线协作，部分分 2：枚举时限，断环后顺次检查。
// n,m <= 2000 或 n = 2 时，保证第 1 至 10 点，共 50 分。
// 时间 O(m + nm)，空间 O(n)；n = 2 时总时间 O(m)。
int n,m,p;
vector<int> c;

bool check(int t){
	int x = 0;
	for(int j = 1; j <= n; j++){
		int i = (p + j - 1) % n + 1;
		x = max(0,c[i] + 2 * x - t);
		if(x > c[i]) return false;
	}
	return true;
}

int main(){
	freopen("relay.in","r",stdin);
	freopen("relay.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	c.resize(n + 1);
	for(int j = 1; j <= m; j++){
		int x;
		cin >> x;
		c[x]++;
	}
	p = 1;
	while(c[p] > 0) p++;
	for(int t = 1; t <= m; t++){
		if(check(t)){
			cout << t << '\n';
			break;
		}
	}
	return 0;
}
