// 灯带，部分分2：检验两种交替串。适用 k=1，保证点5至7共15分。时间和空间 O(n+m)。
#include<bits/stdc++.h>
using namespace std;

int n,m,k;
string s;

int main(){
	freopen("lantern.in","r",stdin);
	freopen("lantern.out","w",stdout);
	cin >> n >> m >> k >> s;
	int ans = 0;
	for(int first = 0; first < 2; first++){
		int x = 0,y = 0;
		bool ok = true;
		for(int i = 0; i < n + m; i++){
			char c = 'R';
			if((i + first) % 2 == 1) c = 'B';
			if(c == 'R') x++;
			else y++;
			if(s[i] != '?' && s[i] != c) ok = false;
		}
		if(ok && x == n && y == m) ans++;
	}
	cout << ans << '\n';
	return 0;
}
