#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, a[105];
string reason;
ofstream score, report;
int finish(bool ok, const string &s, const char *full) {
	score << (ok ? full : "0") << '\n';
	report << s << '\n';
	return 0;
}
bool read_plan(ifstream &s, ll &cost) {
	if(!(s >> cost) || cost < 0 || cost > 100000000000ll) {
		reason = "Missing or invalid cost.";
		return 0;
	}
	vector<int> p(n), stk;
	bool vis[105] = {};
	for(int i = 0; i < n; i++) {
		ll x;
		if(!(s >> x) || x < 1 || x > n || vis[x]) {
			reason = "Missing, repeated or invalid index.";
			return 0;
		}
		p[i] = x, vis[x] = 1;
	}
	int now = 1;
	ll sum = 0;
	for(int i = 0; i < n; i++) {
		while(now <= p[i]) stk.push_back(now++);
		if(stk.empty() || stk.back() != p[i]) {
			reason = "Unreachable stack order.";
			return 0;
		}
		stk.pop_back();
		if(i) sum += abs(a[p[i]] - a[p[i - 1]]);
	}
	if(sum != cost) {
		reason = "The reported cost is incorrect.";
		return 0;
	}
	return 1;
}
int main(int argc, char *argv[]) {
	if(argc != 7) return 1;
	score.open(argv[5]), report.open(argv[6]);
	if(!score || !report) return 1;
	ifstream in(argv[1]), out(argv[2]), ans(argv[3]);
	if(!in || !out || !ans) return 1;
	int t;
	if(!(in >> t) || t < 1 || t > 20) return 1;
	while(t--) {
		if(!(in >> n) || n < 1 || n > 100) return 1;
		for(int i = 1; i <= n; i++)
			if(!(in >> a[i]) || a[i] < 1 || a[i] > 1000000000) return 1;
		ll standard, got;
		if(!read_plan(ans, standard)) return 1;
		if(!read_plan(out, got)) return finish(0, reason, argv[4]);
		if(got < standard) return 1;
		if(got > standard) return finish(0, "The arrangement is not optimal.", argv[4]);
	}
	string extra;
	if(ans >> extra) return 1;
	if(out >> extra) return finish(0, "Extra output.", argv[4]);
	return finish(1, "Optimal stack arrangement.", argv[4]);
}
