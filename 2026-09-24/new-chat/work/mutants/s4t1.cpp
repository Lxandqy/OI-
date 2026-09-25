#include<bits/stdc++.h>
using namespace std;

const int maxv = 100000 + 10;
int cnt[maxv];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	int best = 0;
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		cnt[x]++;
		if(cnt[x] >= 3){
			best = max(best, x);
		}
	}

	cout << 1LL * best * n << '\n';
	return 0;
}
