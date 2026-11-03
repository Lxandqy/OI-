#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) ((x) & (-x))
using namespace std;
const int maxn = 1e5 + 10;
struct Mo {
	int l, r, id;
}q[maxn];
int n, m, a[maxn], pos[maxn], c[maxn], cnt, top;
ll s[maxn], sum, cur, ans[maxn];
bool cmp(Mo x, Mo y) {
	if(pos[x.l] != pos[y.l]) return pos[x.l] < pos[y.l];
	if(pos[x.l] & 1) return x.r < y.r;
	return x.r > y.r;
}
void modify(int x, int k) {
	for(int i = x; i <= n; i += lowbit(i)) {
		c[i] += k;
		s[i] += 1ll * x * k;
	}
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= lowbit(i)) res += c[i];
	return res;
}
ll query_sum(int x) {
	ll res = 0;
	for(int i = x; i; i -= lowbit(i)) res += s[i];
	return res;
}
int get(int k) {
	int x = 0;
	for(int d = top; d; d >>= 1) {
		int y = x + d;
		if(y <= n && c[y] < k) {
			k -= c[y];
			x = y;
		}
	}
	return x + 1;
}
void add(int i, int op) {
	int x = a[i], k = query(x);
	if(!op) cur += k;
	else cur += cnt - k;
	modify(x, 1);
	cnt++, sum += x;
}
void del(int i, int op) {
	int x = a[i], k = query(x);
	if(!op) cur -= k - 1;
	else cur -= cnt - k;
	modify(x, -1);
	cnt--, sum -= x;
}
ll cal() {
	int k = (cnt + 1) / 2, x = get(k);
	ll res = sum - 2 * query_sum(x) + 1ll * x * (2 * k - cnt);
	return cur + res - 1ll * cnt * cnt / 4;
}
void solve() {
	cin >> n >> m;
	int len = max(1, (int)(n / sqrt(m)));
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		a[x] = i;
		pos[i] = (i - 1) / len;
		c[i] = 0, s[i] = 0;
	}
	for(int i = 1; i <= m; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	sort(q + 1, q + m + 1, cmp);
	top = 1;
	while((top << 1) <= n) top <<= 1;
	cnt = 0, sum = 0, cur = 0;
	int L = 1, R = 0;
	for(int i = 1; i <= m; i++) {
		while(L > q[i].l) add(--L, 0);
		while(R < q[i].r) add(++R, 1);
		while(L < q[i].l) del(L++, 0);
		while(R > q[i].r) del(R--, 1);
		ans[q[i].id] = cal();
	}
	for(int i = 1; i <= m; i++) cout << ans[i] << '\n';
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
