// 双点巡查，部分分 2：扫描右点，普通数组逐格增加已结束区间的权值。
// n <= 8000 或区间两两不交，覆盖第 1 至 10 点（50 分）。
// 一般时间 O(n^2)，两两不交时 O(n log n)，空间 O(n)。
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct node{
	int l,r;
	long long w;
};
bool cmp(node a,node b){
	return a.r < b.r;
}
int main(){
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<node> a(n + 1);
	vector<int> p(n + 1);
	for(int i = 1; i <= n; i++){
		cin >> a[i].l >> a[i].r >> a[i].w;
		p[i] = a[i].l;
	}
	sort(p.begin() + 1,p.end());
	int k = unique(p.begin() + 1,p.end()) - p.begin() - 1;
	vector<long long> diff(k + 2),v(k + 1);
	for(int i = 1; i <= n; i++){
		a[i].l = lower_bound(p.begin() + 1,p.begin() + k + 1,a[i].l) - p.begin();
		a[i].r = upper_bound(p.begin() + 1,p.begin() + k + 1,a[i].r) - p.begin() - 1;
		diff[a[i].l] += a[i].w;
		diff[a[i].r + 1] -= a[i].w;
	}
	sort(a.begin() + 1,a.end(),cmp);
	int j = 1;
	long long cover = 0,best = 0,ans = 0;
	for(int i = 1; i <= k; i++){
		cover += diff[i];
		while(j <= n && a[j].r < i){
			for(int t = a[j].l; t <= a[j].r; t++){
				v[t] += a[j].w;
				best = max(best,v[t]);
			}
			j++;
		}
		ans = max(ans,cover + best);
	}
	cout << ans << '\n';
	return 0;
}
