#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) ((x) & (-x))
using namespace std;
const int maxn = 100010;
int n, a[maxn], pos[maxn], tree[maxn];
ll B;
void add(int x, int v) {
	for(; x <= n; x += lowbit(x)) tree[x] += v;
}
int query(int x) {
	int ans = 0;
	for(; x; x -= lowbit(x)) ans += tree[x];
	return ans;
}
bool check(int k) {
	priority_queue<int> q;
	for(int i = 1; i <= n; i++) tree[i] = lowbit(i);
	int now = n;
	ll sum = 0;
	for(int i = n; i; i--) {
		while(now && now + k - 1 >= i) q.push(pos[now--]);
		int x = q.top();
		q.pop();
		sum += i - query(x);
		if(sum > B) return false;
		add(x, -1);
	}
	return true;
}
int main() {
	freopen("buffer.in", "r", stdin);
	freopen("buffer.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> B;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		pos[a[i]] = i;
	}
	int l = 1, r = n;
	while(l < r) {
		int mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << '\n';
	return 0;
}
