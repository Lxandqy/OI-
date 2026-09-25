#include<bits/stdc++.h>
using namespace std;

const int N = 1005;
int n,m,k,sx,sy,ex,ey;
int cx[1010],cy[1010],diff[N][N],que[1000010];
unsigned char state[N][N];

void addRect(int x1,int y1,int x2,int y2){
	diff[x1][y1]++;
	diff[x2 + 1][y1]--;
	diff[x1][y2 + 1]--;
	diff[x2 + 1][y2 + 1]++;
}

bool check(int r,int &area){
	area = 0;
	if(r == 0) return true;
	for(int x = 0; x <= n; x++) memset(diff[x],0,(m + 1) * sizeof(int));
	for(int x = 0; x < n; x++) memset(state[x],0,m);
	for(int i = 0; i < k; i++){
		int x1 = max(0,cx[i] - r + 1);
		int x2 = min(n - 1,cx[i] + r - 1);
		int y1 = max(0,cy[i] - r + 1);
		int y2 = min(m - 1,cy[i] + r - 1);
		addRect(x1,y1,x2,y2);
	}
	for(int x = 0; x < n; x++){
		for(int y = 0; y < m; y++){
			if(x > 0) diff[x][y] += diff[x - 1][y];
			if(y > 0) diff[x][y] += diff[x][y - 1];
			if(x > 0 && y > 0) diff[x][y] -= diff[x - 1][y - 1];
			if(diff[x][y] > 0){
				state[x][y] = 1;
				area++;
			}
		}
	}
	if(state[sx][sy] || state[ex][ey]) return false;
	const int dx[4] = {0,1,0,-1};
	const int dy[4] = {1,0,-1,0};
	int head = 0,tail = 0;
	que[tail++] = sx * m + sy;
	state[sx][sy] = 2;
	while(head < tail){
		int id = que[head++];
		int x = id / m;
		int y = id % m;
		if(x == ex && y == ey) return true;
		for(int d = 0; d < 4; d++){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if(state[nx][ny]) continue;
			state[nx][ny] = 2;
			que[tail++] = nx * m + ny;
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
	swap(n,m);
	cin >> sx >> sy >> ex >> ey;
	for(int i = 0; i < k; i++) cin >> cx[i] >> cy[i];
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
