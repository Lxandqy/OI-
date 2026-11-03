#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n,m;
long long s[N];

int main(){
	freopen("letters.in","r",stdin);
	freopen("letters.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		long long x;
		cin >> x;
		s[i] = s[i - 1] + x;
	}
	int p = 1;
	for(int i = 1; i <= m; i++){
		long long x;
		cin >> x;
		while(s[p] < x) p++;
		cout << p << ' ' << x - s[p - 1] << '\n';
	}
	return 0;
}
