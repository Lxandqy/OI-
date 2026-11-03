// 纸牌游戏，部分分 3：至多两种牌，按首牌和末牌计数。
// 适用 m <= 2，覆盖点 1-3、13-14，保证 20 分；时间 O(n+m)，空间 O(m)。
#include<bits/stdc++.h>
using namespace std;

const int M = 300000 + 10;
int n,m,cnt[M];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int x = 0;
    for(int i = 1; i <= n; i++){
        cin >> x;
        cnt[x]++;
    }
    cnt[x] = n;
    for(int i = 1; i <= m; i++){
        if(i > 1) cout << ' ';
        cout << cnt[i];
    }
    cout << '\n';
    return 0;
}
