// 纸牌游戏，部分分 4：压缩相等段，按段长加权模拟。
// 适用段数 r <= 5000，覆盖点 1-12、15-17，保证 60 分。
// 时间 O(n+r^2)，空间 O(n+m)。
#include<bits/stdc++.h>
using namespace std;

const int N = 500000 + 10;
const int M = 300000 + 10;
int n,m,r,b[N],len[N],st[M],pos[M],ans[M];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        if(r == 0 || b[r] != x){
            r++;
            b[r] = x;
        }
        len[r]++;
    }
    for(int i = 1; i <= r; i++){
        fill(pos + 1,pos + m + 1,0);
        int top = 0;
        for(int j = i; j <= r; j++){
            int x = b[j];
            if(pos[x]){
                int p = pos[x];
                while(top >= p){
                    pos[st[top]] = 0;
                    top--;
                }
            }
            top++;
            st[top] = x;
            pos[x] = top;
        }
        for(int j = 1; j <= top; j++) ans[st[j]] += len[i];
    }
    for(int x = 1; x <= m; x++){
        if(x > 1) cout << ' ';
        cout << ans[x];
    }
    cout << '\n';
    return 0;
}
