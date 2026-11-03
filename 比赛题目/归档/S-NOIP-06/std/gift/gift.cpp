#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
struct Mo {
	int l, r, x, y, id;
}query[maxn];
int n, q, a[maxn], pos[maxn], cnt[maxn], num[maxn];
int pre[maxn], nxt[maxn], ans[maxn], ways[maxn];
ll fac[maxn], inv[maxn];
ll poww(ll a, int b) {
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
void init() {
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	inv[n] = poww(fac[n], mod - 2);
	for(int i = n; i; i--) inv[i - 1] = inv[i] * i % mod;
	nxt[0] = n + 1, pre[n + 1] = 0;
}
ll C(int n, int m) {
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
bool cmp(Mo a, Mo b) {
	if(pos[a.l] != pos[b.l]) return pos[a.l] < pos[b.l];
	return (pos[a.l] & 1) ? a.r < b.r : a.r > b.r;
}
void insert(int x, int l, int r) {
	pre[x] = l, nxt[x] = r;
	nxt[l] = pre[r] = x;
}
void erase(int x) {
	nxt[pre[x]] = nxt[x];
	pre[nxt[x]] = pre[x];
}
void add(int i) {
	int x = cnt[a[i]];
	// 新次数紧接在旧次数后，先插入再删除旧节点。
	if(!num[x + 1]) insert(x + 1, x, nxt[x]);
	num[x + 1]++;
	if(x && !--num[x]) erase(x);
	cnt[a[i]]++;
}
void del(int i) {
	int x = cnt[a[i]];
	if(x > 1 && !num[x - 1]) insert(x - 1, pre[x], x);
	if(x > 1) num[x - 1]++;
	if(!--num[x]) erase(x);
	cnt[a[i]]--;
}
void calc(Mo t) {
	int sum = 0, best = 0;
	ll res = 0;
	for(int b = pre[n + 1]; b; b = pre[b]) {
		sum += num[b];
		int k = min(sum, t.y);
		if(k < t.x) continue;
		int val = b * k;
		if(val > best) best = val, res = 0;
		if(val == best) res = (res + C(sum, k)) % mod;
	}
	ans[t.id] = best ? t.r - t.l + 1 - best : -1;
	ways[t.id] = res;
}
int main() {
	freopen("gift.in", "r", stdin);
	freopen("gift.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> q;
	int sz = sqrt(n);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		pos[i] = (i - 1) / sz;
	}
	for(int i = 1; i <= q; i++) {
		cin >> query[i].l >> query[i].r >> query[i].x >> query[i].y;
		query[i].id = i;
	}
	init();
	sort(query + 1, query + q + 1, cmp);
	int L = 1, R = 0;
	for(int i = 1; i <= q; i++) {
		int l = query[i].l, r = query[i].r;
		while(L > l) add(--L);
		while(R < r) add(++R);
		while(L < l) del(L++);
		while(R > r) del(R--);
		calc(query[i]);
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << ' ' << ways[i] << '\n';
	return 0;
}
