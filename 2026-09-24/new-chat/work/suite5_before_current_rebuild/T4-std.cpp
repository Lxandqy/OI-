#include<bits/stdc++.h>
using namespace std;

int n,m,k,sx,sy,ex,ey;
const int MAXC = 1002010;
pair<int,int> center[1010];
int diff[MAXC],que[MAXC];
unsigned char blocked[MAXC],vis[MAXC];

void addRect(int x1,int y1,int x2,int y2){
	int w = m + 1;
	diff[x1 * w + y1]++;
	diff[(x2 + 1) * w + y1]--;
	diff[x1 * w + y2 + 1]--;
	diff[(x2 + 1) * w + y2 + 1]++;
}

bool check(int r,int &area){
	area = 0;
	if(r == 0) return true;
	fill(diff,diff + (n + 1) * (m + 1),0);
	fill(blocked,blocked + n * m,0);
	fill(vis,vis + n * m,0);
	for(int i = 0; i < k; i++){
		int x = center[i].first;
		int y = center[i].second;
		addRect(max(0,x - r + 1),max(0,y - r + 1),
			min(n - 1,x + r - 1),min(m - 1,y + r - 1));
	}
	for(int x = 0; x < n; x++){
		for(int y = 0; y < m; y++){
			int id = x * (m + 1) + y;
			if(x > 0) diff[id] += diff[(x - 1) * (m + 1) + y];
			if(y > 0) diff[id] += diff[id - 1];
			if(x > 0 && y > 0) diff[id] -= diff[(x - 1) * (m + 1) + y - 1];
			if(diff[id] > 0){
				blocked[x * m + y] = 1;
				area++;
			}
		}
	}
	int start = sx * m + sy;
	int goal = ex * m + ey;
	if(blocked[start] || blocked[goal]) return false;
	int head = 0,tail = 0;
	que[tail++] = start;
	vis[start] = 1;
	const int dx[4] = {1,-1,0,0};
	const int dy[4] = {0,0,1,-1};
	while(head < tail){
		int id = que[head++];
		if(id == goal) return true;
		int x = id / m;
		int y = id % m;
		for(int d = 0; d < 4; d++){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			int next = nx * m + ny;
			if(blocked[next] || vis[next]) continue;
			vis[next] = 1;
			que[tail++] = next;
		}
	}
	return false;
}

int main(){
	freopen("green.in","r",stdin);
	freopen("green.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	cin >> sx >> sy >> ex >> ey;
	for(int i = 0; i < k; i++) cin >> center[i].first >> center[i].second;
	int l = 0,r = max(n,m) + 1;
	while(l + 1 < r){
		int mid = (l + r) / 2;
		int area;
		if(check(mid,area)) l = mid;
		else r = mid;
	}
	int area;
	check(l,area);
	cout << area << '\n';
	return 0;
}
