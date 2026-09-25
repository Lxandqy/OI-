#include<bits/stdc++.h>
using namespace std;

int n,original[1000010],ans = 1000000000;

void dfs(int i,int first,int last,int cost){
	if(cost >= ans) return;
	if(i == n){
		if(last != first) ans = min(ans,cost);
		return;
	}
	for(int c = 0; c < 3; c++){
		if(c == last) continue;
		int add = (c - original[i] + 3) % 3;
		dfs(i + 1,first,c,cost + add);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> n >> s;
	for(int i = 0; i < n; i++){
		if(s[i] == 'r') original[i] = 0;
		if(s[i] == 'g') original[i] = 1;
		if(s[i] == 'b') original[i] = 2;
	}
	for(int first = 0; first < 3; first++){
		int cost = (first - original[0] + 3) % 3;
		dfs(1,first,first,cost);
	}
	cout << ans << '\n';
	return 0;
}
