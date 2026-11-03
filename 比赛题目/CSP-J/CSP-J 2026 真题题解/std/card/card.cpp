#include<bits/stdc++.h>
using namespace std;

const int N = 500000 + 10;
const int M = 300000 + 10;
int n,m,a[N],f[N],last[M],ans[M];

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        last[a[i]] = i;
        f[i] = 1;
    }
    for(int i = 1; i <= n; i++){
        int x = a[i];
        ans[x] += f[i];
        f[last[x] + 1] += f[i];
    }
    for(int x = 1; x <= m; x++){
        if(x > 1) cout << ' ';
        cout << ans[x];
    }
    cout << '\n';
    return 0;
}
