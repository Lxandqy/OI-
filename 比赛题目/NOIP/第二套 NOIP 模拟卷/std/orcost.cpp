#include<bits/stdc++.h>
using namespace std;

const int N = 50000 + 10;
const int Q = 100000 + 10;
const int E = N * 62;
int n,q,a[N],id[N],pre[N],nxt[N],head[N],to[E],ne[E],cnt;
int qhead[N],ql[Q],qn[Q],active;
long long bit1[N],bit2[N],bit3[N],bit4[N],total1,total2,ans[Q];
map<int,int> seg;

bool cmp(int x,int y){
	if(a[x] != a[y]) return a[x] < a[y];
	return x < y;
}

void add_edge(int x,int y){
	if(x > y) swap(x,y);
	to[++cnt] = x;
	ne[cnt] = head[y];
	head[y] = cnt;
}

void add(int p,long long x,long long y,long long z,long long w){
	for(int i = p; i <= n; i += i & -i){
		bit1[i] += x;
		bit2[i] += y;
		bit3[i] += z;
		bit4[i] += w;
	}
}

void change_sum(int l,int r,long long v,int t){
	long long w = v * (t - 1);
	add(l,v,v * (l - 1),w,w * (l - 1));
	add(r + 1,-v,-v * r,-w,-w * r);
	total1 += v * (r - l + 1);
	total2 += w * (r - l + 1);
}

void query(int p,long long &x,long long &y){
	long long s1 = 0,s2 = 0,s3 = 0,s4 = 0;
	for(int i = p; i > 0; i -= i & -i){
		s1 += bit1[i];
		s2 += bit2[i];
		s3 += bit3[i];
		s4 += bit4[i];
	}
	x = s1 * p - s2;
	y = s3 * p - s4;
}

void change(int p,int v,int t){
	if(p == 0) return;
	map<int,int>::iterator right = seg.upper_bound(p);
	map<int,int>::iterator it = right;
	it--;
	if(it->second <= v) return;
	if(p < active && (right == seg.end() || right->first != p + 1)){
		seg[p + 1] = it->second;
	}
	int r = p;
	while(true){
		int l = it->first;
		change_sum(l,r,(long long)v - it->second,t);
		bool first = it == seg.begin();
		map<int,int>::iterator last = it;
		if(!first) last--;
		seg.erase(it);
		if(first){
			seg[l] = v;
			break;
		}
		if(last->second <= v){
			if(last->second < v) seg[l] = v;
			break;
		}
		r = l - 1;
		it = last;
	}
}

int main(){
	freopen("orcost.in","r",stdin);
	freopen("orcost.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		id[i] = i;
		pre[i] = i - 1;
		nxt[i] = i + 1;
	}
	for(int i = 1; i <= q; i++){
		int r;
		cin >> ql[i] >> r;
		qn[i] = qhead[r];
		qhead[r] = i;
	}
	sort(id + 1,id + n + 1,cmp);
	for(int i = n; i >= 1; i--){
		int x = id[i],y = pre[x];
		for(int j = 1; j <= 31 && y != 0; j++){
			add_edge(x,y);
			y = pre[y];
		}
		y = nxt[x];
		for(int j = 1; j <= 31 && y <= n; j++){
			add_edge(x,y);
			y = nxt[y];
		}
		nxt[pre[x]] = nxt[x];
		pre[nxt[x]] = pre[x];
	}
	for(int r = 2; r <= n; r++){
		int v = a[r - 1] | a[r];
		change(r - 2,v,r);
		active = r - 1;
		if(seg.empty() || seg.rbegin()->second != v) seg[active] = v;
		change_sum(active,active,v,r);
		for(int i = head[r]; i != 0; i = ne[i]){
			change(to[i],a[to[i]] | a[r],r);
		}
		for(int i = qhead[r]; i != 0; i = qn[i]){
			long long x,y;
			query(ql[i] - 1,x,y);
			ans[i] = r * (total1 - x) - (total2 - y);
		}
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
