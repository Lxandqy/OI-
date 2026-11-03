// 按位与 and，部分分 2：两个边界的一次扫描
// 适用条件：m=1 或 m=n
// 保证覆盖：点 6、7，10 分
// 复杂度：时间 O(n)，额外空间 O(1)
#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    int mx = 0,all = (1 << 30) - 1;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        mx = max(mx,x);
        all &= x;
    }
    if(m == 1) cout << mx << '\n';
    else cout << all << '\n';
    return 0;
}
