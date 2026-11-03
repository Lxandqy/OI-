// 通行（rail），部分分第 1 项。
// 算法: 逐路段计次并搜索购卡组合。
// 适用条件: n<=18,m<=200
// 保证点号: 1,2,3,4; 保证分: 20。
// 时间复杂度: O(n*m+2^n)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int n,m,p[N],cnt[N];
long long a[N],b[N],c[N];
long long ans = LLONG_MAX;

void dfs(int i,long long cost){
    if(i == n){
        ans = min(ans,cost);
        return;
    }
    dfs(i + 1,cost + cnt[i] * a[i]);
    dfs(i + 1,cost + c[i] + cnt[i] * b[i]);
}

int main(){
    freopen("rail.in","r",stdin);
    freopen("rail.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> p[i];
    for(int i = 1; i < m; i++){
        int l = min(p[i],p[i + 1]);
        int r = max(p[i],p[i + 1]);
        for(int j = l; j < r; j++) cnt[j]++;
    }
    for(int i = 1; i < n; i++) cin >> a[i] >> b[i] >> c[i];
    dfs(1,0);
    cout << ans << '\n';
    return 0;
}
