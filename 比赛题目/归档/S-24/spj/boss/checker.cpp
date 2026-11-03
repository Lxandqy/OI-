#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int n, m, fa[maxn], dep[maxn], cnt[maxn], day[maxn];
int optimum() {
	for(int i = 2; i <= n; i++) dep[i] = dep[fa[i]] + 1;
	for(int i = 1; i <= n; i++) cnt[dep[i]]++;
	for(int i = n - 1; i >= 0; i--) cnt[i] += cnt[i + 1];
	int ans = 0;
	for(int i = 0; i < n; i++) if(cnt[i]) ans = max(ans, i + (cnt[i] + m - 1) / m);
	return ans;
}
int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	n = inf.readInt(1, 100000); m = inf.readInt(1, n);
	for(int i = 2; i <= n; i++) fa[i] = inf.readInt(1, i - 1);
	int best = optimum(), ans = ouf.readInt(1, n);
	if(ans != best) quitf(_wa, "Days %d, optimum %d", ans, best);
	for(int i = 1; i <= ans; i++) {
		int s = ouf.readInt(1, m);
		for(int j = 1; j <= s; j++) {
			int u = ouf.readInt(1, n);
			if(day[u]) quitf(_wa, "Repeated vertex");
			day[u] = i;
		}
	}
	if(!ouf.seekEof()) quitf(_wa, "Extra output");
	for(int i = 1; i <= n; i++) if(!day[i]) quitf(_wa, "Missing vertex");
	for(int i = 2; i <= n; i++) if(day[fa[i]] >= day[i]) quitf(_wa, "Precedence violated");
	quitf(_ok, "Optimal schedule");
}