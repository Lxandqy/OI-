#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("dye.in","r",stdin);
    freopen("dye.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,l,r,x,y,ans = 1;
    cin >> n >> l >> r;
    for(int i = 2; i <= n; i++){
        cin >> x >> y;
        if(max(l,x) <= min(r,y)){
            l = max(l,x);
            r = min(r,y);
        }else{
            ans++;
            l = x;
            r = y;
        }
    }
    cout << ans << endl;
    return 0;
}
