#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
struct node{
	int l,r;
	long long w;
}a[N];
int n,k,p[N];
long long b[N],c[N],mx[N * 4],tag[N * 4];
bool cmp(node x,node y){
	return x.r < y.r;
}
void add(int x,int l,int r,int ql,int qr,long long v){
	if(ql <= l && r <= qr){
		mx[x] += v;
		tag[x] += v;
		return;
	}
	int mid = (l + r) / 2;
	if(ql <= mid) add(x * 2,l,mid,ql,qr,v);
	if(qr > mid) add(x * 2 + 1,mid + 1,r,ql,qr,v);
	mx[x] = max(mx[x * 2],mx[x * 2 + 1]) + tag[x];
}
int main(){
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i].l >> a[i].r >> a[i].w;
		p[i] = a[i].l;
	}
	sort(p + 1,p + n + 1);
	k = unique(p + 1,p + n + 1) - p - 1;
	for(int i = 1; i <= k + 1; i++) b[i] = 0;
	for(int i = 1; i <= n; i++){
		a[i].l = lower_bound(p + 1,p + k + 1,a[i].l) - p;
		a[i].r = upper_bound(p + 1,p + k + 1,a[i].r) - p - 1;
		b[a[i].l] += a[i].w;
		b[a[i].r + 1] -= a[i].w;
	}
	c[0] = 0;
	for(int i = 1; i <= k; i++) c[i] = c[i - 1] + b[i];
	sort(a + 1,a + n + 1,cmp);
	for(int i = 1; i <= 4 * k; i++){
		mx[i] = 0;
		tag[i] = 0;
	}
	long long ans = 0;
	int j = 1;
	for(int i = 1; i <= k; i++){
		while(j <= n && a[j].r < i){
			add(1,1,k,a[j].l,a[j].r,a[j].w);
			j++;
		}
		ans = max(ans,c[i] + mx[1]);
	}
	cout << ans << '\n';
	return 0;
}
