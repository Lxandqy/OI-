#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
long long a[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int used = min(k,n / 2);
	cout << used << '\n';
	for(int i = 1; i <= n; i++){
		if(i > 1) cout << ' ';
		int pairNumber = (i + 1) / 2;
		if(pairNumber <= used){
			int left = 2 * pairNumber - 1;
			long long sum = a[left] + a[left + 1];
			if(sum % 2 == 0) cout << sum / 2 << "/1";
			else cout << sum << "/2";
		}else{
			cout << a[i] << "/1";
		}
	}
	cout << '\n';
	for(int j = 1; j <= used; j++) cout << 2 * j - 1 << ' ' << 2 * j << '\n';
	return 0;
}
