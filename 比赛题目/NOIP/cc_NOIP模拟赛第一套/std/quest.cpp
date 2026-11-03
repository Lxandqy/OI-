#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int c,n;
long long r;
long long a[N],b[N];
int must[N];
int pos[N],neg[N];
long long D[N];
bool cmpA(int x,int y){
	return a[x] < a[y];
}
bool cmpD(int x,int y){
	return D[x] < D[y];
}
int main(){
	freopen("quest.in","r",stdin);
	freopen("quest.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> c;
	cin >> n >> r;
	int np = 0,nn = 0;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> must[i];
		if(b[i] >= 0) pos[++np] = i;
		else neg[++nn] = i;
	}
	// 第一步：体力不减的委托按要求从小到大，能做就做
	sort(pos + 1,pos + np + 1,cmpA);
	long long R = r;
	int ans = 0;
	for(int t = 1; t <= np; t++){
		int i = pos[t];
		if(a[i] > R){
			// 之后的要求只会更高，都做不了
			for(int s = t; s <= np; s++){
				if(must[pos[s]]){
					cout << -1 << endl;
					return 0;
				}
			}
			break;
		}
		R += b[i];
		ans++;
	}
	// 第二步：体力减少的委托，做完后累计消耗不能超过 D[i]，按 D 从小到大考虑
	for(int t = 1; t <= nn; t++){
		int i = neg[t];
		D[i] = R - max(a[i] + b[i],0LL);
	}
	sort(neg + 1,neg + nn + 1,cmpD);
	// 已选的可选委托：按消耗从大到小取出，存（消耗，编号）
	priority_queue<pair<long long,int> > q;
	long long total = 0;
	int cnt = 0;
	for(int t = 1; t <= nn; t++){
		int i = neg[t];
		long long cost = -b[i];
		total += cost;
		cnt++;
		if(!must[i]) q.push(make_pair(cost,i));
		// 加入 i 后超出期限：放弃消耗最大的可选委托，直到不超出或者 i 自己被放弃
		while(total > D[i]){
			if(q.empty()){
				// 只剩必做委托仍然超出，i 一定是必做的，无法完成
				cout << -1 << endl;
				return 0;
			}
			int j = q.top().second;
			total -= q.top().first;
			q.pop();
			cnt--;
			if(j == i) break;
		}
	}
	cout << ans + cnt << endl;
	return 0;
}
