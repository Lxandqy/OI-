#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while(T--){
		long long L,R;
		cin >> L >> R;
		long long power = 1;
		int len = 1;
		while(L * power * 2 < R){
			power *= 2;
			len++;
		}
		long long count = max(0LL,R / power - L + 1);
		if(len >= 2){
			long long limit = R / (power / 2 * 3);
			count += (len - 1) * max(0LL,limit - L + 1);
		}
		cout << len << ' ' << count << '\n';
	}
	return 0;
}
