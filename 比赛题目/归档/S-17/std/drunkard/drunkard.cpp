#include<bits/stdc++.h>
using namespace std;
int n, m, s = -1, up = 2e9, mx[2] = {-1, -1};
bool ok = 1;
set<pair<int, int>> st;
int get(int x) {
	return max(x, mx[x ^ 1] + 1);
}
void insert(int p, int q) {
	if(!ok) return;
	auto it = st.insert({q, p}).first;
	if(it != st.begin()) {
		auto pre = prev(it);
		if(abs(p - pre->second) > q - pre->first) ok = 0;
	}
	if(next(it) != st.end()) {
		auto nxt = next(it);
		if(abs(p - nxt->second) > nxt->first - q) ok = 0;
	}
	if(p == 1) mx[q & 1] = max(mx[q & 1], q);
	else {
		int t = (q - p + 1) & 1;
		if(s != -1 && s != t) ok = 0;
		s = t, up = min(up, q - p + 1);
	}
	if(s != -1 && get(s) > up) ok = 0;
}
int main() {
	freopen("drunkard.in", "r", stdin);
	freopen("drunkard.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	while(m--) {
		string op; cin >> op;
		if(op == "clue") {
			int p, q; cin >> p >> q;
			insert(p, q);
		}
		else if(!ok) cout << "bad\n";
		else if(op == "min") cout << (s == -1 ? min(get(0), get(1)) : get(s)) << '\n';
		else if(s == -1) cout << "inf\n";
		else cout << up << '\n';
	}
	return 0;
}
