// letters, partial 2: equal dormitory sizes allow division and remainder.
// Points 1-9, guaranteed 45 points.
// O(n+m) time for equal sizes, otherwise O(nm); O(n) space.
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
	int same = 1;
	for(int i = 2; i <= n; i++){
		if(a[i] != a[1]) same = 0;
	}
	for(int i = 1; i <= m; i++){
		long long x;
		cin >> x;
		if(same){
			cout << (x - 1) / a[1] + 1 << ' ' << (x - 1) % a[1] + 1 << '\n';
		}else{
			int p = 1;
			while(x > a[p]){
				x -= a[p];
				p++;
			}
			cout << p << ' ' << x << '\n';
		}
	}
	return 0;
}
