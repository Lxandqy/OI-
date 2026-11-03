// 安全密码（password），部分分第 1 项。
// 算法: 枚举允许密码并扫描匹配。
// 适用条件: m<=3 and total n<=1000; or singleton ranges
// 保证点号: 1,2,3,4,20; 保证分: 25。
// 时间复杂度: O(P*(n+m))。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

string s;
int m;

bool isSubsequence(const string &p){
	int j = 0;
	for(int i = 0; i < (int)s.size() && j < m; i++){
		if(s[i] == p[j]) j++;
	}
	return j == m;
}

bool dfs(int pos,string &l,string &r,string &p){
	if(pos == m) return !isSubsequence(p);
	for(char c = l[pos]; c <= r[pos]; c++){
		p.push_back(c);
		if(dfs(pos + 1,l,r,p)) return true;
		p.pop_back();
	}
	return false;
}

int main(){
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	int t;
	cin >> t;
	while(t--){
		string l,r,p;
		cin >> s >> m >> l >> r;
		cout << (dfs(0,l,r,p) ? "YES" : "NO") << '\n';
	}
	return 0;
}
