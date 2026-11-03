#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	long long cnt[26] = {};
	for(int i = 0; i < (int)s.size(); i++){
		cnt[s[i] - 'a']++;
	}
	long long ans = 0;
	for(int i = 0; i < 26; i++){
		// 将相同字符放在一起，该块贡献 1+2+...+cnt[i]。
		ans += cnt[i] * (cnt[i] + 1) / 2;
	}
	cout << ans << '\n';
	return 0;
}
