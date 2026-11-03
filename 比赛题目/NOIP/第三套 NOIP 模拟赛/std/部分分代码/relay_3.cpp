#include<cstdio>
#include<iostream>
using namespace std;

// 环线协作，部分分 3：两个工人时按两种速度分配任务。
// n = 2，因至少一人没有自己的任务，保证第 9 至 10 点，共 10 分。
// 读入共 O(m)，求值 O(1)，空间 O(1)。
int main(){
	freopen("relay.in","r",stdin);
	freopen("relay.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	for(int j = 1; j <= m; j++){
		int x;
		cin >> x;
	}
	cout << (2 * m + 2) / 3 << '\n';
	return 0;
}
