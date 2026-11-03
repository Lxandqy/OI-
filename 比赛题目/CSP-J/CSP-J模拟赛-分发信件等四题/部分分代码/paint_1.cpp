// 粉刷木板，部分分1：枚举竖刷集合。n<=18，保证第1至4点20分，O(n*2^n)。
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 5010;
int n,a[N],v[N],ans;

void dfs(int x,int cnt){
	if(cnt >= ans) return;
	if(x > n){
		long long sum = cnt;
		int last = 0,mn = 1000000000;
		for(int i = 1; i <= n; i++){
			mn = min(mn,a[i]);
			if(v[i] == 0){
				if(last == 0) sum += a[i];
				else sum += a[i] - mn;
				last = i;
				mn = a[i];
			}
		}
		if(sum < ans) ans = sum;
		return;
	}
	v[x] = 0;
	dfs(x + 1,cnt);
	v[x] = 1;
	dfs(x + 1,cnt + 1);
}

int main(){
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	ans = n;
	dfs(1,0);
	cout << ans << '\n';
	return 0;
}
