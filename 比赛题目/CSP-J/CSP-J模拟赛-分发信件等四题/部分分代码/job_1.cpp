// job, partial 1: enumerate all ordered non-overlapping segments.
// Condition: n <= 20, or k = 1. Points 1-4 and 7-8, 30 points guaranteed.
// O(n * 2^n) time, O(n) space; O(n) time when k = 1.
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int N = 5005;
int n,m,k;
long long s[N],ans;

void dfs(int x,int c,long long sum){
	if(c == k){
		ans = max(ans,sum);
		return;
	}
	for(int i = x; i + (k - c) * m - 1 <= n; i++){
		dfs(i + m,c + 1,sum + s[i + m - 1] - s[i - 1]);
	}
}

int main(){
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		s[i] = s[i - 1] + x;
	}
	dfs(1,0,0);
	cout << ans << '\n';
	return 0;
}
