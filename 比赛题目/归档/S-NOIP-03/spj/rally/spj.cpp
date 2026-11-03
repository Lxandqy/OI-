#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 100005;
int n, m, k, u[maxn], v[maxn], d[maxn];
bool vis[maxn];
ofstream score, report;

int finish(bool ok, const string &s, const char *full) {
	score << (ok ? full : "0") << '\n';
	report << s << '\n';
	return 0;
}

int main(int argc, char *argv[]) {
	if(argc != 7) return 1;
	score.open(argv[5]);
	report.open(argv[6]);
	if(!score || !report) return 1;
	ifstream in(argv[1]), out(argv[2]), ans(argv[3]);
	if(!in || !out || !ans) {
		finish(false, "Cannot open judging files.", argv[4]);
		return 1;
	}
	if(!(in >> n >> m >> k) || n < 1 || n >= maxn || m < 0 || m >= maxn || k < 1 || k > n) return 1;
	for(int i = 1; i <= m; i++) {
		if(!(in >> u[i] >> v[i]) || u[i] < 1 || u[i] > n || v[i] < 1 || v[i] > n) return 1;
	}
	ll type, standard, s;
	string extra;
	if(!(ans >> standard)) return 1;
	if(!(out >> type)) return finish(false, "Missing or invalid answer type.", argv[4]);
	if(type == -1) {
		if(out >> extra) return finish(false, "Extra output after -1.", argv[4]);
		return finish(standard == -1, standard == -1 ? "Accepted." : "A valid team exists.", argv[4]);
	}
	if(type == 1) {
		if(!(out >> s) || s < 1 || s > n) return finish(false, "Invalid team size.", argv[4]);
	}
	else if(type == 2) s = k;
	else return finish(false, "Unknown answer type.", argv[4]);
	for(int i = 1; i <= s; i++) {
		ll x;
		if(!(out >> x) || x < 1 || x > n) return finish(false, "Missing or out-of-range member.", argv[4]);
		if(vis[x]) return finish(false, "Repeated member.", argv[4]);
		vis[x] = true;
	}
	if(out >> extra) return finish(false, "Extra output.", argv[4]);
	ll cnt = 0;
	for(int i = 1; i <= m; i++) {
		if(vis[u[i]] && vis[v[i]]) {
			d[u[i]]++;
			d[v[i]]++;
			cnt++;
		}
	}
	if(type == 1) {
		for(int i = 1; i <= n; i++) {
			if(vis[i] && d[i] < k) return finish(false, "Too few partners inside the team.", argv[4]);
		}
	}
	else if(cnt != s * (s - 1) / 2) return finish(false, "Some two members have not teamed up.", argv[4]);
	return finish(true, "Accepted.", argv[4]);
}
