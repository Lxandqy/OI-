// 工坊互助：部分分 1，仅让一对工人互助，保证测试点 1~4（20 分）。
// 枚举工人对并检查工作量的平衡点，时间 O(n^2)，空间 O(n)。
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n,id[3];
long long a[N],b[N],c[N];

int main(){
	freopen("workshop.in","r",stdin);
	freopen("workshop.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i] >> c[i];
		ans = max(ans,a[i]);
		for(int j = 0; j < 3; j++){
			if(id[j] == 0 || a[i] > a[id[j]]){
				for(int k = 2; k > j; k--) id[k] = id[k - 1];
				id[j] = i;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			int x = i,y = j;
			if(a[x] < a[y]) swap(x,y);
			long long other = 0;
			for(int k = 0; k < 3; k++){
				if(id[k] != x && id[k] != y) other = max(other,a[id[k]]);
			}
			long long p = max(0LL,a[x] - a[y] - c[y]) / (b[y] + 1);
			for(long long v = p; v <= p + 1; v++){
				if(v == 0 || v > a[x]) continue;
				long long now = max(a[x] - v,a[y] + c[y] + b[y] * v);
				ans = min(ans,max(now,other));
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
