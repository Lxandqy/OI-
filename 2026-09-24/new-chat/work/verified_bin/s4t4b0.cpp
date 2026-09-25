#include<bits/stdc++.h>
using namespace std;

long long a[3005];
char op[3005];

long long solve(int l,int r){
	if(l == r) return a[l];
	long long best = 0;
	for(int j = l; j < r; j++){
		long long left = solve(l,j);
		long long right = solve(j + 1,r);
		long long value;
		if(op[j] == '+') value = left + right;
		else value = left * right;
		best = max(best,value);
	}
	return best;
}

int main(){
	freopen("eval.in","r",stdin);
	freopen("eval.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	int q = 0;
	long long number = 0;
	for(int i = 0; i < (int)s.size(); i++){
		if(s[i] >= '0' && s[i] <= '9'){
			number = number * 10 + s[i] - '0';
		}else{
			a[++q] = number;
			op[q] = s[i];
			number = 0;
		}
	}
	a[++q] = number;
	cout << solve(1,q) << '\n';
	return 0;
}
