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
	if(argc != 7) return 1;
	ifstream in(argv[1]), out(argv[2]);
	double full = atof(argv[4]); ofstream score(argv[5]), message(argv[6]);
	auto finish = [&](bool ok, string msg) { score << (ok ? full : 0); message << msg; };
	in >> n >> m;
	for(int i = 2; i <= n; i++) in >> fa[i];
	int best = optimum(); long long ans;
	if(!(out >> ans) || ans != best) { finish(0, "Wrong minimum days"); return 0; }
	for(int i = 1; i <= ans; i++) {
		long long s;
		if(!(out >> s) || s < 1 || s > m) { finish(0, "Wrong daily count"); return 0; }
		for(int j = 1; j <= s; j++) {
			long long u;
			if(!(out >> u) || u < 1 || u > n || day[u]) { finish(0, "Wrong or repeated vertex"); return 0; }
			day[u] = i;
		}
	}
	string extra;
	if(out >> extra) { finish(0, "Extra output"); return 0; }
	for(int i = 1; i <= n; i++) if(!day[i]) { finish(0, "Missing vertex"); return 0; }
	for(int i = 2; i <= n; i++) if(day[fa[i]] >= day[i]) { finish(0, "Precedence violated"); return 0; }
	finish(1, "Optimal schedule");
}