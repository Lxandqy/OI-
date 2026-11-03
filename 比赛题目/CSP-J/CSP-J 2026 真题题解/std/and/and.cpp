#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
int n,m,a[N];

int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    for(int b = 29; b >= 0; b--){
        int x = ans | (1 << b);
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            if((a[i] & x) == x) cnt++;
        }
        if(cnt >= m) ans = x;
    }
    cout << ans << '\n';
    return 0;
}
