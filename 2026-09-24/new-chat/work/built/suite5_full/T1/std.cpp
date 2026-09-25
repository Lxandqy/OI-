#include<bits/stdc++.h>
using namespace std;

bool palindromeDate(int y,int m,int d){
	string s = to_string(y) + to_string(m) + to_string(d);
	int l = 0,r = (int)s.size() - 1;
	while(l < r){
		if(s[l] != s[r]) return false;
		l++;
		r--;
	}
	return true;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int y,m,d;
	cin >> y >> m >> d;
	for(int yy = y; ; yy++){
		for(int mm = 1; mm <= 12; mm++){
			for(int dd = 1; dd <= 27; dd++){
				if(yy == y && (mm < m || (mm == m && dd <= d))) continue;
				if(palindromeDate(yy,mm,dd)){
					cout << yy << ' ' << mm << ' ' << dd << '\n';
					return 0;
				}
			}
		}
	}
}
