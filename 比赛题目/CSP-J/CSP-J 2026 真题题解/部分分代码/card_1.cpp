// 纸牌游戏，部分分 1：逐局栈模拟。
// 适用 n <= 5000，覆盖点 1-12，保证 48 分；时间 O(n^2)，空间 O(n+m)。
#include<bits/stdc++.h>
using namespace std;

const int N = 500000 + 10;
const int M = 300000 + 10;
int n,m,a[N],st[M],pos[M],ans[M];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++){
        fill(pos + 1,pos + m + 1,0);
        int top = 0;
        for(int j = i; j <= n; j++){
            int x = a[j];
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
        for(int j = 1; j <= top; j++) ans[st[j]]++;
    }
    for(int x = 1; x <= m; x++){
        if(x > 1) cout << ' ';
        cout << ans[x];
    }
    cout << '\n';
    return 0;
}
