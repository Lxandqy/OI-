// 粉刷木板，部分分2：统计高度2的连续段。a[i]<=2，保证第5至8点20分，O(n)。
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 5010;
int n,a[N];

int main(){
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int ans = 1;
	for(int i = 1; i <= n; i++){
		if(a[i] == 2 && a[i - 1] != 2) ans++;
	}
	cout << min(n,ans) << '\n';
	return 0;
}
