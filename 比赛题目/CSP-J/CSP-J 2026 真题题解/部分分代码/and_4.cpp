// 按位与 and，部分分 4：前后缀按位与，枚举删去的位置
// 适用条件：m=n-1
// 保证覆盖：点 11、12，10 分
// 复杂度：时间 O(n)，空间 O(n)
#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
int a[N],pre[N],suf[N];

int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    pre[0] = (1 << 30) - 1;
    for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] & a[i];
    suf[n + 1] = (1 << 30) - 1;
    for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] & a[i];
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans = max(ans,pre[i - 1] & suf[i + 1]);
    }
    cout << ans << '\n';
    return 0;
}
