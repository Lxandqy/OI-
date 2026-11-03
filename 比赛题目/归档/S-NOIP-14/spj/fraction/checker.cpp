#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
bool read_number(const string &s, long double &x) {
	if(s.size() > 256) return 0;
	static const regex pat(R"([+-]?([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][+-]?[0-9]+)?)");
	if(!regex_match(s, pat)) return 0;
	char *p;
	x = strtold(s.c_str(), &p);
	return *p == 0 && isfinite(x);
}
bool check(long double x, long double y) {
	return fabsl(x - y) <= 0.0001L + 0.0000000001L;
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	long double x, y;
	if(!read_number(ans.readToken(), y) || !ans.seekEof()) quitf(_fail, "Invalid jury answer.");
	if(!read_number(ouf.readToken(), x) || !ouf.seekEof()) quitf(_wa, "Expected one finite real number.");
	if(!check(x, y)) quitf(_wa, "Absolute error exceeds 1e-4.");
	quitf(_ok, "Accepted.");
}
