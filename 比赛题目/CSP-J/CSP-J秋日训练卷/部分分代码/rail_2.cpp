// 通行（rail），部分分第 2 项。
// 算法: 逐路段计次并独立比较费用。
// 适用条件: n,m<=1500
// 保证点号: 1,2,3,4,5,6,7,8,9,10; 保证分: 50。
// 时间复杂度: O(n*m)。重叠点只计一次。
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int n,m,p[N];
long long cnt[N];

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
    long long ans = 0;
    for(int i = 1; i < n; i++){
        long long a,b,c;
        cin >> a >> b >> c;
        ans += min(cnt[i] * a,c + cnt[i] * b);
    }
    cout << ans << '\n';
    return 0;
}
