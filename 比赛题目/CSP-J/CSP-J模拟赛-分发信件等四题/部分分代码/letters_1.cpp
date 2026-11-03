// letters, partial 1: subtract each dormitory size from the address.
// n,m <= 2000; points 1-6, guaranteed 30 points.
// O(nm) time, O(n) space.
#include<iostream>
#include<cstdio>
using namespace std;

const int N = 2e5 + 10;
int n,m;
long long a[N];

int main(){
	freopen("letters.in","r",stdin);
	freopen("letters.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++){
		long long x;
		cin >> x;
		int p = 1;
		while(x > a[p]){
			x -= a[p];
			p++;
		}
		cout << p << ' ' << x << '\n';
	}
	return 0;
}
