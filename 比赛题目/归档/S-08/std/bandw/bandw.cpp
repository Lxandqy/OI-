#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll p[20];
int main() {
	freopen("bandw.in", "r", stdin);
	freopen("bandw.out", "w", stdout);
	ll n; cin >> n;
	p[0] = 1;
	for(int i = 1; i <= 18; i++) p[i] = p[i - 1] * 5;
	int len = 2;
	while(n > 9 * p[len - 1]) n -= 9 * p[len - 1], len++;
	n--;
	int x = n / p[len - 1] + 1;
	cout << x;
	n %= p[len - 1];
	for(int i = len - 2; i >= 0; i--) {
		x = 2 * (n / p[i]) + (1 - x % 2);
		cout << x; n %= p[i];
	}
	cout << '\n';
	return 0;
}
