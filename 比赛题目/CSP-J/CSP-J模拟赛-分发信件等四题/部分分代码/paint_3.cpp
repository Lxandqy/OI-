// 粉刷木板，部分分3：枚举最高横刷高度。高度非递减，保证第9至12点20分，O(n)。
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
	int ans = n;
	for(int i = 1; i <= n; i++) ans = min(ans,a[i] + n - i);
	cout << ans << '\n';
	return 0;
}
