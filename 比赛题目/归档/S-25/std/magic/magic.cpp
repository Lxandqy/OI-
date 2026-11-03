#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 4e5 + 10;
struct Trie {
	int tree[maxn][26], cnt[26], tot;
	void insert(string s) {
		int u = 0;
		for(char c : s) {
			int val = c - 'a';
			if(!tree[u][val]) tree[u][val] = ++tot, cnt[val]++;
			u = tree[u][val];
		}
	}
}trie[2];
bool last[26], single[26];
int main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n; cin >> n;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s;
		last[s.back() - 'a'] = 1;
		if(s.size() == 1) single[s[0] - 'a'] = 1;
		trie[0].insert(s);
		reverse(s.begin(), s.end()); trie[1].insert(s);
	}
	ll ans = 0;
	for(int i = 0; i < 26; i++) ans += single[i];
	for(int u = 1; u <= trie[0].tot; u++)
		for(int c = 0; c < 26; c++) {
			if(!trie[0].tree[u][c]) ans += trie[1].cnt[c];
			else ans += last[c];
		}
	cout << ans << '\n';
	return 0;
}
