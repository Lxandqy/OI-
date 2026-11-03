// 纸牌游戏，部分分 5：按首牌点数分组，分别沿最后出现位置跳转。
// 适用 m <= 3000，覆盖点 1-19，保证 76 分；时间 O(n+m^2)，空间 O(n+m)。
#include<bits/stdc++.h>
using namespace std;

const int N = 500000 + 10;
const int M = 300000 + 10;
int n,m,a[N],last[M],cnt[M],ans[M];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        last[a[i]] = i;
        cnt[a[i]]++;
    }
    for(int x = 1; x <= m; x++){
        int p = last[x];
        while(p <= n){
            ans[a[p]] += cnt[x];
            p = last[a[p]] + 1;
        }
    }
    for(int x = 1; x <= m; x++){
        if(x > 1) cout << ' ';
        cout << ans[x];
    }
    cout << '\n';
    return 0;
}
