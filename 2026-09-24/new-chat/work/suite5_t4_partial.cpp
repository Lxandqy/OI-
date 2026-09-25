#include<bits/stdc++.h>
using namespace std;

const int N = 1005;
int n,m,k,sx,sy,ex,ey;
int cx[1010],cy[1010],que[1000010];
unsigned char blocked[N][N];

bool check(int r,int &area){
	area = 0;
	for(int x = 0; x < n; x++) memset(blocked[x],0,m);
	for(int i = 0; i < k; i++){
		int x1 = max(0,cx[i] - r + 1);
		int x2 = min(n - 1,cx[i] + r - 1);
		int y1 = max(0,cy[i] - r + 1);
		int y2 = min(m - 1,cy[i] + r - 1);
		for(int x = x1; x <= x2; x++){
			memset(blocked[x] + y1,1,y2 - y1 + 1);
		}
	}
	for(int x = 0; x < n; x++){
		for(int y = 0; y < m; y++) area += blocked[x][y] != 0;
	}
	if(blocked[sx][sy] || blocked[ex][ey]) return false;
	int head = 0,tail = 0;
	que[tail++] = sx * m + sy;
	blocked[sx][sy] = 2;
	const int dx[4] = {0,1,0,-1};
	const int dy[4] = {1,0,-1,0};
	while(head < tail){
		int id = que[head++];
		int x = id / m;
		int y = id % m;
		if(x == ex && y == ey) return true;
		for(int d = 0; d < 4; d++){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if(blocked[nx][ny]) continue;
			blocked[nx][ny] = 2;
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
	cin >> sx >> sy >> ex >> ey;
	for(int i = 0; i < k; i++) cin >> cx[i] >> cy[i];
	int answer = 0;
	for(int r = 1; r <= max(n,m); r++){
		int area;
		if(!check(r,area)) break;
		answer = area;
	}
	cout << answer << '\n';
	return 0;
}
