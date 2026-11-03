// 双点巡查，部分分 3：区间两两不交，取最大的两份权值。
// 覆盖第 9 至 10 点（10 分）。时间 O(n)，额外空间 O(1)。
#include<cstdio>
#include<iostream>
using namespace std;
int main(){
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	long long first = 0,second = 0;
	for(int i = 1; i <= n; i++){
		int l,r;
		long long w;
		cin >> l >> r >> w;
		if(w >= first){
			second = first;
			first = w;
		}else if(w > second){
			second = w;
		}
	}
	cout << first + second << '\n';
	return 0;
}
