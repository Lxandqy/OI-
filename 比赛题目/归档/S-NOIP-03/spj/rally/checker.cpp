#include "testlib.h"
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 1e5 + 10;
int n, m, k, u[maxn], v[maxn], d[maxn];
bool vis[maxn];

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	n = inf.readInt(1, 100000, "n");
	m = inf.readInt(0, 100000, "m");
	k = inf.readInt(1, n, "k");
	for(int i = 1; i <= m; i++) {
		u[i] = inf.readInt(1, n, "u");
		v[i] = inf.readInt(1, n, "v");
	}
	int standard = ans.readInt(-1, 2, "answer type");
	ensuref(standard == -1 || standard == 1 || standard == 2, "Invalid jury answer type.");
	if(ouf.seekEof()) quitf(_wa, "Missing answer.");
	int type = ouf.readInt(-1, 2, "answer type");
	if(type == -1) {
		if(!ouf.seekEof()) quitf(_wa, "Extra output after -1.");
		if(standard != -1) quitf(_wa, "A valid team exists.");
		quitf(_ok, "No valid team exists.");
	}
	int s;
	if(type == 1) s = ouf.readInt(1, n, "team size");
	else if(type == 2) s = k;
	else quitf(_wa, "Unknown answer type.");
	for(int i = 1; i <= s; i++) {
		int x = ouf.readInt(1, n, "member");
		if(vis[x]) quitf(_wa, "Repeated member %d.", x);
		vis[x] = 1;
	}
	if(!ouf.seekEof()) quitf(_wa, "Extra output.");
	ll cnt = 0;
	for(int i = 1; i <= m; i++) {
		if(vis[u[i]] && vis[v[i]]) {
			d[u[i]]++, d[v[i]]++;
			cnt++;
		}
	}
	if(type == 1) {
		for(int i = 1; i <= n; i++) {
			if(vis[i] && d[i] < k) quitf(_wa, "Member %d has too few partners in the team.", i);
		}
	}
	else if(cnt != 1ll * s * (s - 1) / 2) quitf(_wa, "The selected members do not form a clique.");
	// 有解方案直接按题意检查，只有无解输出需要参考标准答案。
	if(standard == -1) quitf(_fail, "A valid team was found, but the jury answer says impossible.");
	quitf(_ok, "Valid team.");
}
