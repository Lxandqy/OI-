#include<bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int edgeU[100005], edgeV[100005], que[100005];
bool seen[100005];
int n, bannedU, bannedV;

int countLeaves(int start){
	for(int i = 1; i <= n; i++){
		seen[i] = false;
	}
	int head = 0, tail = 1, result = 0;
	que[0] = start;
	seen[start] = true;
	while(head < tail){
		int u = que[head++];
		int degree = (int)g[u].size();
		if(u == bannedU || u == bannedV){
			degree--;
		}
		if(degree <= 1){
			result++;
		}
		for(int j = 0; j < (int)g[u].size(); j++){
			int v = g[u][j];
			if((u == bannedU && v == bannedV) ||
				(u == bannedV && v == bannedU)){
				continue;
			}
			if(!seen[v]){
				seen[v] = true;
				que[tail++] = v;
			}
		}
	}
	return result;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			g[i].clear();
		}
		for(int i = 1; i < n; i++){
			cin >> edgeU[i] >> edgeV[i];
			g[edgeU[i]].push_back(edgeV[i]);
			g[edgeV[i]].push_back(edgeU[i]);
		}
		bool chain = true;
		for(int i = 1; i <= n; i++){
			if(g[i].size() > 2){
				chain = false;
			}
		}
		if(chain){
			if(n == 2){
				cout << "0 1\n";
			} else if(n == 3){
				cout << "1 2\n";
			}else{
				cout << 0 << ' ' << n - 3 << '\n';
			}
			continue;
		}
		int ans = n, ways = 0;
		for(int i = 1; i < n; i++){
			bannedU = edgeU[i];
			bannedV = edgeV[i];
			int left = countLeaves(bannedU);
			int right = countLeaves(bannedV);
			int difference = abs(left - right);
			if(difference < ans){
				ans = difference;
				ways = 1;
			} else if(difference == ans){
				ways++;
			}
		}
		cout << ans << ' ' << ways << '\n';
	}
	return 0;
}
