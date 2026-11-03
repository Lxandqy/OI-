// 纸牌游戏，部分分 2：非递减序列中，答案为每种牌的最后出现位置。
// 适用性质 A，覆盖点 7-9、20，保证 16 分；时间 O(n+m)，空间 O(m)。
#include<bits/stdc++.h>
using namespace std;

const int M = 300000 + 10;
int n,m,last[M];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        last[x] = i;
    }
    for(int x = 1; x <= m; x++){
        if(x > 1) cout << ' ';
        cout << last[x];
    }
    cout << '\n';
    return 0;
}
