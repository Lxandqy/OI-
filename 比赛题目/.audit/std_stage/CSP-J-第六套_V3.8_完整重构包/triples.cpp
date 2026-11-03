#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
struct Node {
	long long key, weight;
};
Node p[100005];
long long a[100005], b[100005], c[100005], prefix[100005];
int n;

bool cmp(const Node &u, const Node &v){
	return u.key < v.key;
}

long long calc(){
	sort(p + 1, p + n + 1, cmp);
	prefix[0] = 0;
	for(int i = 1; i <= n; i++){
		prefix[i] = (prefix[i - 1] + p[i].weight) % MOD;
	}
	long long result = 0;
	int r = n;
	for(int l = 1; l <= n; l++){
		while(r >= l && p[l].key + p[r].key > 0){
			r--;
		}
		if(r < l){
			break;
		}
		// 区间 [l,r] 包含自身，恰好统计一次无序点对。
		long long sum = (prefix[r] - prefix[l - 1] + MOD) % MOD;
		result = (result + p[l].weight * sum) % MOD;
	}
	return result;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> c[i];
		p[i].key = 2 * a[i] - b[i];
		p[i].weight = c[i];
	}
	long long ans = calc();
	for(int i = 1; i <= n; i++){
		p[i].key = 2 * b[i] - a[i];
		p[i].weight = c[i];
	}
	ans = (ans + calc()) % MOD;
	cout << ans << '\n';
	return 0;
}
