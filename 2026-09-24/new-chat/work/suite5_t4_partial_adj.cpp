#include<bits/stdc++.h>
using namespace std;

const int N = 1010;
int n,m,k,sx,sy,ex,ey;
int cx[N],cy[N],row[N];

int main(){
	freopen("green.in","r",stdin);
	freopen("green.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	cin >> sx >> sy >> ex >> ey;
	int r = max(n,m) + 1;
	for(int i = 0; i < k; i++){
		cin >> cx[i] >> cy[i];
		int ds = max(abs(sx - cx[i]),abs(sy - cy[i]));
		int de = max(abs(ex - cx[i]),abs(ey - cy[i]));
		r = min(r,min(ds,de));
	}
	int answer = 0;
	for(int x = 0; x < n; x++){
		memset(row,0,(m + 1) * sizeof(int));
		for(int i = 0; i < k; i++){
			if(abs(x - cx[i]) >= r) continue;
			int y1 = max(0,cy[i] - r + 1);
			int y2 = min(m - 1,cy[i] + r - 1);
			row[y1]++;
			row[y2 + 1]--;
		}
		int count = 0;
		for(int y = 0; y < m; y++){
			count += row[y];
			if(count > 0) answer++;
		}
	}
	cout << answer << '\n';
	return 0;
}
