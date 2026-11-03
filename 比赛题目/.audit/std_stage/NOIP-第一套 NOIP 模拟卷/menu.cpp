#include<bits/stdc++.h>
using namespace std;

const int N = (1 << 22) + 10;
int n,m,c,f[N],sum[N],ans;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> c;
	for(int i = 1; i <= m; i++){
		int x;
		cin >> x;
		sum[1 << (x - 1)]++;
	}
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		int x = 0;
		for(int j = 0; j < c; j++){
			if(s[j] == '1') x |= 1 << j;
		}
		f[x]++;
	}
	int all = (1 << c) - 1;
	for(int i = 0; i < c; i++){
		for(int s = 0; s <= all; s++){
			if(s & (1 << i)){
				f[s] += f[s ^ (1 << i)];
				sum[s] += sum[s ^ (1 << i)];
			}
		}
	}
	for(int s = 1; s <= all; s++){
		if(sum[s] == 0) continue;
		int cnt = n - f[all ^ s];
		if(cnt == 0){
			cout << -1 << '\n';
			return 0;
		}
		ans = max(ans,(sum[s] + cnt - 1) / cnt);
	}
	cout << ans << '\n';
	return 0;
}
