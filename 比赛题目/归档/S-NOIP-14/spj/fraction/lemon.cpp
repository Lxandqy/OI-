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
	if(argc != 7) return 2;
	ifstream user(argv[2]), answer(argv[3]);
	ofstream score(argv[5]), report(argv[6]);
	string a, b, extra;
	long double x, y;
	if(!(answer >> b) || !read_number(b, y) || (answer >> extra)) {
		score << 0;
		report << "Invalid jury answer.";
		return 2;
	}
	bool ok = (user >> a) && read_number(a, x) && !(user >> extra) && check(x, y);
	score << (ok ? argv[4] : "0");
	report << (ok ? "Accepted." : "Expected one finite real number with absolute error at most 1e-4.");
	return 0;
}
