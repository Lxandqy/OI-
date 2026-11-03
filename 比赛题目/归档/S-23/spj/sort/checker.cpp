#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
bool check(istream &in, istream &out, string &message) {
	int t; in >> t;
	while(t--) {
		int n; in >> n;
		vector<int> a(n + 1), b(n + 1), c;
		for(int i = 1; i <= n; i++) in >> a[i], c.push_back(a[i]);
		for(int i = 1; i <= n; i++) in >> b[i];
		bool possible = 1;
		for(int i = 1; i <= n && possible; i++) {
			int j = 0;
			while(j < (int)c.size() && c[j] != b[i]) j++;
			if(j == (int)c.size()) { possible = 0; break; }
			for(int k = 0; k < j; k++) if(c[k] < b[i]) possible = 0;
			c.erase(c.begin() + j);
		}
		long long flag;
		if(!(out >> flag) || (flag != 0 && flag != -1)) { message = "Expected 0 or -1"; return 0; }
		if(flag == -1) {
			if(possible) { message = "A valid transformation exists"; return 0; }
			continue;
		}
		if(!possible) { message = "Transformation is impossible"; return 0; }
		long long m;
		if(!(out >> m) || m < 0 || m > 1ll * n * n) { message = "Wrong number of operations"; return 0; }
		set<int> bad;
		for(int i = 1; i < n; i++) if(a[i] > a[i + 1]) bad.insert(i);
		while(m--) {
			long long l, r;
			if(!(out >> l >> r) || l < 1 || l > r || r > n) { message = "Invalid interval"; return 0; }
			while(1) {
				auto it = bad.lower_bound(l);
				if(it == bad.end() || *it >= r) break;
				int i = *it;
				swap(a[i], a[i + 1]);
				for(int j = max(1, i - 1); j <= min(n - 1, i + 1); j++) {
					if(a[j] > a[j + 1]) bad.insert(j);
					else bad.erase(j);
				}
			}
		}
		if(a != b) { message = "Final sequence differs from b"; return 0; }
	}
	string extra;
	if(out >> extra) { message = "Extra output"; return 0; }
	message = "Valid transformations";
	return 1;
}
int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	ifstream in(argv[1]), out(argv[2]);
	string message;
	if(!check(in, out, message)) quitf(_wa, "%s", message.c_str());
	while(!ouf.eof()) ouf.skipChar();
	quitf(_ok, "%s", message.c_str());
}