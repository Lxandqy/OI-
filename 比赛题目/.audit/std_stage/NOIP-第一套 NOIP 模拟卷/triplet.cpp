#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
struct node{
	int to,id;
};
vector<node> v[N];
vector<int> ans;
int n,deg[N],sz[N],tag[N],cnt[3];
bool cut[N],ok;

// r = -1 时不删环边，否则删去前缀和模 3 为 r 的环边。
void update(int r){
	vector<int> now;
	for(int i = 1; i <= n; i++){
		if(cut[i] || (r >= 0 && tag[i] == r)) now.push_back(i);
	}
	if(!ok || now < ans){
		ok = true;
		ans = now;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x,y;
		cin >> x >> y;
		v[x].push_back({y,i});
		v[y].push_back({x,i});
		deg[x]++;
		deg[y]++;
	}
	if(n % 3 != 0){
		cout << -1 << '\n';
		return 0;
	}
	queue<int> q;
	for(int i = 1; i <= n; i++){
		sz[i] = 1;
		tag[i] = -1;
		if(deg[i] == 1) q.push(i);
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		if(sz[x] > 3){
			cout << -1 << '\n';
			return 0;
		}
		deg[x] = 0;
		for(int i = 0; i < (int)v[x].size(); i++){
			int y = v[x][i].to,id = v[x][i].id;
			if(deg[y] == 0) continue;
			if(sz[x] == 3) cut[id] = true;
			else sz[y] += sz[x];
			deg[y]--;
			if(deg[y] == 1) q.push(y);
		}
	}

	int start = 1;
	while(deg[start] == 0) start++;
	int x = start,pre = 0,sum = 0;
	do{
		if(sz[x] > 3){
			cout << -1 << '\n';
			return 0;
		}
		sum += sz[x];
		for(int i = 0; i < (int)v[x].size(); i++){
			int y = v[x][i].to,id = v[x][i].id;
			if(deg[y] == 0 || y == pre) continue;
			tag[id] = sum % 3;
			cnt[tag[id]]++;
			pre = x;
			x = y;
			break;
		}
	}while(x != start);

	if(sum == 3) update(-1);
	for(int r = 0; r < 3; r++){
		if(cnt[r] == sum / 3) update(r);
	}
	if(!ok){
		cout << -1 << '\n';
		return 0;
	}
	cout << ans.size() << '\n';
	for(int i = 0; i < (int)ans.size(); i++){
		if(i) cout << ' ';
		cout << ans[i];
	}
	cout << '\n';
	return 0;
}
