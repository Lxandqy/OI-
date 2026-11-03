#include<bits/stdc++.h>
using namespace std;

const int N = 300000 + 5;
int nxt[10][N];

int main(){
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		string s,l,r;
		int m;
		cin >> s;
		cin >> m;
		cin >> l >> r;
		int n = (int)s.size();
		for(int d = 0; d < 10; d++) nxt[d][n] = n;
		for(int i = n - 1; i >= 0; i--){
			for(int d = 0; d < 10; d++) nxt[d][i] = nxt[d][i + 1];
			nxt[s[i] - '0'][i] = i;
		}
		int cur = -1;
		bool found = false;
		for(int i = 0; i < m && !found; i++){
			int far = -1;
			for(int d = l[i] - '0'; d <= r[i] - '0'; d++){
				int p = nxt[d][cur + 1];
				if(p == n){
					found = true;
					break;
				}
				far = max(far,p);
			}
			cur = far;
		}
		cout << (found ? "YES" : "NO") << '\n';
	}
	return 0;
}
