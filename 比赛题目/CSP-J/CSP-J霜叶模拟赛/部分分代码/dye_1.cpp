// 染布，部分分1：枚举最后一批的开头。
// n<=2000，保证测试点1至8，共40分；时间O(n^2)，空间O(n)。
#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
int n,l[N],r[N],f[N];
int main(){
    freopen("dye.in","r",stdin);
    freopen("dye.out","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
    for(int i = 1; i <= n; i++){
        f[i] = i;
        int x = 1,y = 1000000000;
        for(int j = i; j >= 1; j--){
            x = max(x,l[j]);
            y = min(y,r[j]);
            if(x > y) break;
            f[i] = min(f[i],f[j - 1] + 1);
        }
    }
    cout << f[n] << endl;
    return 0;
}
