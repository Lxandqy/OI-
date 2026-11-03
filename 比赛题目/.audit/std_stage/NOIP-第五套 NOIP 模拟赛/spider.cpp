#include<bits/stdc++.h>
using namespace std;
const int N = 300010,MOD = 998244353;
int n,a[N],spf[N],dist[N],ways[N],sum[N],mark[N];
bool used[N];
vector<int> factor[N],bucket[N],layer[N];
int divisors[64],signs[64];
int make_divisors(int x){
	int size = 1;
	divisors[0] = 1;
	signs[0] = -1;
	for(int i = 0; i < (int)factor[x].size(); i++){
		int old = size;
		for(int j = 0; j < old; j++){
			divisors[size] = divisors[j] * factor[x][i];
			signs[size] = -signs[j];
			size++;
		}
	}
	return size;
}
int main(){
	freopen("spider.in","r",stdin);
	freopen("spider.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	int bound = 1;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		bound = max(bound,a[i]);
	}
	int s,t;
	cin >> s >> t;
	for(int i = 1; i <= n; i++){
		factor[i].clear();
		layer[i - 1].clear();
		dist[i] = -1;
		ways[i] = 0;
	}
	for(int i = 0; i <= bound; i++){
		spf[i] = 0;
		bucket[i].clear();
		used[i] = false;
		mark[i] = -1;
	}
	for(int i = 2; i <= bound; i++){
		if(spf[i] != 0) continue;
		for(int j = i; j <= bound; j += i){
			if(spf[j] == 0) spf[j] = i;
		}
	}
	for(int i = 1; i <= n; i++){
		int x = a[i];
		while(x > 1){
			int p = spf[x];
			factor[i].push_back(p);
			bucket[p].push_back(i);
			while(x % p == 0) x /= p;
		}
	}
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		layer[dist[x]].push_back(x);
		for(int j = 0; j < (int)factor[x].size(); j++){
			int p = factor[x][j];
			if(used[p]) continue;
			used[p] = true;
			for(int z = 0; z < (int)bucket[p].size(); z++){
				int y = bucket[p][z];
				if(dist[y] != -1) continue;
				dist[y] = dist[x] + 1;
				q.push(y);
			}
		}
	}
	if(dist[t] == -1){
		cout << "-1 0\n";
		return 0;
	}
	ways[s] = 1;
	for(int d = 0; d < dist[t]; d++){
		for(int z = 0; z < (int)layer[d].size(); z++){
			int x = layer[d][z],size = make_divisors(x);
			for(int j = 1; j < size; j++){
				int v = divisors[j];
				if(mark[v] != d){
					mark[v] = d;
					sum[v] = 0;
				}
				sum[v] += ways[x];
				if(sum[v] >= MOD) sum[v] -= MOD;
			}
		}
		for(int z = 0; z < (int)layer[d + 1].size(); z++){
			int x = layer[d + 1][z],size = make_divisors(x);
			long long value = 0;
			for(int j = 1; j < size; j++){
				int v = divisors[j];
				if(mark[v] == d) value += 1LL * signs[j] * sum[v];
			}
			ways[x] = (value % MOD + MOD) % MOD;
		}
	}
	cout << dist[t] << ' ' << ways[t] << '\n';
	return 0;
}
