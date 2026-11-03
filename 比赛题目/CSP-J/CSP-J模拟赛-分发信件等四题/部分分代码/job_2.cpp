// job, partial 2: sort and take the largest k values.
// Condition: m = 1. Points 5-6, 10 points. O(n log n) time, O(n) space.
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int N = 5005;
int n,m,k;
long long a[N],ans;

int main(){
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1,a + n + 1);
	for(int i = n - k + 1; i <= n; i++) ans += a[i];
	cout << ans << '\n';
	return 0;
}
