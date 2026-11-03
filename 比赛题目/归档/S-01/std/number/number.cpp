#include<bits/stdc++.h>
using namespace std;
int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s; cin >> s;
	int sum = 0;
	for(char c : s) sum += c - '0';
	cout << (int)s.size() - 1 + (sum - 1) / 9 << '\n';
	return 0;
}
