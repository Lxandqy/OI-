#include "testlib.h"
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, a[105];
ll read_plan(InStream &s, bool jury) {
	ll cost = s.readLong(0, 100000000000ll, "cost");
	vector<int> p(n), stk;
	bool vis[105] = {};
	for(int i = 0; i < n; i++) {
		p[i] = s.readInt(1, n, "index");
		if(vis[p[i]]) quitf(jury ? _fail : _wa, "Repeated index.");
		vis[p[i]] = 1;
	}
	int now = 1;
	ll sum = 0;
	for(int i = 0; i < n; i++) {
		while(now <= p[i]) stk.push_back(now++);
		if(stk.empty() || stk.back() != p[i]) quitf(jury ? _fail : _wa, "Unreachable stack order.");
		stk.pop_back();
		if(i) sum += abs(a[p[i]] - a[p[i - 1]]);
	}
	if(sum != cost) quitf(jury ? _fail : _wa, "The reported cost is incorrect.");
	return cost;
}
int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	int t = inf.readInt(1, 20, "T");
	while(t--) {
		n = inf.readInt(1, 100, "n");
		for(int i = 1; i <= n; i++) a[i] = inf.readInt(1, 1000000000, "height");
		ll standard = read_plan(ans, 1), got = read_plan(ouf, 0);
		if(got < standard) quitf(_fail, "A better valid arrangement was found.");
		if(got > standard) quitf(_wa, "The arrangement is not optimal.");
	}
	if(!ans.seekEof()) quitf(_fail, "Extra jury output.");
	if(!ouf.seekEof()) quitf(_wa, "Extra output.");
	quitf(_ok, "Optimal stack arrangement.");
}
